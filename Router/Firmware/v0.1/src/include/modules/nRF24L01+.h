#ifndef NRF24L01_H_
#define NRF24L01_H_


//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 83

void ICACHE_FLASH_ATTR nrf24l01Init(MQTT_Client* p_mqttClient);
void ICACHE_FLASH_ATTR nrf24l01Pause(void);
void ICACHE_FLASH_ATTR nrf24l01Unpause(void);


#endif /* USER_CONFIG_H_ */


