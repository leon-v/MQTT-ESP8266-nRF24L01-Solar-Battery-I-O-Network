#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"


#include "configFlash.h"
#include "mqtt.h"
#include "radio.h"

#include "radioToMQTT.h"

static radioToMQTTStatus_t radioToMQTTStatus;

radioToMQTTStatus_t radioToMQTTGetStatus(void){
	return radioToMQTTStatus;
}

void radioToMQTTTask(){

	MQTTClient * client = mqttGetClient();

	int rc = 0;
	radioMessage_t radioMessage;
	char mqttTopic[64];
	EventBits_t mqttEventBits;

	configASSERT();

	for (;;) {

		if (xQueueReceive(radioGetRXQueue(), &radioMessage, portMAX_DELAY)) {

			mqttEventBits = xEventGroupWaitBits(mqttGetEventGroup(), MQTT_CONNECTED_BIT, false, true, 0);

			if (mqttEventBits & MQTT_CONNECTED_BIT){

				strcpy(mqttTopic, "radio/out/");
				strcat(mqttTopic, mqttGetUniqueID());
				strcat(mqttTopic, "/");
				strcat(mqttTopic, radioMessage.name);
				strcat(mqttTopic, "/");
				strcat(mqttTopic, radioMessage.sensor);

	    		MQTTMessage message;

				message.qos = QOS1;
		    	message.retained = 0;
				message.payload = &radioMessage.value;
				message.payloadlen = strlen(message.payload);

		    	if ((rc = MQTTPublish(client, mqttTopic, &message)) != 0) {
		    		if (configFlash.debugLevel > 1){
			        	printf("Radio->MQTT - Task - Return code from MQTT publish is %d\n", rc);
			    	}
			    }

			    else{

			    	radioToMQTTStatus.messagesOutAccum++;

			    	if (configFlash.debugLevel > 2){
			    		printf("Radio->MQTT - Task - Publish: Name=%s, Sensor=%s, Value=%s.\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
			    	}
			    }
			    
			}
			else{

				radioToMQTTStatus.messagesDumpAccum++;

				if (configFlash.debugLevel > 2){
					printf("Radio->MQTT - Task - Dump: Name=%s, Sensor=%s, Value=%s.\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
				}
			}

    		

    	}

	}	

    vTaskDelete(NULL);
    return;
}


void radioToMQTTTimerTask(){

	for(;;){
		vTaskDelay(60000 / portTICK_RATE_MS);

	    radioToMQTTStatus.messagesOutCount = radioToMQTTStatus.messagesOutAccum;
	    radioToMQTTStatus.messagesOutTotal+= radioToMQTTStatus.messagesOutAccum;
	    radioToMQTTStatus.messagesOutAccum = 0;

	    radioToMQTTStatus.messagesDumpCount = radioToMQTTStatus.messagesDumpAccum;
	    radioToMQTTStatus.messagesDumpTotal+= radioToMQTTStatus.messagesDumpAccum;
	    radioToMQTTStatus.messagesDumpAccum = 0;

	    printf("Radio->MQTT - Timer - Sent %d, Dumped %d messages in the last 60 seconds.\n", radioToMQTTStatus.messagesOutCount, radioToMQTTStatus.messagesDumpCount);
	}
	
	vTaskDelete(NULL);
    return;
}


void radioToMQTTInit(void){
	radioToMQTTStatus.messagesOutCount = 0;
	radioToMQTTStatus.messagesOutAccum = 0;
	radioToMQTTStatus.messagesOutTotal = 0;

	radioToMQTTStatus.messagesDumpCount = 0;
	radioToMQTTStatus.messagesDumpAccum = 0;
	radioToMQTTStatus.messagesDumpTotal = 0;
	

	xTaskCreate(&radioToMQTTTask, "radioToMQTT", 2048, NULL, 10, NULL);

	xTaskCreate(&radioToMQTTTimerTask, "radioMQTTTimer", 2048, NULL, 9, NULL);
}