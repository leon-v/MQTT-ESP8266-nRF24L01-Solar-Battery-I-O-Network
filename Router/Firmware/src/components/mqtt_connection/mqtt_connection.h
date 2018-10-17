#ifndef MQTT_H_
#define MQTT_H_

void mqttClientInit(void);
xQueueHandle getMQTTConnectionMessageQueue(void);

#endif