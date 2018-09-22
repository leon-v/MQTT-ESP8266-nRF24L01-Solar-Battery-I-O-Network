#include "nrf24l01.h"
#include "configFlash.h"
#include "radio.h"

static xQueueHandle radioInterruptQueue = NULL;
xQueueHandle radioGetInterruptQueue(void){
	return radioInterruptQueue;
}

static xQueueHandle radioRXQueue = NULL;
xQueueHandle radioGetRXQueue(void){
	return radioRXQueue;
}

static radioStatus_t radioStatus = radioStatus_r;
radioStatus_t radioGetStatus(void){
	return radioStatus;
}

int forwardCount = 0;

void rxCallback(nrf24l01Packet_t * rxPacket){

	radioMessage_t radioRxMessage;

	char * name;
	char * sensor;
	char * value;

	// printf("Radio - Task - Message: %s\n", rxPacket->Message);
	// printf("Radio - Task - ACK Request: %d\n", rxPacket->packetData.ACKRequest);
	// printf("Radio - Task - TX Count: %d\n", status.txCount);

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

	xQueueSend(radioRXQueue, &radioRxMessage, 0);

	radioStatus.nrf24l01In++;
}
static void radioInterruptTask(void *arg){
    uint32_t gp_io;

	nrf24l01Init();
	nrf24l01SetRXCallback(rxCallback);
	nrf24l01SetRXMode(1);


    printf("Radio - Task - Stated.\n");

    for (;;) {

        if (xQueueReceive(radioInterruptQueue, &gp_io, 10000 / portTICK_RATE_MS)) {
        	while (!gpio_get_level(gp_io)){
        		nrf24l01ISR();
        		delayUs(10);
        	}
        	
    	}
    }
}

void radioInit(void){

	//create a queue to handle gpio event from isr
    radioInterruptQueue = xQueueCreate(8, sizeof(uint32_t));

    radioRXQueue = xQueueCreate(32, sizeof(radioMessage_t));
	
    xTaskCreate(&radioInterruptTask, "radioInterruptTask", 2048, NULL, 14, NULL);
}