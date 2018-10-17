#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

#include "nrf24l01.h"
#include "beeline.h"

#include "mqtt_connection.h"

static xQueueHandle radioInterruptQueue = NULL;
xQueueHandle radioGetInterruptQueue(void){
	return radioInterruptQueue;
}

static xQueueHandle radioRXQueue = NULL;
xQueueHandle radioGetRXQueue(void){
	return radioRXQueue;
}

void radioRXxCallback(nrf24l01Packet_t * rxPacket){

	beelineMessage_t radioRxMessage;

	char * name;
	char * sensor;
	char * value;

	printf("Radio - Task - Message: %s\n", rxPacket->Message);
	printf("Radio - Task - ACK Request: %d\n", rxPacket->packetData.ACKRequest);
	printf("Radio - Task - TX Count: %d\n", status.txCount);

	name = strtok(rxPacket->Message, "/");

	if (name == NULL){
		printf("Radio - Task - Invalid Name\n");
		return;
	}

	sensor = strtok(NULL, "/");

	if (sensor == NULL){
		printf("Radio - Task - Invalid Sensor\n");
		return;
	}

	value = strtok(NULL, "/");

	if (value == NULL){
		printf("Radio - Task - Invalid Value\n");
		return;
	}

	strcpy(radioRxMessage.name, name);
	strcpy(radioRxMessage.sensor, sensor);
	strcpy(radioRxMessage.value, value);

	xQueueSend(getMQTTConnectionMessageQueue(), &radioRxMessage, 0);
}

static void radioInterruptTask(void *arg){
    uint32_t gp_io;

    printf("Radio - Task - nrf24l01Init.\n");
	nrf24l01Init();

	printf("Radio - Task - nrf24l01SetRXCallback.\n");
	nrf24l01SetRXCallback(radioRXxCallback);

	printf("Radio - Task - nrf24l01SetRXMode.\n");
	nrf24l01SetRXMode(1);


    printf("Radio - Task - Stated.\n");

    for (;;) {

        if (xQueueReceive(radioInterruptQueue, &gp_io, 10000 / portTICK_RATE_MS)) {

        	while (!gpio_get_level(gp_io)){
        		nrf24l01ISR();
        		delayUs(10);
        	}
        	
    	}

    	nrf24l01ISR();
    }
}

void radioInit(void){

	printf("Radio - Init - radioInterruptQueue.\n");

	//create a queue to handle gpio event from isr
    radioInterruptQueue = xQueueCreate(8, sizeof(uint32_t));

    printf("Radio - Init - radioRXQueue.\n");
    radioRXQueue = xQueueCreate(32, sizeof(beelineMessage_t));
		
	printf("Radio - Init - xTaskCreate.\n");
    xTaskCreate(&radioInterruptTask, "radioInterruptTask", 2048, NULL, 14, NULL);
}