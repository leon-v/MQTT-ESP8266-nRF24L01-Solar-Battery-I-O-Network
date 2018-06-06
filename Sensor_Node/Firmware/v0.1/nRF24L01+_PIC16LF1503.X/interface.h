#ifndef HARDWARE_H
#define	HARDWARE_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define _XTAL_FREQ 16000000

void delayUs(unsigned int delay);
void delayMs(unsigned int delay);

void nrf24l01CELow(void);
void nrf24l01CEHigh(void);
void nrf24l01CSLow(void);
void nrf24l01CSHigh(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);


#endif	/* XC_HEADER_TEMPLATE_H */

