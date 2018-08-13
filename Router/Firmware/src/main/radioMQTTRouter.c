
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "MQTTClient.h"

#include "configFlash.h"
#include "wifi.h"

#include "esp_system.h"

#define MQTT_CLIENT_THREAD_STACK_WORDS  8192
#define MQTT_CLIENT_THREAD_PRIO         8


static void radioMQTTRouterMessageIn(MessageData* data){
    printf("Message arrived: %s\n", (char*)data->message->payload);
}

void radioMQTTRouterTask(){

	MQTTClient client;
    Network network;
    unsigned char sendbuf[80];
    unsigned char readbuf[80] = {0};
    int rc = 0, count = 0;
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

    printf("mqtt client thread starts\n");


	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	NetworkInit(&network);

    MQTTClientInit(&client, &network, 30000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

    if ((rc = NetworkConnect(&network, "valkenb.org", 1883)) != 0) {
        printf("Return code from network connect is %d\n", rc);
    }

#if defined(MQTT_TASK)

    if ((rc = MQTTStartTask(&client)) != pdPASS) {
        printf("Return code from start tasks is %d\n", rc);
    } else {
        printf("Use MQTTStartTask\n");
    }

#endif

    connectData.MQTTVersion = 3;
    connectData.clientID.cstring = "NRF24L01+ Router ESP8266 Test";
    connectData.keepAliveInterval = 10;
    connectData.cleansession = 0;
    //sprintf(connectData.clientID.cstring, "NRF24L01+ Router ESP8266 %u", system_get_chip_id());
    //connectData.clientID.lenstring = strlen(connectData.clientID.cstring);

    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("Return code from MQTT connect is %d\n", rc);
    } else {
        printf("MQTT Connected\n");
    }

    if ((rc = MQTTSubscribe(&client, "radio/out/Test/#", 2, radioMQTTRouterMessageIn)) != 0) {
        printf("Return code from MQTT subscribe is %d\n", rc);
    } else {
        printf("MQTT subscribe to topic \"ESP8266/sample/sub\"\n");
    }

    while (++count) {
        MQTTMessage message;
        char payload[30];

        message.qos = QOS2;
        message.retained = 0;
        message.payload = payload;
        sprintf(payload, "message number %d", count);
        message.payloadlen = strlen(payload);

        if ((rc = MQTTPublish(&client, "radio/in/Test", &message)) != 0) {
            printf("Return code from MQTT publish is %d\n", rc);
        } else {
            printf("MQTT publish topic \"ESP8266/sample/pub\", message number is %d\n", count);
        }

        vTaskDelay(1000 / portTICK_RATE_MS);  //send every 1 seconds
    }

    printf("mqtt_client_thread going to be deleted\n");
    vTaskDelete(NULL);
    return;

}


void radioMQTTRouterInt(){


	xTaskCreate(&radioMQTTRouterTask, "radioMQTTRouter", MQTT_CLIENT_THREAD_STACK_WORDS, NULL, MQTT_CLIENT_THREAD_PRIO, NULL);
}