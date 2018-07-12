#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "nrf24l01.h"
#include "flash.h"
#include "interface.h"

unsigned char sleepLoop = 0;
unsigned int counter = 0;
char tempString[16];

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
//	adcSum*= adcLoop;
    
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

void setName(void){
    memset(nrf24l01TXBuffer, 0, sizeof(nrf24l01TXBuffer));
    strcat(nrf24l01TXBuffer, romData.name);
    strcat(nrf24l01TXBuffer, "/");
}
void loop(){
    
	// Write payload data
    CLRWDT();
    
    setName();
    utoa(tempString, counter, 10);
    strcat(nrf24l01TXBuffer, "DBG/");
    strcat(nrf24l01TXBuffer, tempString);
    counter = 0;
    nrf24l01TXPacketData.byte = 0;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
    
    setName();
    utoa(tempString, getADCValue(0b000100, 2505), 10);
    strcat(nrf24l01TXBuffer, "VBAT/");
    strcat(nrf24l01TXBuffer, tempString);
    nrf24l01TXPacketData.byte = 0;
    nrf24l01TXPacketData.ACKRequest = 1;
	nrf24l01SendString();
	sleep();
    
    setName();
    utoa(tempString, getADCValue(0b010011, 2500), 10);
    strcat(nrf24l01TXBuffer, "ANC3/");
    strcat(nrf24l01TXBuffer, tempString);
    nrf24l01TXPacketData.byte = 0;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
    
    setName();
    utoa(tempString, getADCValue(0b111111, 208900) - 40, 10);
    strcat(nrf24l01TXBuffer, "FVR/");
    strcat(nrf24l01TXBuffer, tempString);
    nrf24l01TXPacketData.byte = 0;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
    
    setName();
    utoa(tempString, getADCValue(0b111101, 2475), 10);
    strcat(nrf24l01TXBuffer, "TEMP/");
    strcat(nrf24l01TXBuffer, tempString);
    nrf24l01TXPacketData.byte = 0;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
	
//	checkRxData();
}

void main(void) {
    
    // I Always forget to reset that damn ADC
    ANSELA = 0x00;
    ANSELC = 0x00;
    
    ODCONA = 0x00;
    ODCONC = 0x00;
    
//    SLRCONA = 0x00;
//    SLRCONC = 0x00;
    
    INLVLA = 0x00;
    INLVLC = 0x00;
    
    WPUA = 0x00;
    WPUC = 0x00;
    
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC4 = 0;
    
    PORTCbits.RC4 = 0;
   
    
    // Pin 11 is int
//    RA2
    
    /* Reset Interrupts */
    INTCONbits.PEIE = 0;
    INTCONbits.GIE = 0;
    
    OSCCON1bits.NOSC = 0b000; // HFINTOSC with 2x PLL (32 MHz)
    OSCCON1bits.NDIV = 0b000;
    
    delayMs(10);
    
    flashRealod();
	
	#define ROM_DATA_VERSION 0x05

	if (romData.check != ROM_DATA_VERSION){
		romData.check = ROM_DATA_VERSION;
		strcpy(romData.name, "UW1");
		romData.bootMode = 0x00;
		flashUpdate();
	}
    
    nrf24l01Init(0);
    
    
//    OPTION_REGbits.nWPUEN = 0;
    

    /* Setup ADC */
    ADCON0bits.ADON = 0;
   
    //ANA4
    ANSELAbits.ANSA4 = 1;
    TRISAbits.TRISA4 = 1;
    WPUAbits.WPUA4 = 0;
    
    //ANC3
    ANSELCbits.ANSC3 = 1;
    TRISCbits.TRISC3 = 1;
    
    /* Configure Temp sensor*/
    FVRCONbits.TSEN = 0;
    FVRCONbits.TSRNG = 0; // 2V Low Range
    FVRCONbits.TSEN = 1;
    
    /* Configure FVR */
    FVRCONbits.FVREN = 0; // Disable Voltage Reference Module
    FVRCONbits.ADFVR = 1; // 1.024V
    FVRCONbits.FVREN = 1; // Enable Voltage Reference Module
    
    ADCON1bits.ADCS = 0b111;
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADPREF = 0b00;
    
    ADCON0bits.CHS = 3;
    ADCON0bits.ADON = 1;
    
    
    /* Setup Interrupt Pin */
//	RA2PPSbits.RA2PPS = 0b00010;// A2
    TRISAbits.TRISA2 = 1;
    PIE0bits.INTE = 1;
    INTCONbits.INTEDG = 0;
            
    
    /* Setup WDT*/
    WDTCONbits.WDTPS = 10; //10=1S, 11=2S, 12=4S
    
    /* Setup Charge Control */
    TRISAbits.TRISA5 = 0;
    PORTAbits.RA5 = 0;
    
    /* Start Interrupts */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
	
    setName();
    utoa(tempString, romData.bootMode, 10);
    strcat(nrf24l01TXBuffer, "BOOT/");
    strcat(nrf24l01TXBuffer, tempString);
    nrf24l01TXPacketData.byte = 0;
    nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01SendString();
	sleep();
    
    while(1){
        loop();
    }
    
    return;
}
