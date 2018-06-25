#include "radio_interface.h"

void nrf24l01InterfaceInit(void){

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); // MISO
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); // MOSI
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); // CLK
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15); // CS

	// MISO as input
	gpio_output_set(MISOPIN, 0, 0, MISOPIN);// (high, low, out, in)
	GPIO_DIS_OUTPUT(MISOBIT);

	// MISO as output and low
	gpio_output_set(0, MOSIPIN, MOSIPIN, 0);// (high, low, out, in)

	// CLK as output and low
	gpio_output_set(0, CLKPIN, CLKPIN, 0);// (high, low, out, in)

	// Enable the chip
	gpio_output_set(0, CEPIN, CEPIN, 0);// (high, low, out, in)
	os_delay_us(1000);

	// Set CS inactive
	// (high, low, out, in)
	gpio_output_set(CSPIN, 0, CSPIN, 0);
	
	os_delay_us(65535);
}

i_uint8_t nrf24l01SPISend(i_uint8_t data){

	// CS is low
	uint8 result = 0x00;
	uint8 bit = 8;
	while (bit > 0){

		// Read MISO
		result|= (GPIO_INPUT_GET(MISOBIT) << (bit - 1));

		// Set MOSI
		if ( (data >> (bit - 1)) & 1) {
			// High
			gpio_output_set(MOSIPIN, 0, MOSIPIN, 0);// (high, low, out, in)
		}else{
			// Low
			gpio_output_set(0, MOSIPIN, MOSIPIN, 0);// (high, low, out, in)
		}

		// Clock Up
		os_delay_us(200);
		gpio_output_set(CLKPIN, 0, CLKPIN, 0);// (high, low, out, in)

		// Clock Down
		os_delay_us(200);
		gpio_output_set(0, CLKPIN, CLKPIN, 0);// (high, low, out, in)

		bit--;
	}

	return result;
}


void nrf24l01SPIStart(void){
    nrf24l01CSLow();
    delayUs(100);
}

void nrf24l01SPIEnd(void){
    delayUs(100);
    nrf24l01CSHigh();
}

void enableInterrupts(i_uint8_t enable){
    if (enable){
    	//open interrupts
    	ets_intr_unlock();	 	 
    }
    else{
    	//close interrupts
    	ets_intr_lock();		 
    }
}

void exception(i_uint8_t number){
	os_printf("EXCEPTION: %u\r\n", number);
}