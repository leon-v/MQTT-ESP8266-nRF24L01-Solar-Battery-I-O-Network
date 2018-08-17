#include <xc.h>
#include "interface.h"


/* nrf24l01 Interfaces */


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
    SSP1CON1bits.SSPM = 0b0001;
    
    SSP1CON1bits.SSPEN = 1;
    
}

void resetWDT(void){
	WDTCONbits.WDTPS = 0b01100; // 4s
    CLRWDT();
}

void sleepMs(unsigned int milliseconds){
	
	unsigned char wdtps;
	for (wdtps = 0; wdtps <= 0b10010; wdtps++){
		if ((milliseconds >> wdtps) & 0b1){
START_SLEEP:
			WDTCONbits.WDTPS = wdtps;
			SLEEP();
			NOP();
			NOP();

			if( STATUSbits.nTO || STATUSbits.nPD){
				goto START_SLEEP;
			}
		}
	}
	
	resetWDT();
}

unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    
    PORTCbits.RC4 = 1;
    
    while (!SSP1STATbits.BF){
        NOP();
    }
    
    return SSP1BUF;
}

void nrf24l01SPIStart(void){
	enableInterrupts(0);
    nrf24l01CSLow();
    delayUs(10);
}

void nrf24l01SPIEnd(void){
    delayUs(10);
    nrf24l01CSHigh();
	enableInterrupts(1);
}

void exception(unsigned char exception){
    RESET();
}
