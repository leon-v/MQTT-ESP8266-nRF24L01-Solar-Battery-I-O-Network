#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "mbedtls/platform.h"
#include "mbedtls/net_sockets.h"
#include "mbedtls/esp_debug.h"
#include "mbedtls/ssl.h"
#include "mbedtls/entropy.h"
#include "mbedtls/ctr_drbg.h"
#include "mbedtls/error.h"
#include "mbedtls/certs.h"

#include "wifi.h"
#include "radio.h"


/* Constants that aren't configurable in menuconfig */
#define WEB_SERVER "www.howsmyssl.com"
#define WEB_PORT "443"
#define WEB_URL "https://www.howsmyssl.com/a/check"

static const char *REQUEST = "GET " WEB_URL " HTTP/1.0\r\n"
    "Host: "WEB_SERVER"\r\n"
    "User-Agent: esp-idf/1.0 esp32\r\n"
    "\r\n";

/* Root cert for howsmyssl.com, taken from server_root_cert.pem

   The PEM file was extracted from the output of this command:
   openssl s_client -showcerts -connect www.howsmyssl.com:443 </dev/null

   The CA root cert is the last cert given in the chain of certs.

   To embed it in the app binary, the PEM file is named
   in the component.mk COMPONENT_EMBED_TXTFILES variable.
*/
extern const uint8_t server_root_cert_pem_start[] asm("_binary_server_root_cert_pem_start");
extern const uint8_t server_root_cert_pem_end[]   asm("_binary_server_root_cert_pem_end");




static xQueueHandle elasticPublishQueue = NULL;

xQueueHandle elasticGetPublishQueue(void){
	return elasticPublishQueue;
}

static void elasticPublishTask(void *arg){

	radioMessage_t radioMessage;
	EventBits_t wifiEventBits;
	BaseType_t response;

	char buf[512];
    int ret, flags, len;

    mbedtls_entropy_context entropy;
    mbedtls_ctr_drbg_context ctr_drbg;
    mbedtls_ssl_context ssl;
    mbedtls_x509_crt cacert;
    mbedtls_ssl_config conf;
    mbedtls_net_context server_fd;

start:

    printf("elasticPublishTask xEventGroupWaitBits\n");

	wifiEventBits = xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	if (!(wifiEventBits & WIFI_CONNECTED_BIT)){
		goto start;
	}

    mbedtls_ssl_init(&ssl);
    mbedtls_x509_crt_init(&cacert);
    mbedtls_ctr_drbg_init(&ctr_drbg);

    printf("elasticPublishTask Seeding the random number generator\n");

    mbedtls_ssl_config_init(&conf);

    mbedtls_entropy_init(&entropy);

    if((ret = mbedtls_ctr_drbg_seed(&ctr_drbg, mbedtls_entropy_func, &entropy, NULL, 0)) != 0) {
        printf("elasticPublishTask mbedtls_ctr_drbg_seed returned %d\n", ret);
        abort();
    }

    printf("elasticPublishTask Loading the CA root certificate...\n");

    ret = mbedtls_x509_crt_parse(&cacert, server_root_cert_pem_start, server_root_cert_pem_end-server_root_cert_pem_start);

    if(ret < 0) {
        printf("elasticPublishTask mbedtls_x509_crt_parse returned -0x%x\n\n", -ret);
        abort();
    }

    printf("elasticPublishTask Setting hostname for TLS session...\n");

     /* Hostname set here should match CN in server certificate */
    if((ret = mbedtls_ssl_set_hostname(&ssl, WEB_SERVER)) != 0) {
        printf("elasticPublishTask mbedtls_ssl_set_hostname returned -0x%x\n", -ret);
        abort();
    }

    printf("elasticPublishTask Setting up the SSL/TLS structure...\n");

    if((ret = mbedtls_ssl_config_defaults(&conf, MBEDTLS_SSL_IS_CLIENT, MBEDTLS_SSL_TRANSPORT_STREAM, MBEDTLS_SSL_PRESET_DEFAULT)) != 0) {
        printf("elasticPublishTask mbedtls_ssl_config_defaults returned %d\n", ret);
        goto exit;
    }

    /* MBEDTLS_SSL_VERIFY_OPTIONAL is bad for security, in this example it will print
       a warning if CA verification fails but it will continue to connect.

       You should consider using MBEDTLS_SSL_VERIFY_REQUIRED in your own code.
    */
    mbedtls_ssl_conf_authmode(&conf, MBEDTLS_SSL_VERIFY_OPTIONAL);
    mbedtls_ssl_conf_ca_chain(&conf, &cacert, NULL);
    mbedtls_ssl_conf_rng(&conf, mbedtls_ctr_drbg_random, &ctr_drbg);

#ifdef CONFIG_MBEDTLS_DEBUG
    mbedtls_esp_enable_debug_log(&conf, 4);
#endif

    if ((ret = mbedtls_ssl_setup(&ssl, &conf)) != 0) {
        printf("elasticPublishTask mbedtls_ssl_setup returned -0x%x\n", -ret);
        goto exit;
    }

	printf("elasticPublishTask Start\n");

	for (;;){

		printf("elasticPublishTask xQueueReceive\n");

		response = xQueueReceive(elasticPublishQueue, &radioMessage, 1000 / portTICK_RATE_MS);

		if (!response){
			continue;
		}

		    printf("elasticPublishTask xEventGroupWaitBits\n");

			wifiEventBits = xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

			if (!(wifiEventBits & WIFI_CONNECTED_BIT)){
				continue;
			}

        printf("elasticPublishTask Connected to AP\n");

        mbedtls_net_init(&server_fd);

        printf("elasticPublishTask Connecting to %s:%s...\n", WEB_SERVER, WEB_PORT);

        if ((ret = mbedtls_net_connect(&server_fd, WEB_SERVER, WEB_PORT, MBEDTLS_NET_PROTO_TCP)) != 0) {
            printf("elasticPublishTask mbedtls_net_connect returned -%x\n", -ret);
            goto exit;
        }

        printf("elasticPublishTask Connected.\n");

        mbedtls_ssl_set_bio(&ssl, &server_fd, mbedtls_net_send, mbedtls_net_recv, NULL);

        printf("elasticPublishTask Performing the SSL/TLS handshake...\n");

        while ((ret = mbedtls_ssl_handshake(&ssl)) != 0) {

            if (ret != MBEDTLS_ERR_SSL_WANT_READ && ret != MBEDTLS_ERR_SSL_WANT_WRITE) {
                printf("elasticPublishTask mbedtls_ssl_handshake returned -0x%x\n", -ret);
                goto exit;
            }
        }

        printf("elasticPublishTask Verifying peer X.509 certificate...\n");

        if ((flags = mbedtls_ssl_get_verify_result(&ssl)) != 0) {

            /* In real life, we probably want to close connection if ret != 0 */
            printf("elasticPublishTask Failed to verify peer certificate!\n");
            bzero(buf, sizeof(buf));
            mbedtls_x509_crt_verify_info(buf, sizeof(buf), "  ! ", flags);
            printf("elasticPublishTask verification info: %s\n", buf);
        }

        else {
            printf("elasticPublishTask Certificate verified.\n");
        }

        printf("elasticPublishTask Cipher suite is %s\n", mbedtls_ssl_get_ciphersuite(&ssl));

        printf("elasticPublishTask Writing HTTP request...\n");

        size_t written_bytes = 0;
        do {
            ret = mbedtls_ssl_write(&ssl, (const unsigned char *)REQUEST + written_bytes, strlen(REQUEST) - written_bytes);

            if (ret >= 0) {
                printf("elasticPublishTask %d bytes written\n", ret);
                written_bytes += ret;
            }

            else if (ret != MBEDTLS_ERR_SSL_WANT_WRITE && ret != MBEDTLS_ERR_SSL_WANT_READ) {
                printf("elasticPublishTask mbedtls_ssl_write returned -0x%x\n", -ret);
                goto exit;
            }

        } while(written_bytes < strlen(REQUEST));

        printf("elasticPublishTask Reading HTTP response...\n");

        do {
            len = sizeof(buf) - 1;
            bzero(buf, sizeof(buf));
            ret = mbedtls_ssl_read(&ssl, (unsigned char *)buf, len);

            if(ret == MBEDTLS_ERR_SSL_WANT_READ || ret == MBEDTLS_ERR_SSL_WANT_WRITE){
                continue;
            }

            if (ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) {
                ret = 0;
                break;
            }

            if (ret < 0) {
                printf("elasticPublishTask mbedtls_ssl_read returned -0x%x\n", -ret);
                break;
            }

            if (ret == 0) {
                printf("elasticPublishTask connection closed\n");
                break;
            }

            len = ret;
            printf("elasticPublishTask %d bytes read\n", len);
            /* Print response directly to stdout as it is read */
            for(int i = 0; i < len; i++) {
                putchar(buf[i]);
            }

        } while(1);

        mbedtls_ssl_close_notify(&ssl);

    exit:
        mbedtls_ssl_session_reset(&ssl);
        mbedtls_net_free(&server_fd);

        if(ret != 0) {
            mbedtls_strerror(ret, buf, 100);
            printf("elasticPublishTask Last error was: -0x%x - %s\n", -ret, buf);
        }

        putchar('\n'); // JSON output doesn't have a newline at end

        static int request_count;
        printf("elasticPublishTask Completed %d requests", ++request_count);

        for(int countdown = 10; countdown >= 0; countdown--) {
            printf("elasticPublishTask %d...\n", countdown);
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }

        printf("elasticPublishTask Starting again!\n");

		// Got message
		printf("Elastic Send %s/%s/%s\n", radioMessage.name, radioMessage.sensor, radioMessage.value);

	}
}


void elasticInit(void){

	elasticPublishQueue = xQueueCreate(256, sizeof(radioMessage_t));

	xTaskCreate(&elasticPublishTask, "elasticPublishTask", 2048, NULL, 14, NULL);
}