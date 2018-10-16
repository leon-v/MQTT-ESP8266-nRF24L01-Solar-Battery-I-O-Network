#include "nvs_flash.h"
#include <nvs.h>
#include <string.h>
#include "driver/gpio.h"

#include "wifi.h"
#include "wifi_access_point.h"
#include "wifi_client.h"

#include "http.h"

void app_main() {

	esp_err_t espError;
	
    //Initialize NVS
	espError = nvs_flash_init();

    if (espError == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK(nvs_flash_erase());
      	ESP_ERROR_CHECK(nvs_flash_init());
	}

	

    wifiInit();
    // wifiAccessPointInit();
    wifiClientInit();

    httpServerInit();

}