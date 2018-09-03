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




    printf("mqtt client thread starts\n");

    /* Wait for the callback to set the WIFI_CONNECTED_BIT in the
       event group.
    */

    printf("xEventGroupWaitBits ...\n");
    xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);
    ESP_LOGI(TAG, "Connected to AP");

reconnect:

    printf("NetworkInit ...\n");
    NetworkInit(&network);

    printf("MQTTClientInit ...\n");
    MQTTClientInit(&client, &network, 1000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

    char* address = (char *) &configFlash.mqttHost;


    printf("NetworkConnect ...\n");
    if ((rc = NetworkConnect(&network, address, configFlash.mqttPort)) != 0) {
        printf("Return code from network connect %s:%d is %d\n", address, configFlash.mqttPort, rc);
        goto fail;
    }

    connectData.username.cstring = configFlash.mqttUsername;
    connectData.password.cstring = configFlash.mqttPassword;
    connectData.MQTTVersion = 4;

    sprintf(mqttClientID, "Beeline %s", uniqueID);
    connectData.clientID.cstring = mqttClientID;
    connectData.cleansession = 1;

    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("Return code from MQTT connect is %d\n", rc);
        goto fail_has_network;
    } else {
        printf("MQTT Connected\n");
    }

    #if defined(MQTT_TASK)

    if ((rc = MQTTStartTask(&client)) != pdPASS) {
        printf("Return code from start tasks is %d\n", rc);
        goto fail_has_network;
    } else {
        printf("Use MQTTStartTask\n");
    }

	#endif

    while (++count) {
        MQTTMessage message;
        char payload[30];


        message.qos = QOS2;
        message.retained = 0;
        sprintf(payload, "%d", count);
        message.payload = payload;
        message.payloadlen = strlen(payload);

        strcpy(mqttTopic, "radio/out/");
		strcat(mqttTopic, uniqueID);
		strcat(mqttTopic, "/Router/Count");

        if ((rc = MQTTPublish(&client, mqttTopic, &message)) != 0) {
            printf("Return code from MQTT publish is %d\n", rc);
        } else {
            printf("MQTT publish topic \"%s\", message number is %d\n", mqttTopic, count);
        }

        if (!MQTTIsConnected(&client)){
        	printf("MQTT Not Connected\n");
        	goto fail;
        }

        vTaskDelay(10000 / portTICK_RATE_MS);  //send every 1 seconds
    }

fail_has_network:
	
	printf("disconnecting network\n");

	network.disconnect(&network);

fail:
	
	vTaskDelay(2000 / portTICK_RATE_MS);  //send every 1 seconds

	printf("Restaring loop\n");

	goto reconnect;
    printf("mqtt_client_thread going to be deleted\n");
    vTaskDelete(NULL);
    return;
}


/*
void MQTTRun(void* parm)
{
    Timer timer;
    MQTTClient* c = (MQTTClient*)parm;
    int rc = 0;

    TimerInit(&timer);

    while (1) {
        TimerCountdownMS(&timer, 500); // Don't wait too long if no traffic is incoming

#if defined(MQTT_TASK)
        MutexLock(&c->mutex);
#endif
        rc = cycle(c, &timer);
#if defined(MQTT_TASK)
        MutexUnlock(&c->mutex);
#endif
        if (rc < 0){
        	break;
        }

    }

    vTaskDelete(NULL);
    return;
}
*/

void mqtt_connection_send_task(){

	int rc = 0;
	radioMessage_t radioMessage;
	char mqttTopic[64];
	EventBits_t mqttEventBits;
	MQTTMessage message;

	for (;;) {

		if (!xQueueReceive(radioGetRXQueue(), &radioMessage, portMAX_DELAY)) {
			printf("mqtt radio: Queue wait time out, restart listen.\n");
			continue;
		}

		if (!MQTTIsConnected(&client)){
			printf("mqtt radio: Dump: Name=%s, Sensor=%s, Value=%s.\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
			mqttStatus.Dump++;
			continue;
		}

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

    vTaskDelete(NULL);
    return;
}


void mqtt_connection_init(){

	uint8_t mac[6];
    esp_efuse_mac_get_default(mac);

	sprintf(uniqueID, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	MQTTMessageQueue = xQueueCreate(16, sizeof(radioMessage_t));

	xTaskCreate(&mqtt_connection, "mqtt_connection", 8192, NULL, 9, &connectionTask);

	xTaskCreate(&mqtt_connection_send_task, "mqtt_connection_send_task", 8192, NULL, 10, &publishTask);
}