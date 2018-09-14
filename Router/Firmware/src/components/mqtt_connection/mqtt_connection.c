#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "MQTTClient.h"

#include "mqtt_connection.h"
#include "configFlash.h"
#include "wifi.h"
#include "radio.h"
#include "esp_system.h"

#define TAG "mqtt_connection"

TaskHandle_t serviceTask = NULL;
TaskHandle_t connectionTask = NULL;
TaskHandle_t publishTask = NULL;

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t mqttEventGroup;

static xQueueHandle MQTTMessageQueue = NULL;
MQTTClient client;

char uniqueID[16];

mqttStatus_t mqttStatus = mqttStatus_r;

mqttStatus_t mqtt_connection_get_status(void){
	return mqttStatus;
}

EventGroupHandle_t mqttGetEventGroup(void){
	return mqttEventGroup;
}

char * mqttGetUniqueID(void){
	return uniqueID;
}

MQTTClient * mqttGetClient(void){
	return &client;
}

void mqtt_connection(){
    Network network;
    unsigned char sendbuf[80] = {0};
    unsigned char readbuf[80] = {0};
    int rc = 0;
    int count = 0;
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    char mqttTopic[64];
    char mqttClientID[64];
    Timer timer;
    TimerInit(&timer);

	radioMessage_t radioMessage;
	EventBits_t mqttEventBits;
	MQTTMessage message;


    printf("mqtt client thread starts\n");

    /* Wait for the callback to set the WIFI_CONNECTED_BIT in the
       event group.
    */
reconnect:

    printf("xEventGroupWaitBits ...\n");

    xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);
    
    ESP_LOGI(TAG, "Connected to AP");


	vTaskDelay(500 / portTICK_RATE_MS);  //send every 1 seconds

    printf("NetworkInit ...\n");
    NetworkInit(&network);

    printf("MQTTClientInit ...\n");
    MQTTClientInit(&client, &network, 1000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

    char* address = (char *) &configFlash.mqttHost;


    printf("NetworkConnect ...\n");
    if ((rc = NetworkConnect(&network, address, configFlash.mqttPort)) != 0) {
        printf("Return code from network connect %s:%d is %d\n", address, configFlash.mqttPort, rc);
        mqttStatus.connectionFail++;
        goto fail;
    }

    connectData.username.cstring = configFlash.mqttUsername;
    connectData.password.cstring = configFlash.mqttPassword;
    connectData.MQTTVersion = 4;

    sprintf(mqttClientID, "Beeline %s", uniqueID);
    connectData.clientID.cstring = mqttClientID;
    connectData.cleansession = 1;

    printf("MQTTConnect ...\n");
    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("Return code from MQTT connect is %d\n", rc);
        mqttStatus.connectionFail++;
        goto fail;
    }
	
	printf("MQTT Connected\n");

    mqttStatus.connected = 1;
    mqttStatus.connectionSuccess++;


	while (MQTTIsConnected(&client)) {

		rc = xQueueReceive(radioGetRXQueue(), &radioMessage, 10 / portTICK_RATE_MS);

		if (rc){

			strcpy(mqttTopic, "radio/out/");
			strcat(mqttTopic, uniqueID);
			strcat(mqttTopic, "/");
			strcat(mqttTopic, radioMessage.name);
			strcat(mqttTopic, "/");
			strcat(mqttTopic, radioMessage.sensor);

			message.qos = QOS1;
	    	message.retained = 0;
			message.payload = &radioMessage.value;
			message.payloadlen = strlen(message.payload);

	    	if ((rc = MQTTPublish(&client, mqttTopic, &message)) != 0) {
		        printf("Radio->MQTT - Task - Return code from MQTT publish is %d\n", rc);
		        continue;
		    }

	    	mqttStatus.Publish++;

	    	printf("mqtt radio: Publish: Name=%s, Sensor=%s, Value=%s.\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
		}


		// Add sender queue here !
		TimerCountdownMS(&timer, 10); /* Don't wait too long if no traffic is incoming */

		MutexLock(&client.mutex);

		cycle(&client, &timer);

		MutexUnlock(&client.mutex);
	}
	
	mqttStatus.connected = 0;
	
	printf("disconnecting network\n");

fail:
	
	vTaskDelay(500 / portTICK_RATE_MS);  //send every 1 seconds

	printf("Restaring loop\n");

	goto reconnect;
    printf("mqtt_client_thread going to be deleted\n");
    vTaskDelete(NULL);
    return;
}



void mqtt_connection_init(){

	uint8_t mac[6];
    esp_efuse_mac_get_default(mac);

	sprintf(uniqueID, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	MQTTMessageQueue = xQueueCreate(16, sizeof(radioMessage_t));

	xTaskCreate(&mqtt_connection, "mqtt_connection", 8192, NULL, 14, &connectionTask);
}