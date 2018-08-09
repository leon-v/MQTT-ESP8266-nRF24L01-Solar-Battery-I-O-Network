#include "esp_log.h"
#include "esp_event_loop.h"

#include "wifi.h"
#include "wifiAccessPoint.h"

#define WIFI_AP_SSID "ESP8266 V-Sensor Config Mode"

static const char *TAG = "wifiAccessPoint";

static esp_err_t wifiAccessPointEventHandler(void *ctx, system_event_t *event){
	switch(event->event_id) {
		case SYSTEM_EVENT_STA_START:
			esp_wifi_connect();
			break;

		case SYSTEM_EVENT_AP_STACONNECTED:
			xEventGroupSetBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT);
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

void wifiAccessPointInit(void) {

    tcpip_adapter_init();

    ESP_ERROR_CHECK(esp_event_loop_init(wifiAccessPointEventHandler, NULL));

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
    	.ap = {
	        .ssid = WIFI_AP_SSID,
	        .ssid_len = strlen(WIFI_AP_SSID),
	        .max_connection = 1
		},
    };

    wifi_config.ap.authmode = WIFI_AUTH_OPEN;

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));

    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_AP, &wifi_config));

    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifiAccessPointInit finished.SSID:%s", WIFI_AP_SSID);
}