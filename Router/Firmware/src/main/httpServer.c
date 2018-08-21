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
#include "configFlash.h"

#include <sys/socket.h>

const char httpServerOK[] = "HTTP/1.0 200 OK\r\n\r\n";
const char httpServerNotFound[] = "HTTP/1.0 404 Not Found\r\n\r\n";

//https://gist.github.com/laobubu/d6d0e9beb934b60b2e552c2d03e1409e


char * httpServerParseValues(tokens_t * tokens, char * buffer, const char * rowDelimiter, const char * valueDelimiter, const char * endMatch){

	tokens->length = 0;

	// Start parsing the values by creating a new string from the payload 
	char * token = strtok(buffer, rowDelimiter);

	char * end = buffer + strlen(buffer);

	// break apart the string getting all the parts delimited by &
	while (token != NULL) {

		if (strlen(endMatch) > 0){
			end = token + strlen(token) + 1;

			if (strncmp(end, endMatch, strlen(endMatch)) == 0) {
				end+= strlen(endMatch);
				break;
			}
		}

		tokens->tokens[tokens->length++].key = token;

		token = strtok(NULL, rowDelimiter);
	}

	// Re-parse the strigns and break them apart into key / value pairs
	for (unsigned int index = 0; index < tokens->length; index++){

		tokens->tokens[index].key = strtok(tokens->tokens[index].key, valueDelimiter);

		tokens->tokens[index].value = strtok(NULL, valueDelimiter);

		// If the value is NULL, make it point to an empty string.
		if (tokens->tokens[index].value == NULL){
			tokens->tokens[index].value = tokens->tokens[index].key + strlen(tokens->tokens[index].key);
		}
	}

	return end;
}

char * httpServerGetTokenValue(tokens_t * tokens, const char * key){

	for (unsigned int index = 0; index < tokens->length; index++){

		if (strcmp(tokens->tokens[index].key, key) == 0){
			return tokens->tokens[index].value;
		}
	}

	return NULL;
}

//https://github.com/starnight/MicroHttpServer/blob/master/c-version/lib/server.c
void httpServerTask(){

	int ret;

	struct sockaddr_in sock_addr;
    int sockfd, new_sockfd;
    int recv_bytes = 0;
    socklen_t addr_len;
    char * html = NULL;
    char buffer[1024];
    EventBits_t wifiEventBits;

    struct timeval tv;
    tv.tv_sec = 2000;  /* 1 Secs Timeout */

restart:
    printf("HTTP Server - Connection - Thread start. Waiting for network.\n");

    xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	vTaskDelay(500 / portTICK_RATE_MS);

	printf("HTTP Server - Connection - Creating socket.\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("HTTP Server - Connection - Failed to create socket.\n");
        goto failed1;
    }

    printf("HTTP Server - Connection - Successfully created socket.\n");

	
	printf("HTTP Server - Connection - Binding socket.\n");
    memset(&sock_addr, 0, sizeof(sock_addr));
    sock_addr.sin_family = AF_INET;
    sock_addr.sin_addr.s_addr = 0;
    sock_addr.sin_port = htons(80);

    ret = bind(sockfd, (struct sockaddr*)&sock_addr, sizeof(sock_addr));

    if (ret) {
        printf("HTTP Server - Connection - Failed to bind socket.\n");
        goto failed1;
    }

    printf("HTTP Server - Connection - Successfully bound socket.\n");

    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof(struct timeval));

    printf("HTTP Server - Connection - Listening for connection.\n");
    ret = listen(sockfd, 4);

    if (ret) {
        printf("HTTP Server - Connection - Failed to listen for connection.\n");
        goto failed1;
    }

    printf("HTTP Server - Connection - Got connection.\n");

reconnect:

	vTaskDelay(500 / portTICK_RATE_MS);

	wifiEventBits = xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, 10000);

	if (!(wifiEventBits & WIFI_CONNECTED_BIT) ){
		printf("HTTP Server - Connection - WiFi not ready.\n");
		goto failed1;
	}

    printf("HTTP Server - Connection - Waiting for connection.\n");


    
    new_sockfd = accept(sockfd, (struct sockaddr*) &sock_addr, &addr_len);

    if (new_sockfd < 0) {
        printf("HTTP Server - Connection - Failed to accept connection.\n");
        goto failed2;
    }

    printf("HTTP Server - Connection - Accepted connection.\n");

	setsockopt(new_sockfd, SOL_SOCKET, SO_RCVTIMEO, (char *) &tv, sizeof(struct timeval));

    recv_bytes = recv(new_sockfd, &buffer, sizeof(buffer), 0);

    if (recv_bytes <= 0){
    	printf("HTTP Server - Connection - No data received from client.\n");
        goto failed3;
    }

    if (configFlash.debugLevel > 2){
    	printf("HTTP Server - Connection - Got %d bytes from client.\n", recv_bytes);
    }

    buffer[recv_bytes] = '\0';

	char * method = strtok(buffer	,  " \t\r\n");
	char * uri    = strtok(NULL	, " \t");
	char * prot   = strtok(NULL	, " \t\r\n");

	char * headStart = strtok(NULL	, "");

	tokens_t header;

	char * payload = httpServerParseValues(&header, headStart, "\t\r\n", ": ", "\n\r\n");

	char * contentLengthString = httpServerGetTokenValue(&header, "Content-Length");

	if (contentLengthString != NULL){
		printf("contentLengthString %s\n", contentLengthString);
	}

	int contentLength = contentLengthString ? atol(contentLengthString) : strlen(payload);

	printf("contentLength %d\n", contentLength);
	printf("strlen(payload) %d\n", strlen(payload));
	
	// Check if contentLength matches buffer, and if not, wait for more data

    html = httpServerPageGet(method, uri, payload);

    if (html == NULL){
    	send(new_sockfd, httpServerNotFound, strlen(httpServerNotFound), 0);
    }
    else{
    	send(new_sockfd, httpServerOK, strlen(httpServerOK), 0);
    	send(new_sockfd, html, strlen(html), 0);
    	free(html);
    }

failed3:
	if (configFlash.debugLevel > 2){
    	printf("HTTP Server - Connection - Closing connection.\n");
    }
    close(new_sockfd);
    new_sockfd = -1;

failed2:
	goto reconnect;

failed1:
	
	printf("HTTP Server - Connection - Fatal error. Closing socket and ending.\n");
    close(sockfd);
    sockfd = -1;
    goto restart;

    vTaskDelete(NULL);
    return ;
}

void httpServerInit(void) {

	ESP_ERROR_CHECK(nvs_flash_init());

    xTaskCreate(&httpServerTask, "httpServer", 8192, NULL, 9, NULL);
}


