#include <xc.h>
#include "interface.h"
#include "stdlib.h"


/* nrf24l01 Interfaces */
char string[16];

void nrf24l01InterfaceInit(void){
    
    TRISAbits.TRISA0 = 0; // CE out
    TRISAbits.TRISA1 = 0; // CS out
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    TRISCbits.TRISC0 = 0; // CLK
    
    SSPCON1bits.SSPEN = 0; 
    SSPCON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
    SSPCON1bits.SSPM = 0b0000;
    
    SSPCON1bits.SSPEN = 1;
    
}

#pragma interrupt_level 1
unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    
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

//itoa(buffer, read_flashmem(FLASH_OFFSET_BOOT_COUNT), 10);
void _itoa(char * buffer, unsigned int number, unsigned char base){
    itoa(buffer, number, base);
}
