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

static void radioInterruptTask(void *arg){
    uint32_t gp_io;

    for (;;) {


        if (xQueueReceive(radioEventQueue, &gp_io, portMAX_DELAY)) {

			nrf24l01ISR();

    		if (status.RX == RXReady){

    			nrf24l01Packet_t * RXPacket = nrf24l01GetRXPacket();

    			radioToMQTTForward(RXPacket->Message);

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
	    vTaskDelay(1000 / portTICK_RATE_MS);
	}
}

void radioInit(void){

	//create a queue to handle gpio event from isr
    radioEventQueue = xQueueCreate(4, sizeof(uint32_t));

	
    xTaskCreate(&radioInterruptTask, "radioInterruptTask", 2048, NULL, 10, NULL);

	printf("Initialising Radio....");
	nrf24l01Init();
	printf("OK\n");

	
    xTaskCreate(&radioTimerTask, "radioTimerTask", 1024, NULL, 5, NULL);
}