#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


#include "mqtt.h"
#include "radio.h"

#include "radioToMQTT.h"

radioToMQTTStatus_t radioToMQTTStatus;

radioToMQTTStatus_t radioToMQTTGetStatus(void){
	return radioToMQTTStatus;
}

void radioToMQTTTask(){

	// radioToMQTTTaskHandle = xTaskGetCurrentTaskHandle();

	MQTTClient * client = mqttGetClient();

	xEventGroupWaitBits(mqttGetEventGroup(), MQTT_CONNECTED_BIT, false, true, portMAX_DELAY);

    int rc = 0;
	radioMessage_t radioMessage;
	char mqttTopic[64];

    for (;;) {

    	if (xQueueReceive(radioGetRXQueue(), &radioMessage, portMAX_DELAY)) {

    		sprintf(mqttTopic, "radio/out/%s/%s/%s", mqttGetUniqueID(), radioMessage.name, radioMessage.sensor);

    		MQTTMessage message;

			message.qos = QOS1;
	    	message.retained = 0;
			message.payload = &radioMessage.value;
			message.payloadlen = strlen(message.payload);

	    	if ((rc = MQTTPublish(client, mqttTopic, &message)) != 0) {
		        printf("Radio->MQTT - Task - Return code from MQTT publish is %d\n", rc);
		    }

		    radioToMQTTStatus.messagesOutAccum++;

		    // printf("Radio->MQTT - Task - Publish: %s. Value: %s\n", mqttTopic, (char *) message.payload);

    	}

	}
    vTaskDelete(NULL);
    return;
}


void radioToMQTTTimerTask(){

	vTaskDelay(60000 / portTICK_RATE_MS);

    radioToMQTTStatus.messagesOutCount = radioToMQTTStatus.messagesOutAccum;
    radioToMQTTStatus.messagesOutAccum = 0;

    printf("Radio->MQTT - Timer Forwarded %d messages in the last 60 seconds.\n", radioToMQTTStatus.messagesOutCount);
}


void radioToMQTTInit(void){
	xTaskCreate(&radioToMQTTTask, "radioToMQTT", 2048, NULL, 10, NULL);

	// xTaskCreate(&radioToMQTTTimerTask, "radioToMQTTTimerTask", 2048, NULL, 7, NULL);
}