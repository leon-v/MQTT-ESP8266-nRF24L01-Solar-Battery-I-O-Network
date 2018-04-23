#include <xc.h>
#include <pic16lf1503.h>
#include "nrf24l01spi.h"

void nrf24l01SPIInit(nrf24l01SPIData_t spiData){
    
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
       
    PIE1bits.SSP1IE = 1;
    
    SSPCON1bits.SSPEN = 1;
}

unsigned char nrf24l01SPIComplete(nrf24l01SPIData_t spiData){
    return (unsigned char) (spiData.byte == 0);
}

void nrf24l01SPIISR(nrf24l01SPIData_t spiData){
    
    if (!PIR1bits.SSP1IF){
        return;
    }
    
    PIR1bits.SSP1IF = 0;
    
    if (!spiData.byte){
        return;
    }
    
    switch (spiData.byte){
        case 3:
            spiData.status = SSP1BUF;
            SSP1BUF = spiData.request;
            spiData.byte--;
            break;
            
        case 2:
            spiData.result = SSP1BUF;
            SSP1BUF = spiData.request >> 8;
            spiData.byte--;
            break;
        
        case 1:
            spiData.result |= (unsigned int) (SSP1BUF << 8);
            PORTAbits.RA1 = 1;
            spiData.byte--;
            break;
    }
}


void nrf24l01SPISend(nrf24l01SPIData_t spiData){
    
    spiData.byte = 3;
    
    PORTAbits.RA1 = 0;
    SSP1BUF = spiData.command;
}
