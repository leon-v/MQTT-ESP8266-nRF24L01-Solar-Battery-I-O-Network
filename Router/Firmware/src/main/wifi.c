#include "wifi.h"


/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifiEventGroup;

void wifiInit(void) {
	wifiEventGroup = xEventGroupCreate();
}

EventGroupHandle_t wifiGetEventGroup(void){
	return wifiEventGroup;
}



// void wifiStationScanDone(void *arg, int status){

// 	struct bss_info *bss = (struct bss_info *) arg;

//     while (bss != NULL) {

//         if (bss->channel != 0) {

//             struct router_info *info = NULL;
//             os_printf("ssid %s, channel %d, authmode %d, rssi %d\n", bss->ssid, bss->channel, bss->authmode, bss->rssi);
//         }
//         bss = bss->next.stqe_next;
//     }
// }

// void wifiStationScanStart(void){

// 	wifi_set_opmode(STATION_MODE);
// 	wifi_station_set_auto_connect(0);

// 	wifi_station_scan(NULL, wifiStationScanDone);
// }