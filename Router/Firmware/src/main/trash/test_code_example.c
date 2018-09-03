 static void Task_MqttClient_Connect(void *pvParameters) {
 	Network network;
 	unsigned char sendbuf[2048], readbuf[2048] = { 0 }; 
 	int rc = 0, count = 0; 
 	MQTTPacket_connectData connectData = MQTTPacket_connectData_initializer; 
 	pvParameters = 0; 
 	NetworkInit(&network); 
 	MQTTClientInit(&client, &network, 5000, sendbuf, sizeof(sendbuf), readbuf, sizeof(readbuf)); 
 	bool first_flag = false; 
 	char *address = MQTT_SERVICE; 
 	connectData.MQTTVersion = 3; 
 	connectData.clientID.cstring = originTopic; 
 	connectData.username.cstring = MQTT_USER_NAME; 
 	connectData.password.cstring = MQTT_USER_PAW; 
 	connectData.keepAliveInterval = 30; 
 	connectData.cleansession = true; 
 	for (;;) {
 		while (wifi_station_get_connect_status() != STATION_GOT_IP) {
 			vTaskDelay(1000 / portTICK_RATE_MS); 
 		}

 		if (IS_DEBUG_OPEN)
 			printf("Task_MqttClient_Connect NetworkConnect init...\n"); 

		if ((rc = NetworkConnect(&network, address, MQTT_PORT)) != 0) {
			if (IS_DEBUG_OPEN) printf("MClouds NetworkConnect connect fail , code %d\n", rc);
		} else {
			if (IS_DEBUG_OPEN) printf(" NetworkConnect init succeed...\n"); 
		}

		if (!first_flag){

			if ((rc = MQTTStartTask(&client)) != pdPASS) {
				if (IS_DEBUG_OPEN)
					printf("Return code from start tasks fail , errorCpode: %d\n", rc);

			} else {
				if (IS_DEBUG_OPEN)
					printf("Use MQTTStartTask succeed...\n"); 
				first_flag = true; 
			}
		}

		if ((rc = MQTTConnect(&client, &connectData)) != 0) {
			if (IS_DEBUG_OPEN)
				printf("[SY] MClouds connect fail , errorCode: %d\n", rc); 
			network.disconnect(&network); 
			vTaskDelay(1000 / portTICK_RATE_MS); 
		}

		if ((rc = MQTTSubscribe(&client, subTopic, QOS0, MessageArrived)) != 0) {
			if (IS_DEBUG_OPEN)
				printf("[SY] MClouds Subscribe fail is %d\n", rc); 
			network.disconnect(&network); 
			vTaskDelay(1000 / portTICK_RATE_MS); 
		} else {
			isConnectMQTT = true; 

			if (IS_DEBUG_OPEN){
				printf("MQTT subscribe to topic -> %s\n", subTopic); 
			}
		}

		xQueueReset(MqttMessageQueueHandler);

		while (1) {
			char payload[2048]; 
			struct esp_mqtt_msg_type *pMsg; 

			printf("MqttMessageQueueHandler waitting ..\n"); 

			xQueueReceive(MqttMessageQueueHandler, &pMsg, portMAX_DELAY); 

			if (pMsg->power == 3) {
				rc = 1; 
	 		//标志位置位1，准备重连
	 		} else {
	 			sprintf(payload, "%s", pMsg->allData);

				MQTTMessage message; 
				message.qos = QOS1; 
				message.retained = false; 
				message.payload = (void *) payload; 
				message.payloadlen = strlen(payload) + 1; 

				if ((rc = MQTTPublish(&client, pubTopic, &message)) != 0) {
					printf("MQTT publish succeed fail %d\n", rc); 
				} else {
					printf("MQTT publish succeed ...\n"); 
				}
			}

			if (rc != 0) {
				break; 
			}

			printf("network: %d\n", rc); 
		}

		if (IS_DEBUG_OPEN)
			printf("network.disconnect\n"); 

		network.disconnect(&network); 

		vTaskDelay(1500 / portTICK_RATE_MS); 
	}

	printf("mqtt_client_thread going to be deleted\n"); 
	mHandlerMQTTConntion = NULL; 
	vTaskDelete(NULL); 
	return; 
} 
