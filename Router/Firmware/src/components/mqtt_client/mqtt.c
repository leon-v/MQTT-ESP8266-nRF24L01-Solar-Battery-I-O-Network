#include <nvs.h>
#include "mqtt_client.h"

#include "wifi.h"
#include "config.h"

#include "esp_log.h"

static const char *TAG = "MQTT";

static esp_err_t mqtt_event_handler(esp_mqtt_event_handle_t event) 
{
    esp_mqtt_client_handle_t client = event->client;
    int msg_id;

    // your_context_t *context = event->context;
    switch (event->event_id) {
        case MQTT_EVENT_CONNECTED:
            ESP_LOGI(TAG, "MQTT_EVENT_CONNECTED");
            msg_id = esp_mqtt_client_publish(client, "/topic/qos1", "data_3", 0, 1, 0);
            ESP_LOGI(TAG, "sent publish successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos0", 0);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_subscribe(client, "/topic/qos1", 1);
            ESP_LOGI(TAG, "sent subscribe successful, msg_id=%d", msg_id);

            msg_id = esp_mqtt_client_unsubscribe(client, "/topic/qos1");
            ESP_LOGI(TAG, "sent unsubscribe successful, msg_id=%d", msg_id);
		break;


        case MQTT_EVENT_DISCONNECTED:
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

void mqttClientInit(void){

	xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, portMAX_DELAY);

	nvs_handle nvsHandle;
	ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READONLY, &nvsHandle));
	


	esp_mqtt_client_config_t mqtt_cfg = {
        .host = "",
        .port = 1883,
        .username = "",
        .password = "",
        .keepalive = 120,
        .event_handle = mqtt_event_handler,
        // .user_context = (void *)your_context
    };

    size_t nvsLength;

    nvsLength = MAX_CONFIG_STRING_LENGTH;
	nvs_get_str(nvsHandle, "mqttHost", (char *) mqtt_cfg.host, &nvsLength);

	nvs_get_u32(nvsHandle, "mqttPort", &mqtt_cfg.port);

	nvsLength = MAX_CONFIG_STRING_LENGTH;
	nvs_get_str(nvsHandle, "mqttUsername", (char *) mqtt_cfg.username, &nvsLength);

	nvsLength = MAX_CONFIG_STRING_LENGTH;
	nvs_get_str(nvsHandle, "mqttPassword", (char *) mqtt_cfg.password, &nvsLength);

	nvs_get_u32(nvsHandle, "mqttKeepalive", &mqtt_cfg.keepalive);

	nvs_close(nvsHandle);

    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}