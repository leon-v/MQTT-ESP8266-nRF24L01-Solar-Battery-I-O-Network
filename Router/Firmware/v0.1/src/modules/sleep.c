#include "wifi.h"
#include "ets_sys.h"
#include "osapi.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "config.h"
#include "mem.h"
#include "gpio16.h"


#define MQTT_TASK_PRIO                2

unsigned int counter = 0;
unsigned int readyToSleep = 1;
unsigned int wakeCount = 0;
LOCAL MQTT_Client* mqttClient;


void ICACHE_FLASH_ATTR setADC(unsigned int index){

	if ((index >> 0) & 0x0001){
		gpio16_output_set(1);
		// gpio_output_set(BIT16, 0, BIT16, 0);
	} else{
		gpio16_output_set(0);
		// gpio_output_set(0, BIT16, BIT16, 0);
	}

	if ((index >> 1) & 0x0001){
		// gpio_output_set(BIT12, 0, BIT12, 0);
	} else{
		// gpio_output_set(0, BIT12, BIT12, 0);
	}

	if ((index >> 2) & 0x0001){
		// gpio_output_set(BIT13, 0, BIT13, 0);
	} else{
		// gpio_output_set(0, BIT13, BIT13, 0);
	}
}

static os_timer_t readADC_timer;
uint16 adcindex = 0;
void ICACHE_FLASH_ATTR sendADCData(){

	os_printf("send ADC Data\r\n");

	
	#define adcValueBuffferLength	1024

	uint16 adc;
	uint16 adcValueBufffer[adcValueBuffferLength];
	uint16 adcValue;
	uint16 adcValueIndex;
	uint16 length;
	uint16 clockDivider;
	double adcValueSum;

	length = adcValueBuffferLength;
	clockDivider = 8;

	char *mqttTopic = NULL;
	mqttTopic = (char *) os_malloc(96 * sizeof(char));

	char *mqttValue = NULL;
	mqttValue = (char *) os_malloc(8 * sizeof(char));

	gpio_output_set(0, BIT15, BIT15, 0); 			// Set GPIO15 low output
	os_delay_us(100);
	for (adc = 0; adc < 8; adc++){

		setADC(adc);
		os_delay_us(100);

		//adcValue = system_adc_read();

		// for(adcValueIndex = 0; adcValueIndex < length; adcValueIndex++){
		// 	adcValueBufffer[adcValueIndex] = system_adc_read();
		// }

		// This kept giving me error reading 
		ets_intr_lock();		 //close	interrupt
		system_adc_read_fast(adcValueBufffer,	length,	clockDivider);
		ets_intr_unlock();	 	 //open	interrupt

		adcValueSum = 0.0;
		for(adcValueIndex = 0; adcValueIndex < length; adcValueIndex++){
			adcValueSum+= (double) adcValueBufffer[adcValueIndex];;
		}

		adcValue = (unsigned int) (adcValueSum / length);


		mqttTopic = strcpy(mqttTopic, sysCfg.mqtt_topicroot);
		switch (adc){
			case 0:
				adcValue = (unsigned int) ((adcValueSum * sysCfg.mqtt_muladc0) / length);
				os_sprintf(mqttValue, "%d", adcValue);
				mqttTopic = strcat(mqttTopic, sysCfg.mqtt_topicadc0);
				os_printf("%s = %s\r\n", mqttTopic, mqttValue);
				MQTT_Publish(mqttClient, mqttTopic, mqttValue, strlen(mqttValue), 1, 1);
				break;
		}

		
	}

	gpio_output_set(BIT15, 0, BIT15, 0); 			// Set GPIO15 high output (up)

	counter++;

	os_sprintf(mqttValue, "%d", counter);
	mqttTopic = strcpy(mqttTopic, sysCfg.mqtt_topicroot);
	mqttTopic = strcat(mqttTopic, "/Counter");
	os_printf("%s = %s\r\n", mqttTopic, mqttValue);
	MQTT_Publish(mqttClient, mqttTopic, mqttValue, strlen(mqttValue), 1, 1);

}


int loopCount = 0;
static os_timer_t goToSleep_timer;
void ICACHE_FLASH_ATTR goToSleep(void *arg){

	if (loopCount++ > 50){
		loopCount = 0;
		sendADCData();
	}
}

void ClientConnected(void){
	os_timer_arm(&goToSleep_timer, 100, 1);
}
void ClientDisconnected(void){
	os_timer_disarm(&goToSleep_timer);
}

void ICACHE_FLASH_ATTR sleepInit(MQTT_Client* p_mqttClient){

	//  gpio_init();

	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15); 	// Set GPIO15 function

	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12);
	// PIN_PULLUP_EN(PERIPHS_IO_MUX_MTDI_U);

	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13);

	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); // select pin to GPIO 14 mode
	// PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTMS_U);
	// //PIN_PULLDWN_DIS(PERIPHS_IO_MUX_MTMS_U);

 //   gpio_output_set( BIT14, 0, BIT14, 0 );

	// gpio16_output_conf();

	// //gpio_output_set(BIT15, 0, 0, BIT15);// Input Set
	// //gpio_output_set(BIT0, 0, 0, BIT0);// Input Set
	// //gpio_output_set(BIT1, 0, 0, BIT1);// Input Set
	// // MTDO, U0TXD and GPIO0

	// gpio_output_set(BIT2,0, BIT2, 0); // LED OFF

	// gpio_output_set(0, BIT14, 0, BIT14);// Bit 14 input


	// //Setup 415 pins
	// //gpio_output_set(BIT15, 0, BIT15, 0); 			// Set GPIO15 high output (up)
	// gpio_output_set(0, BIT15, BIT15, 0); 			// Set GPIO15 low output

	// gpio_output_set(BIT13, 0, BIT13, 0);
	// gpio_output_set(BIT12, 0, BIT12, 0);
	// gpio16_output_set(1);


	mqttClient = p_mqttClient;

	// Configure GPIO14 to act as an interrupt to wake the IC and to run a task.
	// Running a task on interrupt instead of timers enabled the IC to go back to sleep sooner.
	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14);
	// PIN_PULLUP_DIS(PERIPHS_IO_MUX_MTMS_U); // Or else the capacitor on the pin won't discharge.

	// Output Set &= 0
	// gpio_output_set(0, BIT14, BIT14, 0);

	// gpio_pin_wakeup_enable(14, GPIO_PIN_INTR_LOLEVEL);// Attach wake from light sleep when low to GPIO14
	// gpio_pin_intr_state_set(14, GPIO_PIN_INTR_LOLEVEL);// Attach interrupt task to run on GPIO14
	// ets_isr_attach(ETS_GPIO_INUM, (ets_isr_t)sleepWakeOnInterruptHandeler, NULL);// ^

	// wifi_fpm_auto_sleep_set_in_null_mode(1);

	os_timer_disarm(&goToSleep_timer);
	os_timer_setfn(&goToSleep_timer, (os_timer_func_t *)goToSleep, NULL);

	// ETS_GPIO_INTR_ENABLE();// Enable interrupts

}