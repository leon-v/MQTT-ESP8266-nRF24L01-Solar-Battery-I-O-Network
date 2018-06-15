#ifndef NRF24L01_H_
#define NRF24L01_H_

#include "nRF24L01+_types.h"

typedef struct{
    n_STATUS_t status;
    unsigned waitForTXACK       : 1;
    unsigned waitForTXACKCount  : 4;
    unsigned TXBusy             : 1;
    unsigned TXBusyCount        : 4;
    unsigned RXPending			: 1;
    unsigned RXMode             : 1;
} nrf24l01_t;


//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 83

void ICACHE_FLASH_ATTR nrf24l01Init(MQTT_Client* p_mqttClient);
void ICACHE_FLASH_ATTR nrf24l01Pause(void);
void ICACHE_FLASH_ATTR nrf24l01Unpause(void);


#endif /* USER_CONFIG_H_ */


