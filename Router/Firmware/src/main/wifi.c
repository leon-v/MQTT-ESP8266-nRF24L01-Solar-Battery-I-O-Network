#include "wifi.h"


/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifiEventGroup;

static const char *TAG = "wifi";

static esp_err_t wifiEventHandler(void *ctx, system_event_t *event){

	switch(event->event_id) {

		case SYSTEM_EVENT_STA_START:
        	esp_wifi_connect();
        	break;

    	case SYSTEM_EVENT_STA_GOT_IP:
        	ESP_LOGI(TAG, "got ip:%s", ip4addr_ntoa(&event->event_info.got_ip.ip_info.ip));
        	xEventGroupSetBits(wifiEventGroup, WIFI_CONNECTED_BIT);
        break;

        case SYSTEM_EVENT_STA_DISCONNECTED:
        	esp_wifi_connect();
        	xEventGroupClearBits(wifiEventGroup, WIFI_CONNECTED_BIT);
        break;

		case SYSTEM_EVENT_AP_STACONNECTED:
			xEventGroupSetBits(wifiEventGroup, WIFI_CONNECTED_BIT);
			ESP_LOGI(TAG, "station:"MACSTR" join, AID=%d", MAC2STR(event->event_info.sta_connected.mac), event->event_info.sta_connected.aid);
			break;

		case SYSTEM_EVENT_AP_STADISCONNECTED:
			ESP_LOGI(TAG, "station:"MACSTR" leave, AID=%d", MAC2STR(event->event_info.sta_disconnected.mac), event->event_info.sta_disconnected.aid);
			break;

		default:
		break;
	}

	return ESP_OK;
}

void wifiInit(void) {

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