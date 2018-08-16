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

	strcpy(payloadOut, payloadIn);

	uint32_t notifyValue = MOTIFY_FORWARD;
	xTaskNotify(radioToMQTTTaskHandle, notifyValue, eNoAction);
}


void radioToMQTTTask(){

	MQTTMessage message;
	message.qos = QOS2;
    message.retained = 0;

    char mqttTopic[64];

    char * name;
    char * sensor;
    char * value;

    int rc = 0;

	uint32_t notifyValue;

	radioToMQTTTaskHandle = xTaskGetCurrentTaskHandle();

	MQTTClient * client = mqttGetClient();

	xEventGroupWaitBits(mqttGetEventGroup(), MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);

    for (;;) {

    	xTaskNotifyWait(0, 0, &notifyValue, portMAX_DELAY);

    	name = strtok(payloadOut, "/");
		sensor = strtok(NULL, "/");
		value = strtok(NULL, "/");

		sprintf(mqttTopic, "radio/out/%s/%s/%s", mqttGetUniqueID(), name, sensor);
		
		printf("MQTT Publish: %s. Value: %s\n", mqttTopic, value);
		message.payload = value;

		message.payloadlen = strlen(message.payload);

    	if ((rc = MQTTPublish(client, (char *) &mqttTopic, &message)) != 0) {
	        printf("Return code from MQTT publish is %d\n", rc);
	    }
	}

    vTaskDelete(NULL);
    return;
}

void radioToMQTTInit(void){
	xTaskCreate(&radioToMQTTTask, "radioToMQTT", 2048, NULL, 9, NULL);
}