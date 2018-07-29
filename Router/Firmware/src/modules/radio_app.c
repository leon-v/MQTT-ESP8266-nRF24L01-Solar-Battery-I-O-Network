#include "radio_app.h"

LOCAL MQTT_Client* mqttClient;

#define OUT_PREFIX "/radio/out/"
#define RADIO_TASK_PRIO             	1
#define RADIO_TASK_QUEUE_SIZE        1
os_event_t nrf24l01procTaskQueue[RADIO_TASK_QUEUE_SIZE];

static os_timer_t spiTestTimer;

uint8 enabled = 0;

void radioEnable(uint8 enable){
	enabled = enable;
}

unsigned char ICACHE_FLASH_ATTR nrf24l01GetPipe(char * name){

	unsigned char pipe = 0;
	unsigned char i = 0;

	// Calculate a pipe from the name passed
	for (i = 0; i < strlen(name); i++){
		pipe+= name[i];
	}

	return (unsigned) pipe % 6;
}

void ICACHE_FLASH_ATTR radio_Task(os_event_t *e) {
    
	if (!nrf24l01.RXPending){
		return;
	}

	os_printf("radio_Task \r\n");
		
	nrf24l01Packet_t * RXPacket = nrf24l01GetRXPacket();

	// If we are the primary hub / reciever, we need to send back ACKs
	if (RXPacket->packetData.ACKRequest){
		nrf24l01SetTXPipe(RXPacket->packetData.Pipe);
		nrf24l01SendACK(RXPacket);
	}

	os_printf("Radio RX Message: = %s\r\n", RXPacket->Message);


	char* strings = strtok(RXPacket->Message, "/");

	char *name = (char *) os_zalloc(strlen(strings) * sizeof(char));
	strcpy(name, strings);
	strings = strtok(NULL, "/");

	char *topic = (char *) os_zalloc(strlen(strings) * sizeof(char));
	strcpy(topic, strings);
	strings = strtok(NULL, "/");
	
	char *value = (char *) os_zalloc(strlen(strings) * sizeof(char));
	strcpy(value, strings);



	char *buffer = NULL;
	buffer = (char *) os_zalloc(128 * sizeof(char));

	os_sprintf(buffer, "/radio/in/%u/%s/%s", system_get_chip_id(), name, topic);

	// os_printf("%s = %s\r\n", buffer, value);

	if (enabled){
		int retain = 0;
		int qos = 1;
		MQTT_Publish(mqttClient, buffer, value, strlen(value), qos, retain);
	}

	os_free(name);
	os_free(topic);
	os_free(value);
	os_free(buffer);

	nrf24l01.RXPending = 0;

	nrf24l01SetRXMode(1);
}

void radoCheckStatus(void){

	nrf24l01ISR();

	if (nrf24l01.RXPending){
		system_os_post(RADIO_TASK_PRIO, 0, (os_param_t) mqttClient);
	}
}

void ICACHE_FLASH_ATTR spiTestTimerFunction(void *arg){
	// os_printf("Radio: Timer\r\n");
	radoCheckStatus();
}


void radioInterrupt(int * arg){

	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	// os_printf("Radio: Interrupt\r\n");
	radoCheckStatus();

	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);
}

void ICACHE_FLASH_ATTR radioForwardPacket(char * mqttTopic, char * mqttValue){

	nrf24l01Packet_t TXPacket;
	TXPacket.packetData.byte = 0;
	TXPacket.packetData.ACKRequest = 1;

	mqttTopic+= strlen(OUT_PREFIX);

	os_sprintf(TXPacket.Message, "%s/%s", mqttTopic, mqttValue);

	INFO("Radio Send: %s\r\n", TXPacket.Message);

	char* strings = strtok(mqttTopic, "/");

	char *name = (char *) os_zalloc(strlen(strings) * sizeof(char));
	strcpy(name, strings);
	strings = strtok(NULL, "/");

	char *topic = (char *) os_zalloc(strlen(strings) * sizeof(char));
	strcpy(topic, strings);

	INFO("Radio name: %s\r\n", name);
	INFO("Radio topic: %s\r\n", topic);


	unsigned char pipe = nrf24l01GetPipe(name);
	nrf24l01SetTXPipe(pipe);
    
    system_soft_wdt_stop();
	nrf24l01SendPacket(&TXPacket);
	system_soft_wdt_restart();

	nrf24l01SetRXMode(1);

	INFO("Radio Sent");

	
}


void ICACHE_FLASH_ATTR radioInit(MQTT_Client* p_mqttClient){


	mqttClient = p_mqttClient;

	os_printf("Radio Init\r\n");

	MQTT_Subscribe(mqttClient, strcat(OUT_PREFIX, "#"), 0);

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); // CE


	GPIO_DIS_OUTPUT(GPIO_ID_PIN(5));
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(5));

	gpio_output_set(0, GPIO_ID_PIN(5), 0, GPIO_ID_PIN(5));
	gpio_pin_intr_state_set(GPIO_ID_PIN(5), GPIO_PIN_INTR_NEGEDGE);
	ets_isr_attach(ETS_GPIO_INUM, (ets_isr_t) radioInterrupt, NULL);
	ETS_GPIO_INTR_ENABLE();// Enable interrupts

	nrf24l01Init();

	nrf24l01SetRXMode(1);

	os_timer_disarm(&spiTestTimer);
	os_timer_setfn(&spiTestTimer, (os_timer_func_t *)spiTestTimerFunction, NULL);
	os_timer_arm(&spiTestTimer, 20000, 1);

	system_os_task(radio_Task, RADIO_TASK_PRIO, nrf24l01procTaskQueue, RADIO_TASK_QUEUE_SIZE);

	

	os_printf("Radio Init End\r\n");
}

// Get the RX data into the buffer
        // nrf24l01ReceiveString();

        // if (nrf24l01.RXPending){
        // 	if (nrf24l01ProcessRX){
        // 		nrf24l01ProcessRX();
        // 	}
        // }