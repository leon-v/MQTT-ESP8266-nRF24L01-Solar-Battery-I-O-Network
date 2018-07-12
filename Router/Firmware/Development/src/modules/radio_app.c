#include "radio_app.h"

LOCAL MQTT_Client* mqttClient;

#define RADIO_TASK_PRIO             	1
#define RADIO_TASK_QUEUE_SIZE        1
os_event_t nrf24l01procTaskQueue[RADIO_TASK_QUEUE_SIZE];

static os_timer_t spiTestTimer;

uint8 enabled = 0;

void radioEnable(uint8 enable){
	enabled = enable;
}

void ICACHE_FLASH_ATTR radio_Task(os_event_t *e) {
	// os_printf("radio_Task \r\n");
    
	if (nrf24l01.RXPending){
		nrf24l01.RXPending = 0;

		n_STATUS_t status;
	    status.byte = 0x00;
	    status.RX_DR = 1;
    	nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);

    	nrf24l01ReceiveString();

    	// os_printf("Radio: RX Name: %s \r\n", nrf24l01RXName);
    	// os_printf("Radio: RX Topic: %s \r\n", nrf24l01RXTopic);
    	// os_printf("Radio: RX Name: %s \r\n", nrf24l01RXValue);
    	// os_printf("Radio: RX Data: %u \r\n", nrf24l01RXPacketData.byte);

    	// 1UnconfiguredW1/ADC3/644
    	char *buffer = NULL;
		buffer = (char *) os_malloc(128 * sizeof(char));

		os_sprintf(buffer, "/radio/in/%u/%s/%s", system_get_chip_id(), nrf24l01RXName, nrf24l01RXTopic);
		os_printf("%s = %s\r\n", buffer, nrf24l01RXValue);
		os_printf("Data Byte = %u\r\n", nrf24l01RXPacketData.byte);

		if (nrf24l01RXPacketData.ACKRequest){

			nrf24l01TXPacketData.byte = nrf24l01RXPacketData.byte;
			nrf24l01TXPacketData.ACKRequest = 0;
			nrf24l01TXPacketData.IsACK		= 1;

			strcpy(nrf24l01TXName, nrf24l01RXName);
	    	strcpy(nrf24l01TXTopic, nrf24l01RXTopic);
	    	strcpy(nrf24l01TXValue, nrf24l01RXValue);

	    	nrf24l01SendString(0);

	    	os_printf("Sent ACK\r\n");

	    	nrf24l01SetRXMode(1);
		}
		
		
		if (enabled){
			MQTT_Publish(mqttClient, buffer, nrf24l01RXValue, strlen(nrf24l01RXValue), 1, 1);
		}

    	os_free(buffer);

	}
}

void radoCheckStatus(void){

	nrf24l01ISR();
	if (nrf24l01.RXPending){
		system_os_post(RADIO_TASK_PRIO, 0, (os_param_t) mqttClient);
	}
}

void ICACHE_FLASH_ATTR spiTestTimerFunction(void *arg){
	os_printf("Radio: Timer\r\n");
	radoCheckStatus();
}


void radioInterrupt(int * arg){

	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	// os_printf("Radio: Interrupt\r\n");
	radoCheckStatus();

	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);
}

void ICACHE_FLASH_ATTR radioInit(MQTT_Client* p_mqttClient){


	mqttClient = p_mqttClient;

	os_printf("Radio Init\r\n");

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); // CE


	GPIO_DIS_OUTPUT(GPIO_ID_PIN(5));
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(5));

	gpio_output_set(0, GPIO_ID_PIN(5), 0, GPIO_ID_PIN(5));
	gpio_pin_intr_state_set(GPIO_ID_PIN(5), GPIO_PIN_INTR_NEGEDGE);
	ets_isr_attach(ETS_GPIO_INUM, (ets_isr_t) radioInterrupt, NULL);
	ETS_GPIO_INTR_ENABLE();// Enable interrupts

	nrf24l01Init(1);

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