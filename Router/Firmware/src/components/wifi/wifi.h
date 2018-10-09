#ifndef WIFI_H_
#define WIFI_H_ 

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_DISCONNECTED_BIT BIT1

void wifiInit(void);

EventGroupHandle_t wifiGetEventGroup(void);

#endif /* WIFI_H_ */