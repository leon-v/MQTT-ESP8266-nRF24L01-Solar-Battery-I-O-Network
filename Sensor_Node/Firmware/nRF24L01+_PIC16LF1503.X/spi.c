#include <xc.h>
#include <pic16lf1503.h>

void SPIInit(void){
    TRISAbits.TRISA1 = 0; // CS out
    PORTAbits.RA1 = 1;
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    
    SSPCON1bits.SSPEN = 0; 
    SSPCON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
    SSP1STATbits.CKE = 0;
    SSPCON1bits.SSPM = 0b0000;
    SSPCON1bits.SSPEN = 1;
}

unsigned char status;
unsigned int SPISend(unsigned int command){
    
}