#ifndef NRF24L01_PORT_H_
#define	NRF24L01_PORT_H_

#include "rom/ets_sys.h"
#include "driver/gpio.h"

#define delayUs(x) ets_delay_us(x)
#define sleepMs(x) for (int i = x; i >= 0; i--) {ets_delay_us(1000);}

#define PIN_NUM_MISO 12 // Got data OK but crashed when held up
#define PIN_NUM_MOSI 13 // OK
#define PIN_NUM_CLK  14 // OK
#define PIN_NUM_CS   26

#define PIN_NUM_CE	25
#define PIN_NUM_INT	27


#define nrf24l01CELow() gpio_set_level(PIN_NUM_CE, 0); // (high, low, out, in)
#define nrf24l01CEHigh() gpio_set_level(PIN_NUM_CE, 1); // (high, low, out, in)
#define nrf24l01CSLow() gpio_set_level(PIN_NUM_CS, 0); // (high, low, out, in)
#define nrf24l01CSHigh() gpio_set_level(PIN_NUM_CS, 1); // (high, low, out, in)

void nrf24l01InterfaceInit(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);
void enableInterrupts(unsigned char enable);
void exception(unsigned char number);

#endif	/* NRF24L01_PORT_H_ */