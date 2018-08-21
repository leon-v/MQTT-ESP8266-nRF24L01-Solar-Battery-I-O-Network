#ifndef NRF24L01_INTERFACE_H_
#define	NRF24L01_INTERFACE_H_

#include "rom/ets_sys.h"
#include "driver/gpio.h"

#define delayUs(x) os_delay_us(x)

#define CEPIN	4
#define INTPIN	5
#define MISOPIN	12
#define MOSIPIN	13
#define CLKPIN	14
#define CSPIN	15


#define nrf24l01CELow() gpio_set_level(CEPIN, 0); // (high, low, out, in)
#define nrf24l01CEHigh() gpio_set_level(CEPIN, 1); // (high, low, out, in)
#define nrf24l01CSLow() gpio_set_level(CSPIN, 0); // (high, low, out, in)
#define nrf24l01CSHigh() gpio_set_level(CSPIN, 1); // (high, low, out, in)

void nrf24l01InterfaceInit(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);
void enableInterrupts(unsigned char enable);

#endif	/* NRF24L01_INTERFACE_H_ */