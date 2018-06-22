#include "radio_app.h"

LOCAL MQTT_Client* mqttClient;

#define RADIO_TASK_PRIO             	1
#define RADIO_TASK_QUEUE_SIZE        1
os_event_t nrf24l01procTaskQueue[RADIO_TASK_QUEUE_SIZE];

static os_timer_t spiTestTimer;


void ICACHE_FLASH_ATTR radio_Task(os_event_t *e) {
	os_printf("radio_Task \r\n");
    

    if (nrf24l01.RXPending){
    	nrf24l01.RXPending = 0;

    	char *buffer = NULL;
		buffer = (char *) os_malloc(64 * sizeof(char));

		os_sprintf(buffer, "/radio/%u/in/%s/%s/%s", system_get_chip_id(), nrf24l01RXName, nrf24l01RXTopic, nrf24l01RXValue);

		os_printf("%s\r\n", buffer);

		strcpy(nrf24l01TXName, nrf24l01RXName);
    	strcpy(nrf24l01TXTopic, nrf24l01RXTopic);
    	strcpy(nrf24l01TXValue, "ACK");

    	nrf24l01SendString(0);

    	nrf24l01SetRXMode(1);

		
    	MQTT_Publish(mqttClient, buffer, nrf24l01RXValue, strlen(nrf24l01RXValue), 1, 1);

    	os_free(buffer);
    }
}

void ICACHE_FLASH_ATTR spiTestTimerFunction(void *arg){
	nrf24l01ISR();
	system_os_post(RADIO_TASK_PRIO, 0, (os_param_t) mqttClient);
}


void radioInterrupt(int * arg){

	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	nrf24l01ISR();
	system_os_post(RADIO_TASK_PRIO, 0, (os_param_t) mqttClient);

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
	os_timer_arm(&spiTestTimer, 2000, 1);

	system_os_task(radio_Task, RADIO_TASK_PRIO, nrf24l01procTaskQueue, RADIO_TASK_QUEUE_SIZE);

	

	os_printf("Radio Init End\r\n");
}
