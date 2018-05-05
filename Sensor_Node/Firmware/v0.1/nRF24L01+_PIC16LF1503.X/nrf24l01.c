#include <xc.h>
#include <pic16lf1503.h>
#include "nRF24L01+_types.h"
#include "nrf24l01.h"
#include "config.h"


void nrf24l01ISR(void){
    
}

n_STATUS_t status;
unsigned char pipe = 1;
void nrf24l01SPIStart(void){
    PORTAbits.RA1 = 0;
}

unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    while (!SSP1STATbits.BF){ NOP(); }
    data = SSP1BUF;
    return data;
}

void nrf24l01SPIEnd(void){
    PORTAbits.RA1 = 1;
}

unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    nrf24l01SPIStart();
    
    status.byte = nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    return data;
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

void nrf24l01SetPipe(unsigned char pipe){
    
    // Set TX_ADDR
    nrf24l01SPIStart();
    status.byte = nrf24l01SPISend(n_W_REGISTER | n_TX_ADDR);
    nrf24l01SPISend(n_ADDRESS_P1[0]);
    nrf24l01SPISend(n_ADDRESS_P1[1]);
    nrf24l01SPISend(n_ADDRESS_P1[2]);
    nrf24l01SPISend(n_ADDRESS_P1[3]);
    nrf24l01SPISend(n_ADDRESS_P1[4] + (unsigned) (pipe * n_ADDRESS_MUL));
    nrf24l01SPIEnd();
    
    // Set RX pipe
    nrf24l01SPIStart();
    status.byte = nrf24l01SPISend(n_W_REGISTER | n_RX_ADDR_P0);
    nrf24l01SPISend(n_ADDRESS_P1[0]);
    nrf24l01SPISend(n_ADDRESS_P1[1]);
    nrf24l01SPISend(n_ADDRESS_P1[2]);
    nrf24l01SPISend(n_ADDRESS_P1[3]);
    nrf24l01SPISend(n_ADDRESS_P1[4] + (unsigned) (pipe * n_ADDRESS_MUL));
    nrf24l01SPIEnd();
}
void nrf24l01Init(void){
    
    // 11 INT
    // 12 CS
    // 13 CE
    
    TRISAbits.TRISA0 = 0; // CE out
    PORTAbits.RA0 = 0;
    
    /* SPI INIT */
    TRISAbits.TRISA1 = 0; // CS out
    PORTAbits.RA1 = 1;
    
    TRISAbits.TRISA1 = 0; // CS out
    PORTAbits.RA1 = 1;
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    
    TRISCbits.TRISC0 = 0; // CLK
    
    SSPCON1bits.SSPEN = 0; 
    SSPCON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
//    SSP1STATbits.CKE = 0;
    SSPCON1bits.SSPM = 0b0000;
    
    SSPCON1bits.SSPEN = 1;
    
    // Clear config bit
    n_CONFIG_t config;
	config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
	config.PRIM_RX = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    nrf24l01SetPipe(pipe);
    
    // Write payload data
    nrf24l01SPIStart();
    nrf24l01SPISend(n_W_TX_PAYLOAD);
        
    unsigned char payloadByte = 'A';
    while (payloadByte < ('A' + 8) ){
        nrf24l01SPISend(payloadByte);
        payloadByte++;
    }
    
    nrf24l01SPIEnd();
    
    
    PORTAbits.RA0 = 1;
    __delay_us(10);
    PORTAbits.RA0 = 0;
    
    __delay_ms(500);
}

