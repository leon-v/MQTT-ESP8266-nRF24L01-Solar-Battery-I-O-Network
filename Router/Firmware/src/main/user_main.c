#include "nvs_flash.h"
#include <nvs.h>
#include <string.h>
#include "driver/gpio.h"

#include "wifi.h"
#include "wifi_access_point.h"
#include "http.h"

void app_main() {

	esp_err_t espError;
	
    //Initialize NVS
	espError = nvs_flash_init();

    if (espError == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK(nvs_flash_erase());
      	espError = nvs_flash_init();
	}
    ESP_ERROR_CHECK(espError);

    wifiInit();
    wifiAccessPointInit();

    httpServerInit();

    nvs_handle nvsHandle;
   	espError = nvs_open("BeelineNVS", NVS_READONLY, &nvsHandle);

   	if (espError != ESP_OK){
   		printf("nvs_open return %d\n", espError);
   		return;
   	}

   	char value[64];
   	size_t length;
   	espError = nvs_get_str(nvsHandle, "wifiSSID", value, &length);

   	if (espError != ESP_OK){
   		printf("nvs_get_str return %d\n", espError);
   		return;
   	}

   	printf("Length %d\n", length);
   	printf("wifiSSID From NVS : %s\n", value);

   	nvs_close(nvsHandle);
}