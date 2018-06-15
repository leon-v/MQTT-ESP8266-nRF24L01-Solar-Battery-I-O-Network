#include <xc.h>
#include "nrf24l01.h"
#include "flash.h"
#include "interface.h"

#define SLEEP_MODE          1
#define SUM_ADC_MODE        2
#define SEND_ADC_MODE       3
#define SEND_COUNTER_MODE   4

#define SEND_BOOT_MODE      10
#define RUN_MODE            11
#define START_ADC3_MODE     12
#define START_ADC7_MODE     13
#define START_FVR_MODE      14
#define START_TEMP_MODE     15
#define SEND_INT_MODE       16

unsigned char nextMode = SEND_BOOT_MODE;
unsigned char mode = SEND_BOOT_MODE;

#define ADC_OVERSAMPLE_COUNT 255


unsigned long adcSum = 0;
unsigned char adcLoop = 0;
unsigned char sleepLoop = 0;

// Cahnge ISR to trigger super loop code to do its bidding

void interrupt ISR(void){
    if (PIR1bits.ADIF){
        
        if (mode == SUM_ADC_MODE) {
            
            int result = 0x00;
            result = ADRESL;
            result|= (ADRESH << 8);

            adcSum+= (unsigned) result;
            
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

void startADC(unsigned char channel){
    adcSum = 0;
    adcLoop = ADC_OVERSAMPLE_COUNT;

    if (ADCON0bits.CHS != channel) {
        ADCON0bits.CHS = channel;
        delayUs(200);
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
            
            SLEEP();
            NOP();
            NOP();
                    
            if (!STATUSbits.nTO && !STATUSbits.nPD){
                mode = nextMode;
                sleepLoop = 0;
            }
            
            if (sleepLoop++ > 5){
                RESET();
            }
            break;
            
        case SEND_BOOT_MODE:
            // Write payload data
            strcpy(string, "/BOOT/");
            _itoa(stringAppend, read_flashmem(FLASH_OFFSET_BOOT_COUNT), 10);
            nrf24l01SendString(string, 0);
            mode = RUN_MODE;
            break;
            
        case RUN_MODE:
            mode = SLEEP_MODE;
            nextMode = SEND_COUNTER_MODE;
            break;
            
        case SEND_COUNTER_MODE:
            strcpy(string, "/COUNT/");
            _itoa(stringAppend, counter, 10);
            nrf24l01SendString(string, 0);
            mode = START_ADC3_MODE;
            break;
            
        case START_ADC3_MODE:
               startADC(3);
            
//            if ( (adcSum >= 4200) && (PORTAbits.RA5 == 1) ) {
//                PORTAbits.RA5 = 0;
//            }
//            
//            if ( (adcSum <= 4100) && (PORTAbits.RA5 == 0) ) {
//                PORTAbits.RA5 = 1;
//            }
            nextMode = START_ADC7_MODE;
            break;
        
        case START_ADC7_MODE:
            startADC(7);
            nextMode = START_TEMP_MODE;
            break;
            
        case START_TEMP_MODE:
            startADC(29);
            nextMode = START_FVR_MODE;
            break;
            
        case START_FVR_MODE:
            startADC(31);
            nextMode = RUN_MODE;
            break;

        case SEND_ADC_MODE:
            
            switch (ADCON0bits.CHS){
                case 3:
                    adcSum*= 100;
                    adcSum/= 2505;
                    break;
                    
                case 7:
                    adcSum*= 100;
                    adcSum/= 2500;
                    break;
                 
                case 31:
                    adcSum*= 100;
                    adcSum/= 2475;
                    break;
                    
                 case 29:
                    adcSum/= 2089;
                    adcSum-= 40;
                    break;
                    
                default:
                    adcSum/= 255;
                    break;
            }
            
            strcpy(string, "/ADC");
            _itoa(stringAppend, ADCON0bits.CHS, 10);
            strcpy(stringAppend, "/");
            _itoa(stringAppend, adcSum, 10);
            
            nrf24l01SendString(string, 0);
            

            mode = nextMode;
            break;
            
    }
    
    
}


void main(void) {
    
    // I Always forget to reset that damn ADC
    ANSELA = 0x00;
    ANSELC = 0x00;
    
    // Pin 11 is int
//    RA2
    
    /* Reset Interrupts */
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 0;
    
    OSCCONbits.IRCF = 0b1111; // 16 MHz
    OSCCONbits.SCS = 0b10; // Internal oscillator block
    
    delayMs(10);
    
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
    
    /* Setup Charge Control */
    TRISAbits.TRISA5 = 0;
    PORTAbits.RA5 = 0;
    
    /* Start Interrupts */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
        
    unsigned int bootCount = read_flashmem(FLASH_OFFSET_BOOT_COUNT);
    if (bootCount == 13313){
        bootCount = 1;
    }
    bootCount++;
    write_flashmem(FLASH_OFFSET_BOOT_COUNT, bootCount);
    
    while(1){
        loop();
    }
    
    return;
}
