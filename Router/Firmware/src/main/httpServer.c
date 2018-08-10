#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "wifi.h"

#include "httpServer.h"
#include "httpServerPage.h"

#include <sys/socket.h>

const char httpServerOK[] = "HTTP/1.1 200 OK\r\n\r\n";
const char httpServerNotFound[] = "HTTP/1.1 404 Not Found\r\n\r\n";

//https://gist.github.com/laobubu/d6d0e9beb934b60b2e552c2d03e1409e

header_t reqhdr[32] = { {"\0", "\0"} };

char *request_header(const char* name)
{
    header_t *h = reqhdr;
    while(h->name) {
        if (strcmp(h->name, name) == 0) return h->value;
        h++;
    }
    return NULL;
}

void httpServerTask(){

	int ret;

	struct sockaddr_in sock_addr;
    int sockfd, new_sockfd;
    int recv_bytes = 0;
    socklen_t addr_len;

	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	printf("create socket ......");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("failed\n");
        goto failed1;
    }

    printf("OK\n");

	
	printf("socket bind ......");
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = 0;
    sock_addr.sin_port = htons(80);

    ret = bind(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));

    if (ret) {
        printf("bind failed\n");
        goto failed1;
    }

    printf("OK\n");

    printf("server socket listen ......");
    ret = listen(sockfd, 4);

    if (ret) {
        printf("failed\n");
        goto failed1;
    }
    printf("OK\n");

    char * html = NULL;

reconnect:

	// strcpy(http_header, "HTTP/1.1 200 OK\r\n\r\n");

	// strcat(http_header, );


    printf("HTTP server socket accept client ......");
    new_sockfd = accept(sockfd, (struct sockaddr*)&sock_addr, &addr_len);

    if (new_sockfd < 0) {
        printf("failed\n");
        goto failed2;
    }
    printf("OK\n");


    char buffer[1024];

    recv_bytes = recv(new_sockfd, &buffer, sizeof(buffer), 0);

    printf("R Bytes: %i\n", recv_bytes);

    if (recv_bytes <= 0){
    	printf("No Data\n");
        goto failed3;
    }

    buffer[recv_bytes] = '\0';

	char * method = strtok(buffer	,  " \t\r\n");
	char * uri    = strtok(NULL	, " \t");
	char * prot   = strtok(NULL	, " \t\r\n");

	printf("M: %s, U: %s, P:%s", method, uri, prot);

	header_t *h = reqhdr;
	char *t = NULL;

	char *k, *v;
    while (h < ( reqhdr + sizeof(reqhdr) - 1)) {

        k = strtok(NULL, "\r\n: \t");
        if (!k){
        	break;
        }

        v = strtok(NULL, "\r\n");

        while(*v && *v==' '){
        	v++;
        }

        h->name  = k;
        h->value = v;
        h++;

        printf("[H] %s: %s\n", k, v);

        t = v + 1 + strlen(v);

        if (t[1] == '\r' && t[2] == '\n'){
        	printf("[H] END\n");
        	break;
        }
    }


	t++; // now the *t shall be the beginning of user payload
	char * t2 = request_header("Content-Length"); // and the related header if there is  
	char * payload = t;
	int payload_size = t2 ? atol(t2) : (recv_bytes - (t - buffer));

	printf("payload_size: %i\n", payload_size);

	printf("data length: %i\n", strlen(payload));

	printf("Data: %s\n", payload);

    html = httpServerPageGet(uri);

    if (html == NULL){
    	send(new_sockfd, httpServerNotFound, strlen(httpServerNotFound), 0);
    }
    else{
    	send(new_sockfd, httpServerOK, strlen(httpServerOK), 0);
    	send(new_sockfd, html, strlen(html), 0);
    	free(html);
    }
failed3:
    printf("Close Socket\n");
    close(new_sockfd);
    new_sockfd = -1;

failed2:
	goto reconnect;

failed1:
    close(sockfd);
    sockfd = -1;
    vTaskDelete(NULL);
    printf("task exit\n");

    return ;
}

void httpServerInit(void) {
	ESP_ERROR_CHECK(nvs_flash_init());
    xTaskCreate(&httpServerTask, "httpServer", 8192, NULL, 6, NULL);
}
