#include <xc.h>
#include "interface.h"


/* nrf24l01 Interfaces */
#pragma interrupt_level 1
void nrf24l01CELow(void){
    PORTAbits.RA0 = 0;
}

#pragma interrupt_level 1
void nrf24l01CEHigh(void){
    PORTAbits.RA0 = 1;
}

#pragma interrupt_level 1
void nrf24l01CSLow(void){
    PORTAbits.RA1 = 0;
}

#pragma interrupt_level 1
void nrf24l01CSHigh(void){
    PORTAbits.RA1 = 1;
}

#pragma interrupt_level 1
void nrf24l01InterfaceInit(void){
    
    TRISAbits.TRISA0 = 0; // CE out
    TRISAbits.TRISA1 = 0; // CS out
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    TRISCbits.TRISC0 = 0; // CLK
    
    SSP1CON1bits.SSPEN = 0; 
	
	RC1PPSbits.RC1PPS = 0b10001;
	RC2PPSbits.RC2PPS = 0b11001;
	RC0PPSbits.RC0PPS = 0b11000;
	
    SSP1CON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
    SSP1CON1bits.SSPM = 0b0000;
    
    SSP1CON1bits.SSPEN = 1;
    
}

#pragma interrupt_level 1
unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    
    PORTCbits.RC4 = 1;
    
    while (!SSP1STATbits.BF){
        NOP();
    }
    
    return SSP1BUF;
}

#pragma interrupt_level 1
void nrf24l01SPIStart(void){
    nrf24l01CSLow();
    delayUs(10);
}

#pragma interrupt_level 1
void nrf24l01SPIEnd(void){
    delayUs(10);
    nrf24l01CSHigh();
}

#pragma interrupt_level 1
void enableInterrupts(unsigned char enable){
    PIE0bits.INTE = enable;
}

void exception(unsigned char exception){
    RESET();
}
