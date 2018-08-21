#include "wifi.h"
#include "wifiClient.h"
#include "configFlash.h"

static const char *TAG = "wifiClient";

void wifiClientInit(void) {

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "",
            .password = ""
        },
    };

    memcpy(wifi_config.sta.ssid, configFlash.wifiSSID, strlen(configFlash.wifiSSID));
    memcpy(wifi_config.sta.password, configFlash.wifiPassword, strlen(configFlash.wifiPassword));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    ESP_LOGI(TAG, "wifi_init_sta finished.");
    ESP_LOGI(TAG, "connect to ap SSID:'%s', Password:'%s'", configFlash.wifiSSID, configFlash.wifiPassword);
}