#include "nrf24l01.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "radio.h"
#include "radioToMQTT.h"


static xQueueHandle radioInterruptQueue = NULL;
xQueueHandle radioGetInterruptQueue(void){
	return radioInterruptQueue;
}

static xQueueHandle radioRXQueue = NULL;
xQueueHandle radioGetRXQueue(void){
	return radioRXQueue;
}

static radioStatus_t radioStatus;
radioStatus_t radioGetStatus(void){
	return radioStatus;
}

int forwardCount = 0;

static void radioInterruptTask(void *arg){
    uint32_t gp_io;

    radioMessage_t radioRxMessage;


	nrf24l01Init();
	nrf24l01SetRXMode(1);


    printf("Radio - Task - Stated.\n");

    for (;;) {

        if (xQueueReceive(radioInterruptQueue, &gp_io, portMAX_DELAY)) {

			nrf24l01ISR();

    		if (status.RX == RXReady){

    			nrf24l01Packet_t * RXPacket = nrf24l01GetRXPacket();

    			// printf("Radio - Task - RX: %s\n", RXPacket->Message);

    			char * name = strtok(RXPacket->Message, "/");
		    	char * sensor = strtok(NULL, "/");
		    	char * value = strtok(NULL, "/");

		    	strcpy(radioRxMessage.name, name);
		    	strcpy(radioRxMessage.sensor, sensor);
		    	strcpy(radioRxMessage.value, value);

		    	xQueueSend(radioRXQueue, &radioRxMessage, 0);

    			radioStatus.messagesInAccum++;

				status.RX = RXIdle;
			}
    	}
    }
}

static void radioTimerTask(void *arg){

	for (;;) {

		nrf24l01ISR();

		nrf24l01Service();

	    vTaskDelay(60000 / portTICK_RATE_MS);

	    radioStatus.messagesInCount = radioStatus.messagesInAccum;
	    radioStatus.messagesInAccum = 0;

	    printf("Radio - Timer - Forwarded %d messages in the last 60 seconds.\n", radioStatus.messagesInCount);
	}
}

void radioInit(void){
	radioStatus.messagesInCount = 0;
	radioStatus.messagesInAccum = 0;

	//create a queue to handle gpio event from isr
    radioInterruptQueue = xQueueCreate(4, sizeof(uint32_t));

    radioRXQueue = xQueueCreate(4, sizeof(radioMessage_t));
	
    xTaskCreate(&radioInterruptTask, "radioInterruptTask", 2048, NULL, 10, NULL);
	
    xTaskCreate(&radioTimerTask, "radioTimerTask", 2048, NULL, 9, NULL);
}