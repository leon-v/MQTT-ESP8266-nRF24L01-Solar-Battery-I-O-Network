#include <nvs.h>
#include <mqtt_client.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <esp_log.h>

#include "wifi.h"
#include "beeline.h"

esp_mqtt_client_handle_t client;

static xQueueHandle mqttConnectionMessageQueue = NULL;

static const char *TAG = "MQTT";

xQueueHandle getMQTTConnectionMessageQueue(void){
	return mqttConnectionMessageQueue;
}

static esp_err_t mqttConnectionEventHandler(esp_mqtt_event_handle_t event) {
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
        	xEventGroupSetBits(beelineGetEventGroup(), MQTT_CONNECTED_BIT);

        	beelineMessage_t beelineMessage;
        	strcpy(beelineMessage.name, "TestName");
			strcpy(beelineMessage.sensor, "TestSensor");
			strcpy(beelineMessage.value, "TestValue");

			xQueueSend(mqttConnectionMessageQueue, &beelineMessage, 0);

            // ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            // msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
            // ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
            // ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            // ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            // msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            // ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);


		break;


        case MQTT_EVENT_DISCONNECTED:
        	xEventGroupClearBits(beelineGetEventGroup(), MQTT_CONNECTED_BIT);
            ESP_LOGI(TAG, "MQTT_EVENT_DISCONNECTED");
		break;

        case MQTT_EVENT_SUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_SUBSCRIBED, msg_id=%d", event->msg_id);
            msg_id = esp_mqtt_client_publish(client, "/topic/qos0", "data", 0, 0, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
		break;

        case MQTT_EVENT_UNSUBSCRIBED:
            ESP_LOGI(TAG, "MQTT_EVENT_UNSUBSCRIBED, msg_id=%d", event->msg_id);
		break;

        case MQTT_EVENT_PUBLISHED:
            ESP_LOGI(TAG, "MQTT_EVENT_PUBLISHED, msg_id=%d", event->msg_id);
		break;

        case MQTT_EVENT_DATA:
            ESP_LOGI(TAG, "MQTT_EVENT_DATA");
            printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            printf("DATA=%.*s\r\n", event->data_len, event->data);
		break;

        case MQTT_EVENT_ERROR:
            ESP_LOGI(TAG, "MQTT_EVENT_ERROR");
		break;

    }
    return ESP_OK;
}

void mqttConnectionTask(){

	EventBits_t eventBits = xEventGroupWaitBits(beelineGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	if (!(eventBits & WIFI_CONNECTED_BIT)) {
		printf("MQTT Timed out waiting for WiFI. Ending MQTT\n");
		vTaskDelete(NULL);
		return;
	}

	nvs_handle nvsHandle;
	ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READONLY, &nvsHandle));

    size_t nvsLength;

    char host[MAX_CONFIG_STRING_LENGTH];
    nvsLength = sizeof(host);
	nvs_get_str(nvsHandle, "mqttHost", host, &nvsLength);

	unsigned int port;
	nvs_get_u32(nvsHandle, "mqttPort", &port);

	char username[MAX_CONFIG_STRING_LENGTH];
	nvsLength = sizeof(username);
	nvs_get_str(nvsHandle, "mqttUsername", username, &nvsLength);

	char password[MAX_CONFIG_STRING_LENGTH];
	nvsLength = sizeof(password);
	nvs_get_str(nvsHandle, "mqttPassword", password, &nvsLength);

	unsigned int keepalive;
	nvs_get_u32(nvsHandle, "mqttKeepalive", &keepalive);

	nvs_close(nvsHandle);

	esp_mqtt_client_config_t mqtt_cfg = {
        .host = host,
        .port = port,
        .username = username,
        .password = password,
        .keepalive = keepalive,
        .event_handle = mqttConnectionEventHandler,
        // .user_context = (void *)your_context
    };

    client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);

	while (1){

		eventBits = xEventGroupWaitBits(beelineGetEventGroup(), WIFI_CONNECTED_BIT | MQTT_CONNECTED_BIT, false, true, 5000 / portTICK_RATE_MS);

		if (!(eventBits & WIFI_CONNECTED_BIT)) {
			continue;
		}

		if (!(eventBits & MQTT_CONNECTED_BIT)) {
			continue;
		}

		beelineMessage_t beelineMessage;
		if (xQueueReceive(mqttConnectionMessageQueue, &beelineMessage, 1000 / portTICK_RATE_MS)){

			char mqttTopic[64];
			strcpy(mqttTopic, "beeline/out/");
			// strcat(mqttTopic, );
			// strcat(mqttTopic, "/");
			strcat(mqttTopic, beelineMessage.name);
			strcat(mqttTopic, "/");
			strcat(mqttTopic, beelineMessage.sensor);

			int msg_id;
			msg_id = esp_mqtt_client_publish(client, mqttTopic, beelineMessage.value, 0, 1, 0);
			ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);
		}

	}
	
}

void mqttClientInit(void){
	
	mqttConnectionMessageQueue = xQueueCreate(256, sizeof(beelineMessage_t));

	xTaskCreate(&mqttConnectionTask, "mqttConnection", 4096, NULL, 13, NULL);
}