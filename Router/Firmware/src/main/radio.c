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

static void radioInterruptTask(void *arg){
    uint32_t gp_io;

    radioMessage_t radioRxMessage;
	nrf24l01Packet_t * RXPacket = nrf24l01GetRXPacket();

	char * name;
	char * sensor;
	char * value;

	nrf24l01Init();
	nrf24l01SetRXMode(1);


    printf("Radio - Task - Stated.\n");

    for (;;) {

        if (xQueueReceive(radioInterruptQueue, &gp_io, 100 / portTICK_RATE_MS)) {

        	printf("Int Start\n");

    		if (status.RX == RXReady){

    			printf("Radio - Task - Message: %s\n", RXPacket->Message);
    			printf("Radio - Task - ACK Request: %d\n", RXPacket->packetData.ACKRequest);
    			printf("Radio - Task - TX Count: %d\n", status.txCount);

    			name = strtok(RXPacket->Message, "/");

    			if (name == NULL){
    				printf("Radio - Task - Invalid Name\n");
    				continue;
    			}

		    	sensor = strtok(NULL, "/");

		    	if (sensor == NULL){
    				printf("Radio - Task - Invalid Sensor\n");
    				continue;
    			}

		    	value = strtok(NULL, "/");

		    	if (value == NULL){
    				printf("Radio - Task - Invalid Value\n");
    				continue;
    			}

		    	strcpy(radioRxMessage.name, name);
		    	strcpy(radioRxMessage.sensor, sensor);
		    	strcpy(radioRxMessage.value, value);

		    	xQueueSend(radioRXQueue, &radioRxMessage, 0);

    			radioStatus.nrf24l01In++;

				status.RX = RXIdle;
			}
    	}else{
    		nrf24l01ISR();
    		nrf24l01SetRXMode(1);
    	}
    }
}

void radioInit(void){

	//create a queue to handle gpio event from isr
    radioInterruptQueue = xQueueCreate(8, sizeof(uint32_t));

    radioRXQueue = xQueueCreate(32, sizeof(radioMessage_t));
	
    xTaskCreate(&radioInterruptTask, "radioInterruptTask", 2048, NULL, 14, NULL);
}