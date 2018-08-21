#ifndef RADIO_H_
#define	RADIO_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

typedef struct{
	char name[16];
	char sensor[16];
	char value[16];
} radioMessage_t;

typedef struct{
	unsigned int messagesInCount;
	unsigned int messagesInAccum;
	unsigned long messagesInTotal;
} radioStatus_t;

void radioInit(void);
xQueueHandle radioGetInterruptQueue(void);
xQueueHandle radioGetRXQueue(void);
radioStatus_t radioGetStatus(void);

#endif //RADIO_H_
