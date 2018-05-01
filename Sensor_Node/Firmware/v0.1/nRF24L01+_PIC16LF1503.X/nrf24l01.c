#include <xc.h>
#include <pic16lf1503.h>
#include "nRF24L01+_types.h"
#include "nrf24l01.h"



void nrf24l01ISR(void){
    
}

n_STATUS_t status;
unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    PORTAbits.RA1 = 0;
    
    SSP1BUF = command;
    
    while (!SSP1STATbits.BF){ NOP(); }
    
    status.byte = SSP1BUF;
    
    SSP1BUF = data;
    
    while (!SSP1STATbits.BF){ NOP(); }
    
    PORTAbits.RA1 = 1;
    
    return SSP1BUF;
}

void nrf24l01SendFlash(unsigned char command, unsigned int offset, unsigned int length){
    
    PORTAbits.RA1 = 0;
    
    SSP1BUF = command;
    
    while (!SSP1STATbits.BF){ NOP(); }
    
    status.byte = SSP1BUF;
    
    unsigned char unused;
    unsigned int counter = 0;
    while (counter < length){
        
        // Read from flash and push into radio
        // Flash is 14 bits wide, and ASCII only uses 7, so 2 ASCII characters
        // can fit per read
        SSP1BUF = 0xAA;
        while (!SSP1STATbits.BF){ NOP(); }
        unused = SSP1BUF;
        counter++;
    }
    
    PORTAbits.RA1 = 1;
    
}

void nrf24l01Init(void){
    
    
    /* SPI INIT */
    TRISAbits.TRISA1 = 0; // CS out
    PORTAbits.RA1 = 1;
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    
    TRISCbits.TRISC0 = 0; // CLK
    
    SSPCON1bits.SSPEN = 0; 
    SSPCON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
    SSP1STATbits.CKE = 0;
    SSPCON1bits.SSPM = 0b0000;
    
    SSPCON1bits.SSPEN = 1;
    
    n_CONFIG_t config;
	config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
	config.PRIM_RX = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    // Write my address to the module from flash
    nrf24l01SendFlash(n_W_REGISTER | n_TX_ADDR, 0, 5);
    
}

