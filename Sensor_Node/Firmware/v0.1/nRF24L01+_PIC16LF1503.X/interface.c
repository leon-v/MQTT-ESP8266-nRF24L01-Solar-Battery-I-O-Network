#include "interface.h"

#pragma interrupt_level 1
void delayUs(unsigned int delay){
    __delay_us(delay);
}

#pragma interrupt_level 1
void delayMs(unsigned int delay){
    __delay_ms(delay);
}


/* nrf24l01 Interface */

#define NRF24L01_CEPIN PORTAbits.RA0
#define NRF24L01_CSPIN PORTAbits.RA1

void nrf24l01CELow(void){
    NRF24L01_CEPIN = 0;
}

void nrf24l01CEHigh(void){
    NRF24L01_CEPIN = 1;
}

void nrf24l01CSLow(void){
    NRF24L01_CSPIN = 0;
}

void nrf24l01CSHigh(void){
    NRF24L01_CSPIN = 1;
}

unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    while (!SSP1STATbits.BF){ NOP(); }
    return SSP1BUF;
}

void nrf24l01SPIStart(void){
    nrf24l01CSLow();
    delayUs(10);
}

void nrf24l01SPIEnd(void){
    delayUs(10);
    nrf24l01CSHigh();
}