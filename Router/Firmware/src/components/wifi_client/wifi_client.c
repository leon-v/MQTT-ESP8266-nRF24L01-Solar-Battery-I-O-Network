#include <esp_wifi.h>
#include <nvs.h>

#include "wifi.h"
#include "config.h"

void wifiClientInit(void) {

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

    wifi_config_t wifi_config = {
        .sta = {
            .ssid = "",
            .password = ""
        },
    };

    nvs_handle nvsHandle;
	ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READONLY, &nvsHandle));

	size_t nvsLength;

	nvsLength = MAX_CONFIG_STRING_LENGTH;
	nvs_get_str(nvsHandle, "wifiSSID", (char *) wifi_config.sta.ssid, &nvsLength);

    nvsLength = MAX_CONFIG_STRING_LENGTH;
    nvs_get_str(nvsHandle, "wifiPassword", (char *) wifi_config.sta.password, &nvsLength);

    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());

    printf ("WiFI connect to ap \n");
}