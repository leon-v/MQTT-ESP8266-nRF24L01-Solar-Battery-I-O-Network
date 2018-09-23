#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "radio.h"

static xQueueHandle elasticPublishQueue = NULL;

xQueueHandle elasticGetPublishQueue(void){
	return elasticPublishQueue;
}

static void elasticPublishTask(void *arg){

	radioMessage_t radioMessage;

	for (;;){

		if (xQueueReceive(elasticPublishQueue, &radioMessage, 1000 / portTICK_RATE_MS)){

			// Got message
			printf("Elastic Send %s/%s/%s\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
		}

	}
}


void elasticInit(void){

	elasticPublishQueue = xQueueCreate(256, sizeof(radioMessage_t));

	xTaskCreate(&elasticPublishTask, "elasticPublishTask", 2048, NULL, 14, NULL);
}