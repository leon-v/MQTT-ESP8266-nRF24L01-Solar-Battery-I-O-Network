
#define MQTT_CLIENT_THREAD_STACK_WORDS  8192
#define MQTT_CLIENT_THREAD_PRIO         8

#include "wifi.h"

void radioMQTTRouterTask(){

	MQTTClient client;
    Network network;
    unsigned char sendbuf[80], readbuf[80] = {0};
    int rc = 0, count = 0;
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

    printf("mqtt client thread starts\n");


	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	
}


void radioMQTTRouterInt(){

	// xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	// printf("MQTT Connect ......");

	xTaskCreate(&radioMQTTRouterTask, "radioMQTTRouter", MQTT_CLIENT_THREAD_STACK_WORDS, NULL, MQTT_CLIENT_THREAD_PRIO, NULL);
}