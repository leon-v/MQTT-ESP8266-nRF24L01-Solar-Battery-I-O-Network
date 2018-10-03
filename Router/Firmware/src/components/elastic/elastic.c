// #include <stddef.h>
// #include <stdio.h>
// #include <string.h>
// #include <netdb.h>
// #include <sys/socket.h>

// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"
// #include "freertos/queue.h"

// #include "mbedtls/platform.h"
// #include "mbedtls/net_sockets.h"
// #include "mbedtls/esp_debug.h"
// #include "mbedtls/ssl.h"
// #include "mbedtls/entropy.h"
// #include "mbedtls/ctr_drbg.h"
// #include "mbedtls/error.h"
// #include "mbedtls/certs.h"

// #include "wifi.h"
// #include "radio.h"


// // /* Constants that aren't configurable in menuconfig */
// // #define WEB_SERVER "www.howsmyssl.com"
// // #define WEB_PORT "443"
// // #define WEB_URL "https://www.howsmyssl.com/a/check"

// // static const char *REQUEST = "GET " WEB_URL " HTTP/1.0\r\n"
// //     "Host: "WEB_SERVER"\r\n"
// //     "User-Agent: esp-idf/1.0 esp32\r\n"
// //     "\r\n";

// // /* Root cert for howsmyssl.com, taken from server_root_cert.pem

// //    The PEM file was extracted from the output of this command:
// //    openssl s_client -showcerts -connect www.howsmyssl.com:443 </dev/null

// //    The CA root cert is the last cert given in the chain of certs.

// //    To embed it in the app binary, the PEM file is named
// //    in the component.mk COMPONENT_EMBED_TXTFILES variable.
// // */
// // extern const uint8_t server_root_cert_pem_start[] asm("_binary_server_root_cert_pem_start");
// // extern const uint8_t server_root_cert_pem_end[]   asm("_binary_server_root_cert_pem_end");




// static xQueueHandle elasticPublishQueue = NULL;

// xQueueHandle elasticGetPublishQueue(void){
// 	return elasticPublishQueue;
// }

// static void elasticPublishTask(void *arg){

// 	radioMessage_t radioMessage;
// 	EventBits_t wifiEventBits;
// 	BaseType_t response;

// 	for (;;){

// 		printf("elasticPublishTask Loop Start\n");

// 		wifiEventBits = xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, 1000 / portTICK_RATE_MS);

// 		if (!(wifiEventBits & WIFI_CONNECTED_BIT)){
// 			printf("elasticPublishTask WiFi not Ready\n");
// 			vTaskDelay(1000 / portTICK_PERIOD_MS);
// 			continue;
// 		}

// 		response = xQueueReceive(elasticPublishQueue, &radioMessage, 1000 / portTICK_RATE_MS);

// 		if (!response){
// 			continue;
// 		}

// 		// Got message
// 		printf("Elastic Send %s/%s/%s\n", radioMessage.name, radioMessage.sensor, radioMessage.value);

// 	}
// }


// void elasticInit(void){

// 	elasticPublishQueue = xQueueCreate(256, sizeof(radioMessage_t));

// 	xTaskCreate(&elasticPublishTask, "elasticPublishTask", 8192, NULL, 13, NULL);
// }