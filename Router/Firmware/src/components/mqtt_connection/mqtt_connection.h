#ifndef _MQTT_CONNECTION_H__
#define _MQTT_CONNECTION_H__

#define MQTT_CONNECTED_BIT BIT0

typedef struct{
	unsigned long connectionSuccess;
	unsigned long connectionFail;
	unsigned long Publish;
	unsigned long Dump;
} mqttStatus_t;

#define mqttStatus_r {0, 0, 0, 0}


void mqtt_connection_init(void);
mqttStatus_t mqtt_connection_get_status(void);

#endif