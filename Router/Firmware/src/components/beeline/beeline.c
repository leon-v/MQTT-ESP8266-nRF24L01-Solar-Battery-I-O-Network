#include <freertos/FreeRTOS.h>
#include <freertos/event_groups.h>

static EventGroupHandle_t beelineEventGroup;

EventGroupHandle_t beelineGetEventGroup(void){
	return beelineEventGroup;
}

void beelineInit(void){
	beelineEventGroup = xEventGroupCreate();
}