
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "mqtt.h"
#include "configFlash.h"
#include "wifi.h"

#define MQTT_TASK 1

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t mqttEventGroup;

MQTTClient client;

EventGroupHandle_t mqttGetEventGroup(void){
	return mqttEventGroup;
}

MQTTClient * mqttGetClient(void){
	return &client;
}

void mqttTask(){
    Network network;
    unsigned char sendbuf[80];
    unsigned char readbuf[80] = {0};
    int rc = 0;
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

reconnect:

    printf("MQTT Client - Connection - Thread start.\n");

    vTaskDelay(5000 / portTICK_RATE_MS);  //send every 10 seconds

	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	NetworkInit(&network);

	MQTTClientInit(&client, &network, (configFlash.mqttKeepalive * 1000), sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	char * address = (char *) &configFlash.mqttHost;
	
    if ((rc = NetworkConnect(&network, address, configFlash.mqttPort)) != 0) {
    	printf("MQTT Client - Connection - Failed to connect to %s:%d with error %d.\n", address, configFlash.mqttPort, rc);
        goto fail2;
    }

    printf("MQTT Client - Connection - Socket connected.\n");

    #if defined(MQTT_TASK)

    if ((rc = MQTTStartTask(&client)) != pdPASS) {
        printf("MQTT Client - Connection - Task thread start failed with error %d.\n", rc);
        goto fail1;
    }

    printf("MQTT Client - Connection - Task thread started.\n");

	#endif

    connectData.MQTTVersion = 4; // 3 = 3.1 4 = 3.1.1
    connectData.clientID.cstring = "NRF24L01+ Router ESP8266 TestW";
    //sprintf(connectData.clientID.cstring, "NRF24L01+ Router ESP8266 %u", system_get_chip_id());
    //connectData.clientID.lenstring = strlen(connectData.clientID.cstring);
    // connectData.keepAliveInterval = 30;
    // connectData.cleansession = 0;
    connectData.username.cstring = (char *) &configFlash.mqttUsername;
    connectData.password.cstring = (char *) &configFlash.mqttPassword;

    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("MQTT Client - Connection - Failed to authenticate with MQTT server with error code %d.\n", rc);
        goto fail1;
    }
	
	printf("MQTT Client - Connection - Connected.\n");

	xEventGroupSetBits(mqttEventGroup, MQTT_CONNECTED_BIT);

    for (;;){

    	vTaskDelay(10000 / portTICK_RATE_MS);  //send every 10 seconds

    	if ((rc = MQTTIsConnected(&client)) != 1) {
    		printf("MQTT Client - Connection - Connected check failed with error code %d.\n", rc);
    		goto fail1;
    	}
    }

fail1:
	
	xEventGroupClearBits(mqttEventGroup, MQTT_CONNECTED_BIT);

	MQTTDisconnect(&client);

fail2:
	
	printf("MQTT Client - Connection - Reconnecting.\n");

	goto reconnect;
    // printf("mqtt_client_thread going to be deleted\n");
    // vTaskDelete(NULL);
    // return;
}

void mqttInt(){

	mqttEventGroup = xEventGroupCreate();

	xTaskCreate(&mqttTask, "mqtt", 2048, NULL, 9, NULL);
}