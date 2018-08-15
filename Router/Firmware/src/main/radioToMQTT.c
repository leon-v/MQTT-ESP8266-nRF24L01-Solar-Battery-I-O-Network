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

	radioToMQTTTaskHandle = xTaskGetCurrentTaskHandle();

	MQTTClient * client = mqttGetClient();

	xEventGroupWaitBits(mqttGetEventGroup(), MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);

	MQTTMessage message;
    char mqttTopic[32];
    int rc = 0;

	message.qos = QOS2;
    message.retained = 0;

    char * name;
    char * sensor;
    char * value;

	uint32_t notifyValue;
    for (;;) {

    	xTaskNotifyWait(0, 0, &notifyValue, portMAX_DELAY);

    	name = strtok(payloadOut, "/");
		sensor = strtok(NULL, "/");
		value = strtok(NULL, "/");

		sprintf(mqttTopic, "%s/%s", name, sensor);
		
		message.payload = value;

		message.payloadlen = strlen(message.payload);

    	if ((rc = MQTTPublish(client, &mqttTopic, &message)) != 0) {
	        printf("Return code from MQTT publish is %d\n", rc);
	    }
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