#include <esp_wifi.h>

#include "wifi.h"

void wifiClientInit(void) {

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "V2.4Ghz",
            .password = "wifigrl7"
        },
    };

    // memcpy(wifi_config.sta.ssid, configFlash.wifiSSID, strlen(configFlash.wifiSSID));
    // memcpy(wifi_config.sta.password, configFlash.wifiPassword, strlen(configFlash.wifiPassword));

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf ("WiFI connect to ap \n");
}