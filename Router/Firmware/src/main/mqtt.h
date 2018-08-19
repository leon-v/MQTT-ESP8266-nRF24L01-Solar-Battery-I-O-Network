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

MQTTClient * mqttGetClient(void);
EventGroupHandle_t mqttGetEventGroup(void);
char * mqttGetUniqueID(void);

void mqttInt();

#endif //RADIO_MQTT_ROUTER_H_