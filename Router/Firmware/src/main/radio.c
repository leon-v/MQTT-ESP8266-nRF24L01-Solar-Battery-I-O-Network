#include "nrf24l01.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

void radioInit(void){

	nrf24l01Init();

	while (1) {

		nrf24l01SetRXMode(1);
        vTaskDelay(100 / portTICK_RATE_MS);
        

    }
}