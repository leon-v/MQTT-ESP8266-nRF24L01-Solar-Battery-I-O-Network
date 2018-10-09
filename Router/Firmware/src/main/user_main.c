#include "nvs_flash.h"
#include "driver/gpio.h"

#include "wifi.h"
#include "wifi_access_point.h"
#include "http.h"

void app_main() {
	
    //Initialize NVS
	esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK(nvs_flash_erase());
      	ret = nvs_flash_init();
	}
    ESP_ERROR_CHECK(ret);

    wifiInit();
    wifiAccessPointInit();

    httpServerInit();
}