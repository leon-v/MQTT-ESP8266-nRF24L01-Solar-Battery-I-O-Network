#ifndef RADIO_MQTT_ROUTER_H_
#define RADIO_MQTT_ROUTER_H_

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "MQTTClient.h"

#define MQTT_CONNECTED_BIT BIT0

typedef struct{
	unsigned int connectionSuccessCount;
	unsigned int connectionFailCount;
} mqttStatus_t;

#define mqttStatus_r {0, 0}

MQTTClient * mqttGetClient(void);
EventGroupHandle_t mqttGetEventGroup(void);
char * mqttGetUniqueID(void);
mqttStatus_t mqttGetStatus(void);

void mqttInt();

#endif //RADIO_MQTT_ROUTER_H_