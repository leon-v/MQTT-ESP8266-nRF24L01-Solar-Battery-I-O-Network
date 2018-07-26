#ifndef RADIO_APP_H_
#define	RADIO_APP_H_

#include "nrf24l01.h"
#include "mqtt.h"
#include "mem.h"
#include "debug.h"

void ICACHE_FLASH_ATTR radioInit(MQTT_Client* p_mqttClient);

#endif	/* RADIO_APP_H_ */