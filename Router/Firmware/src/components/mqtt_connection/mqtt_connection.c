#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "MQTTClient.h"

#include "mqtt_connection.h"
#include "configFlash.h"
#include "wifi.h"
#include "radio.h"
#include "esp_system.h"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t mqttEventGroup;

static xQueueHandle MQTTMessageQueue = NULL;
MQTTClient client;

char uniqueID[16];

mqttStatus_t mqttStatus = mqttStatus_r;

mqttStatus_t mqtt_connection_get_status(void){
	return mqttStatus;
}

EventGroupHandle_t mqttGetEventGroup(void){
	return mqttEventGroup;
}

char * mqttGetUniqueID(void){
	return uniqueID;
}

MQTTClient * mqttGetClient(void){
	return &client;
}

void mqtt_connection(){
    Network network;
    unsigned char sendbuf[80] = {0};
    unsigned char readbuf[80] = {0};
    int rc = 0;
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;
    EventBits_t wifiEventBits;

    char clientID[48];

    char * address;

    sprintf(clientID, "Beeline %s", mqttGetUniqueID());

    printf("MQTT Client - Connection - Client ID set to %s.\n", clientID);

    NetworkInit(&network);

    printf("MQTT Client - Connection - Thread start.\n");

reconnect:

	printf("MQTT Client - Connection - Waiting for WiFi.\n");
	
	wifiEventBits = xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, 10000);
	
	if (!(wifiEventBits & WIFI_CONNECTED_BIT) ){
		printf("MQTT Client - Connection - WiFi not ready.\n");
		goto reconnect;
	}

	printf("MQTT Client - Connection - WiFi ready.\n");

	if ( (strlen(configFlash.mqttHost) == 0) || (configFlash.mqttPort == 0) ) {
		printf("MQTT Client - Connection - No configuration set.\n");
		// vTaskDelay(10000 / portTICK_RATE_MS);  //send every 10 seconds
		goto reconnect;
	}

	address = (char *) &configFlash.mqttHost;

	MQTTClientInit(&client, &network, 1000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));
	
    if ((rc = NetworkConnect(&network, address, configFlash.mqttPort)) != 0) {
    	printf("MQTT Client - Connection - Failed to connect to %s:%d with error %d.\n", address, configFlash.mqttPort, rc);
    	close(network.my_socket);
        goto fail2;
    }

    printf("MQTT Client - Connection - Socket connected.\n");

    #if defined(MQTT_TASK)

    if ((rc = MQTTStartTask(&client)) != pdPASS) {
        printf("MQTT Client - Connection - Task thread start failed with error %d.\n", rc);
        goto fail1;
    }

    printf("MQTT Client - Connection - Task thread started.\n");
	
	#endif

	connectData.username.cstring = configFlash.mqttUsername;
    connectData.password.cstring = configFlash.mqttPassword;
    connectData.keepAliveInterval = configFlash.mqttKeepalive;
    connectData.MQTTVersion = 4;
    connectData.clientID.cstring = (char *) &clientID;
    connectData.cleansession = 1;

    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("MQTT Client - Connection - Failed to authenticate with MQTT server with error code %d.\n", rc);
        goto fail1;
    }
	
	printf("MQTT Client - Connection - Connected.\n");

	mqttStatus.connectionSuccess++;

	int isConnected = 0;
	for (;;){

		isConnected = MQTTIsConnected(&client);

		if (!isConnected){
			break;
		}

		vTaskDelay(1000 / portTICK_RATE_MS);  //send every 1 seconds
	}

    printf("MQTT Client - Connection - Connected check failed.\n");


fail1:

	MQTTDisconnect(&client);

fail2:
	
	printf("MQTT Client - Connection - Reconnecting.\n");

	mqttStatus.connectionFail++;

	vTaskDelay(5000 / portTICK_RATE_MS);  //send every 10 seconds

	goto reconnect;

    printf("mqtt_client_thread going to be deleted\n");
    vTaskDelete(NULL);
    return;
}

void mqtt_connection_send_task(){

	int rc = 0;
	radioMessage_t radioMessage;
	char mqttTopic[64];
	EventBits_t mqttEventBits;

	for (;;) {

		if (!xQueueReceive(radioGetRXQueue(), &radioMessage, portMAX_DELAY)) {
			printf("mqtt radio: Queue wait time out, restart listen.\n");
			continue;
		}

		if (!MQTTIsConnected(&client)){
			printf("mqtt radio: Dump: Name=%s, Sensor=%s, Value=%s.\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
			mqttStatus.Dump++;
			continue;
		}

		strcpy(mqttTopic, "radio/out/");
		strcat(mqttTopic, mqttGetUniqueID());
		strcat(mqttTopic, "/");
		strcat(mqttTopic, radioMessage.name);
		strcat(mqttTopic, "/");
		strcat(mqttTopic, radioMessage.sensor);

		MQTTMessage message;

		message.qos = QOS1;
    	message.retained = 0;
		message.payload = &radioMessage.value;
		message.payloadlen = strlen(message.payload);

    	if ((rc = MQTTPublish(&client, mqttTopic, &message)) != 0) {
	        printf("Radio->MQTT - Task - Return code from MQTT publish is %d\n", rc);
	        continue;
	    }

    	mqttStatus.Publish++;

    	printf("mqtt radio: Publish: Name=%s, Sensor=%s, Value=%s.\n", radioMessage.name, radioMessage.sensor, radioMessage.value);
	}

    vTaskDelete(NULL);
    return;
}

void mqtt_connection_init(){

	uint8_t mac[6];
    esp_efuse_mac_get_default(mac);

	sprintf(uniqueID, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	MQTTMessageQueue = xQueueCreate(16, sizeof(radioMessage_t));

	xTaskCreate(&mqtt_connection, "mqtt_connection", 8192, NULL, 9, NULL);

	xTaskCreate(&mqtt_connection_send_task, "mqtt_connection_send_task", 8192, NULL, 9, NULL);
}