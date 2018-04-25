#include "nRF24L01+.h"
#include "spi.h"

LOCAL MQTT_Client* mqttClient;

void ICACHE_FLASH_ATTR nrf24l01Init(uint32_t *args){

	mqttClient = (MQTT_Client*) args;

	
}