#include <xc.h>
#include <pic16lf1503.h>
#include "nrf24l01spi.h"

void nrf24l01SPIInit(){
    
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
}

n_STATUS_t status;
unsigned char nrf24l01SPISend(unsigned char byte1, unsigned char byte2){
    
    PORTAbits.RA1 = 0;
    
    SSP1BUF = byte1;
    
    while (!SSP1STATbits.BF){ NOP(); }
    
    status.byte = SSP1BUF;
    
    SSP1BUF = byte2;
    
    while (!SSP1STATbits.BF){ NOP(); }
    
    PORTAbits.RA1 = 0;
    
    return SSP1BUF;
}
