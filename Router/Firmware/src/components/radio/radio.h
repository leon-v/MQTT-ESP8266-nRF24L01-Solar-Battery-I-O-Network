#ifndef RADIO_H_
#define	RADIO_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "beeline.h"

void radioInit(void);
xQueueHandle radioGetInterruptQueue(void);
xQueueHandle radioGetRXQueue(void);
beelineMessage_t radioGetStatus(void);

#endif //RADIO_H_