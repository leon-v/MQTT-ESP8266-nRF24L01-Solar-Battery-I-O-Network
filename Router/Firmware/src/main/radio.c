#include "nrf24l01.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "radio.h"
#include "radioToMQTT.h"

static xQueueHandle radioEventQueue = NULL;

xQueueHandle radioGetEventQueue(void){
	return radioEventQueue;
}

int forwardCount = 0;
int radioTimerTick = 60;

static void radioInterruptTask(void *arg){
    uint32_t gp_io;

    printf("Radio - Interrupt Task - Stated.\n");

    for (;;) {

        if (xQueueReceive(radioEventQueue, &gp_io, portMAX_DELAY)) {

			nrf24l01ISR();

    		if (status.RX == RXReady){

    			nrf24l01Packet_t * RXPacket = nrf24l01GetRXPacket();

    			
    			radioToMQTTForward(RXPacket->Message);

    			forwardCount++;

				status.RX = RXIdle;
			}
    	}
    }
}

static void radioTimerTask(void *arg){

	for (;;) {

		nrf24l01ISR();

		nrf24l01Service();

		nrf24l01SetRXMode(1);

	    vTaskDelay( (radioTimerTick * 1000) / portTICK_RATE_MS);

	    printf("Radio - Forwarded %d messages in the last %d seconds.\n", forwardCount, radioTimerTick);

	    forwardCount = 0;
	}
}

void radioInit(void){

	printf("Radio - Initialisation - Start.\n");

	//create a queue to handle gpio event from isr
    radioEventQueue = xQueueCreate(4, sizeof(uint32_t));

	
    xTaskCreate(&radioInterruptTask, "radioInterruptTask", 2048, NULL, 10, NULL);

	printf("Radio - Initialisation - Initialising NRF24L01+\n");
	nrf24l01Init();
	printf("Radio - Initialisation - Initialised NRF24L01+\n");

	
    xTaskCreate(&radioTimerTask, "radioTimerTask", 1024, NULL, 5, NULL);
}