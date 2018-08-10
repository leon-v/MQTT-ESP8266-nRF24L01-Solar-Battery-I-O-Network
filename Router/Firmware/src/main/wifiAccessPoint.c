#include "wifi.h"
#include "wifiAccessPoint.h"

#define WIFI_AP_SSID "ESP8266 V-Sensor Config Mode"

static const char *TAG = "wifiAccessPoint";

void wifiAccessPointInit(void) {

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