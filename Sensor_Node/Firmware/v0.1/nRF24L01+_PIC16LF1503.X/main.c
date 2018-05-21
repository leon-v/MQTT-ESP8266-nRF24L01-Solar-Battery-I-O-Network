#include <xc.h>
#include <pic16lf1503.h>
#include "nrf24l01.h"
#include "flash.h"
#include "config.h"

#include <stdlib.h> 

void interrupt ISR(void){
	nrf24l01ISR();
}

unsigned char mode = 1;
#define SEND_BOOT_MODE 1
#define SEND_ADC3_MODE 2

void sendName(void){
    
    unsigned int offset = 0;
    unsigned char btye;
    while (offset < 16){
        btye = read_flashmem(offset);
        
        if (btye == 0x00){
            return;
        }
        
        nrf24l01SendByte(btye);
        offset++;
    }
}

void sendString(char * string){
    
    int i;
    for (i = 0; string[i] != '\0'; i++){
        nrf24l01SendByte(string[i]);
    }
}
void loop(){
    
    switch (mode){
        case SEND_BOOT_MODE:
            // Write payload data
            
            nrf24l01SendStart();
            sendName();
            nrf24l01SendByte('/');
            nrf24l01SendByte('B');
            nrf24l01SendByte('O');
            nrf24l01SendByte('O');
            nrf24l01SendByte('T');
            nrf24l01SendByte('/');
            nrf24l01SendByte('1');
            nrf24l01SendEnd();
            
            mode = 2;
            break;
            
            
        case SEND_ADC3_MODE:
            
            ADCON0bits.CHS = 3;
            
            __delay_us(50);
            
            ADCON0bits.ADGO = 1;
            
            while (ADCON0bits.ADGO){
                NOP();
            }
            
            
            char buffer[8];
            int result = 0x00;
            result = ADRESL;
            result|= (ADRESH << 8);
            
//            result*= 3;
            
            itoa(buffer, result, 10);
            // 4700
            // 10000
            
            
            nrf24l01SendStart();
            sendName();
            nrf24l01SendByte('/');
            nrf24l01SendByte('A');
            nrf24l01SendByte('D');
            nrf24l01SendByte('C');
            nrf24l01SendByte('3');
            nrf24l01SendByte('/');
            nrf24l01SendByte(buffer[0]);
            nrf24l01SendByte(buffer[1]);
            nrf24l01SendByte(buffer[2]);
            nrf24l01SendByte(buffer[3]);
            nrf24l01SendByte(buffer[4]);
            nrf24l01SendByte(buffer[5]);
            nrf24l01SendByte(buffer[6]);
            nrf24l01SendByte(buffer[7]);
            nrf24l01SendEnd();
    }
    
    __delay_ms(500);
    
}

void main(void) {
    
    INTCONbits.GIE = 0;
    INTCONbits.PEIE = 1;
    
    OSCCONbits.IRCF = 0b1111; // 16 MHz
    OSCCONbits.SCS = 0b10; // Internal oscillator block
    
    __delay_ms(10);
    
    nrf24l01Init();
    
    OPTION_REGbits.nWPUEN = 0;
    

    // Setup SDC
    ADCON0bits.ADON = 0;
   
    ANSELAbits.ANSA4 = 1;
    TRISAbits.TRISA4 = 1;
    
    ADCON1bits.ADCS = 0b111;
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADPREF = 0b00;
    
    ADCON0bits.CHS = 3;
    ADCON0bits.ADON = 1;
  
    INTCONbits.GIE = 1;
    
    while(1){
        loop();
    }
    
    return;
}
