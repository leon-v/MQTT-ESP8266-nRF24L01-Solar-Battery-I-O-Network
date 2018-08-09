#ifndef WIFI_H_
#define WIFI_H_ 

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "rom/ets_sys.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
#define WIFI_CONNECTED_BIT 1

void wifiInit(void);

EventGroupHandle_t wifiGetEventGroup(void);

#endif /* WIFI_H_ */