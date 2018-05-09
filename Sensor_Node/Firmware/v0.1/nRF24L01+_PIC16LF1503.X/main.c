#include <xc.h>
#include <pic16lf1503.h>
#include "nrf24l01.h"
#include "flash.h"
#include "config.h"

void interrupt ISR(void){
	nrf24l01ISR();
}

unsigned char mode = 1;
#define SEND_BOOT_MODE 1

void loop(){
    
    switch (mode){
        case SEND_BOOT_MODE:
            // Write payload data
            nrf24l01SendStart();
            unsigned char payloadByte = 'A';
            while (payloadByte < ('A' + 8) ){
                nrf24l01SendByte(payloadByte);
                payloadByte++;
            }
            nrf24l01SendEnd();
            break;
    }
    
    __delay_ms(500);
    
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
