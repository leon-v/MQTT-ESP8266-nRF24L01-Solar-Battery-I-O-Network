#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "nrf24l01.h"
#include "flash.h"
#include "interface.h"

unsigned char sleepLoop = 0;
unsigned int counter = 0;

// Cahnge ISR to trigger super loop code to do its bidding

void interrupt ISR(void){    
    if (PIR0bits.INTF){
        nrf24l01ISR();
        PIR0bits.INTF = 0;
    }
}

unsigned long getADCValue(unsigned char channel, unsigned long divider){
	
	unsigned long adcSum = 0;
	unsigned char adcLoop = 255;
	
	ADCON0bits.CHS = channel;
	delayUs(200);
	
	while (--adcLoop){
		
		ADCON0bits.ADGO = 1;
		while (ADCON0bits.ADGO){
			NOP();
		}
		
		adcSum+= ADRESL;
		adcSum+= (unsigned) (ADRESH << 8);
	}
	
	adcSum*= 100;
	adcSum/= divider;
	
	return adcSum;
}

void sleep(){
	while (1){
		
		SLEEP();
		NOP();
		NOP();

		if (!STATUSbits.nTO && !STATUSbits.nPD) {
			return;
		}
	}
}

void checkRxData(void){
	
	nrf24l01SetRXMode(1);
	
	sleep();
	
	if (!nrf24l01.RXPending){
		return;
	}

}

void loop(){
    
	// Write payload data

	strcpy(nrf24l01TXTopic, "DBG");
	utoa(nrf24l01TXValue, counter, 10);
    counter = 0;
    nrf24l01TXPacketData.byte = 0x00;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();

	strcpy(nrf24l01TXTopic, "ADC3");
	utoa(nrf24l01TXValue, getADCValue(3, 2505), 10);
    nrf24l01TXPacketData.byte = 0x00;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();

	strcpy(nrf24l01TXTopic, "ADC7");
	utoa(nrf24l01TXValue, getADCValue(7, 2500), 10);
    nrf24l01TXPacketData.byte = 0x00;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();

	strcpy(nrf24l01TXTopic, "ADC29");
	utoa(nrf24l01TXValue, getADCValue(29, 208900) - 40, 10);
    nrf24l01TXPacketData.byte = 0x00;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();

	strcpy(nrf24l01TXTopic, "ADC31");
	utoa(nrf24l01TXValue, getADCValue(31, 2475), 10);
    nrf24l01TXPacketData.byte = 0x00;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
	
//	checkRxData();
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
    
    OSCCON1bits.NOSC = 0b000; // HFINTOSC with 2x PLL (32 MHz)
    OSCCON2bits.COSC = 0b000; // HFINTOSC with 2x PLL (32 MHz)
    
    OSCCON1bits.NDIV = 0b000;
    OSCCON2bits.CDIV = 0b000;
    
    delayMs(10);
    
    nrf24l01Init(0);
	
	for (unsigned char i = 0; i < sizeof(nrf24l01TXName); i++){
		nrf24l01TXName[i] = read_flashmem((unsigned) FLASH_OFFSET_NAME + i);
	}
    
//    OPTION_REGbits.nWPUEN = 0;
    
    /* Configure FVR */
    FVRCONbits.FVREN = 0; // Disable Voltage Reference Module
    FVRCONbits.ADFVR = 1; // 1.024V
    FVRCONbits.FVREN = 1; // Enable Voltage Reference Module
    
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
    
    ADCON0bits.CHS = 3;
    ADCON0bits.ADON = 1;
    
    
    /* Setup Interrupt Pin */
    TRISAbits.TRISA2 = 1;
    PIE0bits.INTE = 1;
    INTCONbits.INTEDG = 0;
            
    
    /* Setup WDT*/
    WDTCONbits.WDTPS = 11;
    
    /* Setup Charge Control */
    TRISAbits.TRISA5 = 0;
    PORTAbits.RA5 = 0;
    
    /* Start Interrupts */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
	
	strcpy(nrf24l01TXTopic, "BOOT");
	utoa(nrf24l01TXValue, read_flashmem(FLASH_OFFSET_BOOT_REASON), 10);
    nrf24l01TXPacketData.byte = 0x00;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
    
    while(1){
        loop();
    }
    
    return;
}
