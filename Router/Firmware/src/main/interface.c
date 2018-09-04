#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "interface.h"
#include "nrf24l01.h"
#include "radio.h"
#include "configFlash.h"


static void gpio_isr_handler(void *arg){

	uint32_t gp_io = (uint32_t) arg;
    xQueueSendFromISR(radioGetInterruptQueue(), &gp_io, NULL);
}

void nrf24l01InterfaceInit(void){

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); // MISO
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); // MOSI
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); // CLK
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15); // CS
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); // INT

	// Configure Inputs
	gpio_config_t inputs;
	inputs.pin_bit_mask	= (1ULL << MISOPIN);
	inputs.mode			= GPIO_MODE_INPUT;
	inputs.pull_up_en	= GPIO_PULLUP_DISABLE;
	inputs.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	inputs.intr_type	= GPIO_INTR_DISABLE;
	gpio_config(&inputs);


	// Configure outputs
	gpio_config_t output;
	output.pin_bit_mask	= (1ULL << MOSIPIN) | (1ULL << CLKPIN) | (1ULL << CEPIN) | (1ULL << CSPIN);
	output.mode			= GPIO_MODE_OUTPUT;
	output.pull_up_en	= GPIO_PULLUP_DISABLE;
	output.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	output.intr_type	= GPIO_INTR_DISABLE;
	gpio_config(&output);

	// Configure Interrupts
	gpio_config_t interrupt;
	interrupt.pin_bit_mask	= (1ULL << INTPIN);
	interrupt.mode			= GPIO_MODE_INPUT;
	interrupt.pull_up_en	= GPIO_PULLUP_ENABLE;
	interrupt.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	interrupt.intr_type		= GPIO_INTR_NEGEDGE;
	gpio_config(&interrupt);

	// Setup interrupt pin
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(INTPIN, gpio_isr_handler, (void *) INTPIN);

	// MOSI as output and low
	gpio_set_level(MOSIPIN, 0);

	// CLK as output and low
	gpio_set_level(CLKPIN, 0);

	// Enable the chip
	gpio_set_level(CEPIN, 0);

	os_delay_us(1000);

	gpio_set_level(CSPIN, 1);
	
	os_delay_us(65535);
}

unsigned char nrf24l01SPISend(unsigned char data){

	// CS is low
	char result = 0x00;
	char bit = 8;
	while (bit > 0){

		// Read MISO
		result|= (gpio_get_level(MISOPIN) << (bit - 1));

		// Set MOSI
		if ( (data >> (bit - 1)) & 1) {
			// High
			gpio_set_level(MOSIPIN, 1);
		}else{
			// Low
			gpio_set_level(MOSIPIN, 0);
		}

		// Clock Up
		os_delay_us(2);
		gpio_set_level(CLKPIN, 1);

		// Clock Down
		os_delay_us(2);
		gpio_set_level(CLKPIN, 0);

		bit--;
	}

	return result;
}


void nrf24l01SPIStart(void){
	enableInterrupts(0);
    nrf24l01CSLow();
    delayUs(5);
}

void nrf24l01SPIEnd(void){
	enableInterrupts(1);
    delayUs(5);
    nrf24l01CSHigh();
}

void enableInterrupts(unsigned char enable){
    if (enable){
    	//open interrupts
    	// ets_intr_unlock();
    }
    else{
    	//close interrupts
    	// ets_intr_lock();
    }
}

void exception(unsigned char number){
	printf("EXCEPTION: %u\r\n", number);
	// system_restart();
}