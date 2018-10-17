#ifndef CONFIG_H_
#define CONFIG_H_

#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>
#include <freertos/queue.h>

#define MAX_HTTP_SSI_KEY_LENGTH 32
#define MAX_HTTP_SSI_VALUE_LENGTH 128
#define MAX_CONFIG_STRING_LENGTH 64

typedef struct{
	char name[16];
	char sensor[16];
	char value[16];
} beelineMessage_t;

void beelineInit(void);
EventGroupHandle_t beelineGetEventGroup(void);

#define WIFI_CONNECTED_BIT BIT0
#define MQTT_CONNECTED_BIT BIT1

#endif