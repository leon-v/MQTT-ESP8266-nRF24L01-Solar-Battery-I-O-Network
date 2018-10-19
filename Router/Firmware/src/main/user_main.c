#include <nvs_flash.h>
#include <nvs.h>
#include <string.h>
#include <driver/gpio.h>

#include "beeline.h"

#include "wifi.h"
#include "wifi_access_point.h"
#include "wifi_client.h"

#include "http.h"
#include "mqtt_connection.h"
#include "radio.h"

void app_main() {

	esp_err_t espError;
	
    //Initialize NVS
	espError = nvs_flash_init();

    if (espError == ESP_ERR_NVS_NO_FREE_PAGES) {
		ESP_ERROR_CHECK(nvs_flash_erase());
      	ESP_ERROR_CHECK(nvs_flash_init());
	}

	beelineInit();

	// Setup config button
	gpio_config_t io_conf;
    io_conf.intr_type = GPIO_PIN_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (0b1 << 0);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);

    ets_delay_us(1000000);

    wifiInit();

    if (gpio_get_level(0)){
    	wifiClientInit();
    }
    else{

    	// Reset all NVS data so we always get known values and don't crash
    	wifiClientResetNVS();
    	mqttConnectionResetNVS();

    	wifiAccessPointInit();
    }

    httpServerInit();
    mqttClientInit();

    radioInit();
}