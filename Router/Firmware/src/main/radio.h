#ifndef RADIO_H_
#define	RADIO_H_

typedef struct{
	char name[16];
	char sensor[16];
	char value[16];
} radioMessage_t;

typedef struct{
	unsigned int messagesInCount;
	unsigned int messagesInAccum;
} radioStatus_t;

void radioInit(void);
xQueueHandle radioGetInterruptQueue(void);
xQueueHandle radioGetRXQueue(void);

#endif //RADIO_H_
