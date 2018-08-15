/* Simple WiFi Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include "nvs_flash.h"

#include "wifi.h"
#include "wifiAccessPoint.h"
#include "httpServer.h"
#include "wifiClient.h"
#include "configFlash.h"
#include "mqtt.h"
#include "radio.h"
#include "radioToMQTT.h"

void app_main() {
    //Initialize NVS
	esp_err_t ret = nvs_flash_init();

    if (ret == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK(nvs_flash_erase());
      	ret = nvs_flash_init();
	}
    ESP_ERROR_CHECK(ret);

    configFlashInit();

    configFlashSave();


    wifiInit();

    unsigned char configMode = 0;
    if (configMode){
		wifiAccessPointInit();
    }
    else{
		wifiClientInit();
    }

    mqttInt();

    radioInit();
    radioToMQTTInit();
    

    httpServerInit();
}
