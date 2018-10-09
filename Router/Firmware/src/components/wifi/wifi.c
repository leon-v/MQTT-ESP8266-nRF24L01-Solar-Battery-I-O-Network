#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "rom/ets_sys.h"
#include "esp_wifi.h"
#include "esp_wifi_types.h"
#include "esp_event_loop.h"

#include "wifi.h"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifiEventGroup;

static esp_err_t wifiEventHandler(void *ctx, system_event_t *event){

	switch(event->event_id) {

		case SYSTEM_EVENT_STA_START:
			printf("WiFi - Event - Station start.\n");
        	esp_wifi_connect();
        	break;

    	case SYSTEM_EVENT_STA_GOT_IP:
    		printf("WiFi - Event - Got IP address: %s.\n", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        	xEventGroupSetBits(wifiEventGroup, WIFI_CONNECTED_BIT);
        	break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
        	printf("WiFi - Event - Station disconnected.\n");
        	esp_wifi_connect();
        	xEventGroupClearBits(wifiEventGroup, WIFI_CONNECTED_BIT);
        	break;

		case SYSTEM_EVENT_AP_STACONNECTED:
			printf("WiFi - Event - Client connected to out access point: "MACSTR".\n", MAC2STR(event->event_info.sta_connected.mac));
			xEventGroupSetBits(wifiEventGroup, WIFI_CONNECTED_BIT);
			break;

		case SYSTEM_EVENT_AP_STADISCONNECTED:
			printf("WiFi - Event - Client disconnected to out access point: "MACSTR".\n", MAC2STR(event->event_info.sta_disconnected.mac));
			break;

		default:
		break;
	}

	return ESP_OK;
}

void wifiInit(void) {

	printf("WiFi - Initialisation - Start.\n");

	wifiEventGroup = xEventGroupCreate();

	tcpip_adapter_init();

    ESP_ERROR_CHECK(esp_event_loop_init(wifiEventHandler, NULL));
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