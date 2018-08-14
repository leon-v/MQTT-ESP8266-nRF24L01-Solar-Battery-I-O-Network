
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "mqtt.h"
#include "configFlash.h"
#include "wifi.h"

#define MQTT_TASK 1
#define MQTT_CLIENT_THREAD_STACK_WORDS  2048
#define MQTT_CLIENT_THREAD_PRIO         8

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

    printf("mqtt client thread starts\n");

	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	vTaskDelay(1000 / portTICK_RATE_MS);  //send every 1 seconds

	NetworkInit(&network);

	MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

    char* address = "valkenb.org";

    if ((rc = NetworkConnect(&network, address, 1883)) != 0) {
        printf("Return code from network connect is %d\n", rc);
        goto fail2;
    }

    #if defined(MQTT_TASK)

    if ((rc = MQTTStartTask(&client)) != pdPASS) {
        printf("Return code from start tasks is %d\n", rc);
        goto fail1;
    } else {
        printf("Use MQTTStartTask\n");
    }

	#endif

    connectData.MQTTVersion = 4; // 3 = 3.1 4 = 3.1.1
    connectData.clientID.cstring = "NRF24L01+ Router ESP8266 TestH";
    //sprintf(connectData.clientID.cstring, "NRF24L01+ Router ESP8266 %u", system_get_chip_id());
    //connectData.clientID.lenstring = strlen(connectData.clientID.cstring);
    // connectData.keepAliveInterval = 30;
    // connectData.cleansession = 0;
    connectData.username.cstring = "mqtt";
    connectData.password.cstring = "mqttgrl7";

    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("Return code from MQTT connect is %d\n", rc);
        goto fail1;
    }
	
	printf("MQTT Connected\n");

	xEventGroupSetBits(mqttEventGroup, MQTT_CONNECTED_BIT);

    unsigned int tick = 0;
    while (true){

    	vTaskDelay(1000 / portTICK_RATE_MS);  //send every 10 seconds

    	MQTTMessage message;
        char payload[30];

    	message.qos = QOS2;
        message.retained = 0;
        message.payload = payload;
        sprintf(payload, "%d", tick++);
        message.payloadlen = strlen(payload);

        if ((rc = MQTTPublish(&client, "radio/status/me/tick", &message)) != 0) {
            printf("Return code from MQTT publish is %d\n", rc);
        } else {
            printf("MQTT publish topic \"radio/status/me/tick\", message number is %d\n", tick);
        }

        vTaskDelay(1000 / portTICK_RATE_MS);  //send every 10 seconds

    	if ((rc = MQTTIsConnected(&client)) != 1) {
    		printf("Return from MQTTIsConnected is %d\n", rc);
    		goto fail1;
    	}
    }

fail1:
	
	xEventGroupClearBits(mqttEventGroup, MQTT_CONNECTED_BIT);

	MQTTDisconnect(&client);

fail2:

	goto reconnect;
    // printf("mqtt_client_thread going to be deleted\n");
    // vTaskDelete(NULL);
    // return;
}

void mqttInt(){

	mqttEventGroup = xEventGroupCreate();

	xTaskCreate(&mqttTask, "mqtt", MQTT_CLIENT_THREAD_STACK_WORDS, NULL, MQTT_CLIENT_THREAD_PRIO, NULL);
}