#ifndef INTERFACE_H
#define	INTERFACE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <string.h>

#define _XTAL_FREQ 16000000

#define delayUs(x) __delay_us(x)
#define delayMs(x) __delay_ms(x)

extern char string[16];
#define stringAppend string + strlen(string)

#define nrf24l01CELow() PORTAbits.RA0 = 0
#define nrf24l01CEHigh() PORTAbits.RA0 = 1
#define nrf24l01CSLow() PORTAbits.RA1 = 0
#define nrf24l01CSHigh() PORTAbits.RA1 = 1

void nrf24l01InterfaceInit(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);

void enableInterrupts(unsigned char enable);

void _itoa(char * buffer, unsigned int number, unsigned char base);

#endif	/* INTERFACE_H */

