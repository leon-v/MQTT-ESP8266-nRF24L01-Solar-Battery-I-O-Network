#ifndef INTERFACE_H_
#define	INTERFACE_H_

#include "osapi.h"
#include "gpio.h"

#define i_uint8_t uint8
#define i_int8_t int8

#define delayUs(x) os_delay_us(x)

#define MISOPIN	BIT12
#define MISOBIT	12
#define MOSIPIN	BIT13
#define CLKPIN	BIT14
#define CEPIN	BIT4
#define CSPIN	BIT15

#define nrf24l01CELow() gpio_output_set(0, CEPIN, CEPIN, 0); // (high, low, out, in)
#define nrf24l01CEHigh() gpio_output_set(CEPIN, 0, CEPIN, 0); // (high, low, out, in)
#define nrf24l01CSLow() gpio_output_set(0, CSPIN, CSPIN, 0); // (high, low, out, in)
#define nrf24l01CSHigh() gpio_output_set(CSPIN, 0, CSPIN, 0); // (high, low, out, in)

void nrf24l01InterfaceInit(void);
i_uint8_t nrf24l01SPISend(i_uint8_t data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);

void enableInterrupts(i_uint8_t enable);

#endif	/* INTERFACE_H_ */