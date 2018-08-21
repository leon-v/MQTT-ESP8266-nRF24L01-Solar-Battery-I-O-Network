/* Simple WiFi Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <string.h>
#include "nvs_flash.h"
//#include "rom/ets_sys.h"
#include "driver/gpio.h"

#include "wifi.h"
#include "wifiAccessPoint.h"
// #include "httpServer.h"
#include "wifiClient.h"
#include "configFlash.h"
#include "mqtt.h"
#include "radio.h"
#include "radioToMQTT.h"

#include "user_main.h"
#include "lwip/apps/httpd.h"
#include "lwip/apps/fs.h"

#define CONFIG_BUTTON_PIN 2

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

    unsigned char apMode = 0;

    // Check if we have an SSID and go to AP mode if not;
    if (strlen(configFlash.wifiSSID) == 0){
    	apMode = 1;
    }

    // Check if GPIO2 is getting a button press
    // Configure Inputs
	gpio_config_t inputs;
	inputs.pin_bit_mask	= (1ULL << CONFIG_BUTTON_PIN);
	inputs.mode			= GPIO_MODE_INPUT;
	inputs.pull_up_en	= GPIO_PULLUP_ENABLE;
	inputs.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	inputs.intr_type	= GPIO_INTR_DISABLE;
	gpio_config(&inputs);

	// Check if button pressed down and shorting pin
	if (!gpio_get_level(CONFIG_BUTTON_PIN)){
		apMode = 1;
	}
    
    if (apMode){
		wifiAccessPointInit();		
    }
    else{
		wifiClientInit();
	    
    }

    httpd_init();

    radioInit();
    mqttInt();
    
    radioToMQTTInit();
    // httpServerInit();
    
}

static char body[] = "this is leons test body";
int fs_open_custom(struct fs_file *file, const char *name){

	
	if (strcmp(name, "index.html")){
		file = &body;
		return 1;
	}

	return 0;
}

void fs_close_custom(struct fs_file *file){


}