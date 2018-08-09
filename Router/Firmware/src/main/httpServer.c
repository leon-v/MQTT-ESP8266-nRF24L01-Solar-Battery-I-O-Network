#include <stdio.h>
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

#include "httpServerIndex.h";

#include <sys/socket.h>


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
        goto failed2;
    }
    printf("OK\n");

    char http_header[4096];

reconnect:
	
	strcpy(http_header, "HTTP/1.1 200 OK\r\n\r\n");

	strcat(http_header, httpServerIndex);


    printf("HTTP server socket accept client ......");
    new_sockfd = accept(sockfd, (struct sockaddr*)&sock_addr, &addr_len);

    if (new_sockfd < 0) {
        printf("failed\n");
        goto failed3;
    }
    printf("OK\n");

    send(new_sockfd, http_header, strlen(http_header), 0);

    close(new_sockfd);

failed3:
	goto reconnect;

failed2:
    close(sockfd);
    sockfd = -1;

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
