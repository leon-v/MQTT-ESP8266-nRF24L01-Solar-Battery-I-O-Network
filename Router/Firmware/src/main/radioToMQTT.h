#ifndef RADIO_TO_MQTT_H_
#define RADIO_TO_MQTT_H_

typedef struct{
	unsigned int messagesOutCount;
	unsigned int messagesOutAccum;
	unsigned int messagesDumpCount;
	unsigned int messagesDumpAccum;
} radioToMQTTStatus_t;

void radioToMQTTInit(void);
radioToMQTTStatus_t radioToMQTTGetStatus(void);

#endif //RADIO_TO_MQTT_H_