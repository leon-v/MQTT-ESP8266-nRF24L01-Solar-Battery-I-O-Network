#include <xc.h>
#include <pic16lf1503.h>
#include "nrf24l01.h"
#include "flash.h"
#include "config.h"

#include <stdlib.h> 


unsigned char nextMode = 1;
unsigned char mode = 1;

#define SEND_BOOT_MODE      1
#define RUN_MODE            2
#define START_ADC3_MODE     3
#define START_ADC7_MODE     4
#define START_FVR_MODE      5
#define START_TEMP_MODE     6

#define SLEEP_MODE          7

#define SUM_ADC_MODE        100
#define SEND_ADC_MODE       101

#define ADC_OVERSAMPLE_COUNT 255


long adcSum = 0;
unsigned char adcLoop = 0;
char buffer[6];
char byte[3];

void interrupt ISR(void){
    
    if (PIR1bits.ADIF){
        
        if (mode == SUM_ADC_MODE) {
            
            int result = 0x00;
            result = ADRESL;
            result|= (ADRESH << 8);

            adcSum+= result;
            
            if (!adcLoop){
                mode = SEND_ADC_MODE;
            }else{
                
                ADCON0bits.ADGO = 1;
            }
            
            adcLoop--;
        }
        
        
        PIR1bits.ADIF = 0;
    }
    
    if (INTCONbits.INTF){
        nrf24l01ISR();
        INTCONbits.INTF = 0;
    }
}


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
    
    unsigned char i;
    for (i = 0; string[i] != '\0'; i++){
        nrf24l01SendByte(string[i]);
    }
}

void startADC(unsigned char channel){
    adcSum = 0;
    adcLoop = ADC_OVERSAMPLE_COUNT;

    if (ADCON0bits.CHS != channel) {
        ADCON0bits.CHS = channel;
        __delay_us(200);
    }

    ADCON0bits.ADGO = 1;
    mode = SUM_ADC_MODE;
}
void loop(){
    
    if (mode != SLEEP_MODE) {
        CLRWDT();
    }
    
    switch (mode){
        
        case SLEEP_MODE:
//            nrf24l01SetRecieveMode();
            SLEEP();
            NOP();
            NOP();
            if (!STATUSbits.nTO && !STATUSbits.nPD){
                mode = nextMode;
            }
            break;
            
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
            
            mode = RUN_MODE;
            break;
            
            
        case RUN_MODE:
            mode = SLEEP_MODE;
            nextMode = START_ADC3_MODE;
            break;
            
        case START_ADC3_MODE:
            startADC(3);
            nextMode = START_ADC7_MODE;
            break;
        
        case START_ADC7_MODE:
            startADC(7);
            nextMode = START_FVR_MODE;
            break;
            
        case START_FVR_MODE:
            startADC(31);
            nextMode = START_TEMP_MODE;
            break;
            
        case START_TEMP_MODE:
            startADC(29);
            nextMode = RUN_MODE;
            break;

        case SEND_ADC_MODE:
            
            switch (ADCON0bits.CHS){
                case 3:
                    adcSum/= 22;
                    break;
                    
                case 7:
                    adcSum/= 25;
                    break;
                 
                case 31:
                    adcSum=  (long) (( (float) adcSum) / 24.8);
                    break;
                    
                 case 29:
                    adcSum/= 2089;
                    adcSum-= 40;
                    break;
                    
                default:
                    adcSum/= 255;
                    break;
            }
            
            itoa(buffer, adcSum, 10);
            itoa(byte, ADCON0bits.CHS, 10);
            
            nrf24l01SendStart();
            sendName();
            nrf24l01SendByte('/');
            nrf24l01SendByte('A');
            nrf24l01SendByte('D');
            nrf24l01SendByte('C');
            sendString(byte);
            nrf24l01SendByte('/');
            
            unsigned char i;
            for (i = 0; buffer[i] != '\0'; i++){
                nrf24l01SendByte(buffer[i]);
            }
            
            nrf24l01SendEnd();

            mode = nextMode;
            break;
            
    }
    
    
}


void main(void) {
    
    // Pin 11 is int
//    RA2
    
    /* Reset Interrupts */
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 0;
    
    OSCCONbits.IRCF = 0b1111; // 16 MHz
    OSCCONbits.SCS = 0b10; // Internal oscillator block
    
    __delay_ms(10);
    
    nrf24l01Init();
    
    OPTION_REGbits.nWPUEN = 0;
    
    /* Configure FVR */
    FVRCONbits.FVREN = 0;
    FVRCONbits.ADFVR = 1; // 1.024V
    FVRCONbits.FVREN = 1;
    
    /* Configure Temp sensor*/
    FVRCONbits.TSEN = 0;
    FVRCONbits.TSRNG = 0; // 2V Low Range
    FVRCONbits.TSEN = 1;

    /* Setup ADC */
    ADCON0bits.ADON = 0;
   
    ANSELAbits.ANSA4 = 1;
    TRISAbits.TRISA4 = 1;
    WPUAbits.WPUA4 = 0;
    
    ANSELCbits.ANSC3 = 1;
    TRISCbits.TRISC3 = 1;
    
    ADCON1bits.ADCS = 0b111;
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADPREF = 0b00;
    
    PIE1bits.ADIE = 1;
    
    ADCON0bits.CHS = 3;
    ADCON0bits.ADON = 1;
    
    
    /* Setup Interrupt Pin */
    TRISAbits.TRISA2 = 1;
    INTCONbits.INTE = 1;
    OPTION_REGbits.INTEDG = 0;
            
    
    /* Setup WDT*/
    WDTCONbits.WDTPS = 12;
    
    
    /* Start Interrupts */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    
    while(1){
        loop();
    }
    
    return;
}
