#include <xc.h>
#include <pic16lf1503.h>
#include "nrf24l01.h"

void interrupt ISR(void){
	nrf24l01ISR();
}

void loop(){
    
    
}

void main(void) {
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 1;
    
    OSCCONbits.IRCF = 0b1111; // 16 MHz
    OSCCONbits.SCS = 0b10; // Internal oscillator block
    
    nrf24l01Init();
    
    INTCONbits.GIE = 1;
    
    while(1){
        loop();
    }
    
    return;
}
