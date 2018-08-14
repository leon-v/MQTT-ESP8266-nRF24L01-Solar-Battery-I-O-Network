#include "mqtt.h"

#define RADIO_TO_MQTT_THREAD_STACK_WORDS  1024
#define RADIO_TO_MQTT_THREAD_PRIO         8

void radioToMQTTTask(){

	printf("radioToMQTTTas thread starts\n");

	MQTTClient * client = mqttGetClient();

	xEventGroupWaitBits(mqttGetEventGroup(), MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);


	MQTTMessage message;
    char payload[30];
    int rc = 0;

	message.qos = QOS2;
    message.retained = 0;
    message.payload = payload;
    sprintf(payload, "Hello World1");
    message.payloadlen = strlen(payload);

    if ((rc = MQTTPublish(client, "radio/value/me/yay", &message)) != 0) {
        printf("Return code from MQTT publish is %d\n", rc);
    } else {
        printf("MQTT publish topic \"radio/status/me/tick\"\n");
    }

    vTaskDelete(NULL);
    return;
}

void radioToMQTTInit(){

	xTaskCreate(&radioToMQTTTask, "radioToMQTT", RADIO_TO_MQTT_THREAD_STACK_WORDS, NULL, RADIO_TO_MQTT_THREAD_PRIO, NULL);

}