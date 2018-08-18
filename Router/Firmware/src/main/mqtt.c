
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#include "mqtt.h"
#include "configFlash.h"
#include "wifi.h"
#include "esp_system.h"

/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t mqttEventGroup;

MQTTClient client;

char uniqueID[16];

EventGroupHandle_t mqttGetEventGroup(void){
	return mqttEventGroup;
}

char * mqttGetUniqueID(void){
	return uniqueID;
}

MQTTClient * mqttGetClient(void){
	return &client;
}

void mqttTask(){
    Network network;
    unsigned char sendbuf[80];
    unsigned char readbuf[80] = {0};
    int rc = 0;
    MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer;

reconnect:

    printf("MQTT Client - Connection - Thread start.\n");

    vTaskDelay(1000 / portTICK_RATE_MS);  //send every 10 seconds

	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	if ( (strlen(configFlash.mqttHost) == 0) || (configFlash.mqttPort == 0) ) {
		printf("MQTT Client - Connection - No configuration set.\n");
		vTaskDelay(10000 / portTICK_RATE_MS);  //send every 10 seconds
		goto reconnect;
	}

	NetworkInit(&network);

	MQTTClientInit(&client, &network, (configFlash.mqttKeepalive * 1000), sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf));

	char * address = (char *) &configFlash.mqttHost;
	
    if ((rc = NetworkConnect(&network, address, configFlash.mqttPort)) != 0) {
    	printf("MQTT Client - Connection - Failed to connect to %s:%d with error %d.\n", address, configFlash.mqttPort, rc);
    	close(network.my_socket);
        goto fail1;
    }

    printf("MQTT Client - Connection - Socket connected.\n");

    #if defined(MQTT_TASK)

    if ((rc = MQTTStartTask(&client)) != pdPASS) {
        printf("MQTT Client - Connection - Task thread start failed with error %d.\n", rc);
        goto fail1;
    }

    printf("MQTT Client - Connection - Task thread started.\n");

	#endif

    
    char clientID[48];

    sprintf(clientID, "V-Router %s", mqttGetUniqueID());

    printf("MQTT Client - Connection - Client ID set to %s.\n", clientID);

    connectData.MQTTVersion = configFlash.mqttVersion; // 3 = 3.1 4 = 3.1.1
    connectData.clientID.cstring = clientID;
    connectData.username.cstring = (char *) &configFlash.mqttUsername;
    connectData.password.cstring = (char *) &configFlash.mqttPassword;

    if ((rc = MQTTConnect(&client, &connectData)) != 0) {
        printf("MQTT Client - Connection - Failed to authenticate with MQTT server with error code %d.\n", rc);
        goto fail1;
    }
	
	printf("MQTT Client - Connection - Connected.\n");

	

    while(MQTTIsConnected(&client)){
    	vTaskDelay(1000 / portTICK_RATE_MS);  //send every 1 seconds
    	xEventGroupSetBits(mqttEventGroup, MQTT_CONNECTED_BIT);
    }

    xEventGroupClearBits(mqttEventGroup, MQTT_CONNECTED_BIT);

    printf("MQTT Client - Connection - Connected check failed.\n");

fail1:

	MQTTDisconnect(&client);

// fail2:
	
	printf("MQTT Client - Connection - Reconnecting.\n");

	goto reconnect;
    // printf("mqtt_client_thread going to be deleted\n");
    // vTaskDelete(NULL);
    // return;
}

void mqttInt(){

	uint8_t mac[6];
    esp_efuse_mac_get_default(mac);

	sprintf(uniqueID, "%02x%02x%02x%02x%02x%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

	mqttEventGroup = xEventGroupCreate();

	xTaskCreate(&mqttTask, "mqtt", 2048, NULL, 9, NULL);
}