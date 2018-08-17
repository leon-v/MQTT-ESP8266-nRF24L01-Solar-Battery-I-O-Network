#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "mqtt.h"
#include "radio.h"

#define MOTIFY_FORWARD (1UL << 0)

TaskHandle_t radioToMQTTTaskHandle = NULL;

char payloadOut[32];

void radioToMQTTForward(char * payloadIn){

	if (radioToMQTTTaskHandle == NULL){
		return;
	}

	// char * payloadOut;
	// malloc(payloadOut, (strlen(payloadIn) + 1) * sizeof(char) );

	strcpy(payloadOut, payloadIn);

	uint32_t notifyValue = MOTIFY_FORWARD;
	xTaskNotify(radioToMQTTTaskHandle, notifyValue, eNoAction);
}


void radioToMQTTTask(){

	radioToMQTTTaskHandle = xTaskGetCurrentTaskHandle();

	MQTTClient * client = mqttGetClient();

	xEventGroupWaitBits(mqttGetEventGroup(), MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);

    int rc = 0;


	uint32_t notifyValue;
    for (;;) {

    	xTaskNotifyWait(0, 0, &notifyValue, portMAX_DELAY);

		char * name;
    	char * sensor;
    	char * value;

    	name = strtok(payloadOut, "/");
		sensor = strtok(NULL, "/");
		value = strtok(NULL, "/");

		char * mqttTopic = NULL;
		mqttTopic = malloc(64 * sizeof(char));
		sprintf(mqttTopic, "radio/out/%s/%s/%s", mqttGetUniqueID(), name, sensor);

		char * mqttValue = NULL;
		mqttValue = malloc( (strlen(value) + 1) * sizeof(char));
		strcpy(mqttValue, value);
		
		printf("MQTT Publish: %s. Value: %s\n", mqttTopic, mqttValue);

		MQTTMessage message;

		message.qos = QOS1;
    	message.retained = 0;
		message.payload = mqttValue;
		message.payloadlen = strlen(message.payload);

    	if ((rc = MQTTPublish(client, mqttTopic, &message)) != 0) {
	        printf("Return code from MQTT publish is %d\n", rc);
	    }

	    free(mqttTopic);
	    free(mqttValue);

	}
    // message.payload = payload;
    // sprintf(payload, "Hello World1");
    // message.payloadlen = strlen(payload);

    // if ((rc = MQTTPublish(client, "radio/value/me/yay", &message)) != 0) {
    //     printf("Return code from MQTT publish is %d\n", rc);
    // } else {
    //     printf("MQTT publish topic \"radio/status/me/tick\"\n");
    // }

    vTaskDelete(NULL);
    return;
}

void radioToMQTTInit(void){
	xTaskCreate(&radioToMQTTTask, "radioToMQTT", 2048, NULL, 9, NULL);
}