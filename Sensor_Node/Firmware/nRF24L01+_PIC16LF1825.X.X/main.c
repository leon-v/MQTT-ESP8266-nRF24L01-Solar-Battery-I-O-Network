#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "nrf24l01.h"
#include "interface.h"
#include "../../../../shared.h"

unsigned char sleepLoop = 0;
unsigned long counter = 0;

// Cahnge ISR to trigger super loop code to do its bidding

void interrupt ISR(void){    
    
    if (PIR0bits.INTF){
        nrf24l01ISR();
        PIR0bits.INTF = 0;
    }
}

void sleep(unsigned char wdps){
    
    WDTCONbits.WDTPS = wdps; //9=500ms, 10=1S, 11=2S, 12=4S
    
	while (1){
        
		SLEEP();
		NOP();
		NOP();

		if (!STATUSbits.nTO && !STATUSbits.nPD) {
            
            //Reset WDT to wait for IC failure
            WDTCONbits.WDTPS = 13;
            CLRWDT();
            
			return;
		}
	}
}

float getADCValue(unsigned char channel){
    
    #define ADC_COUNT 1000
	float adcSum = 0;
	unsigned int adcLoop = ADC_COUNT;
	
	ADCON0bits.CHS = channel;
    FVRCONbits.FVREN = 1; // Enable Voltage Reference Module
    ADCON0bits.ADON = 1;
    
	sleep(0);
	
    counter = 0;
    
	while (adcLoop--){
        
        counter++;
		
		ADCON0bits.ADGO = 1;
       
		while (ADCON0bits.ADGO){
            sleep(0);
		}
		
		adcSum+= (ADRESL | (ADRESH << 8));
        
	}
    
    FVRCONbits.FVREN = 0; // Disable Voltage Reference Module
    ADCON0bits.ADON = 0;
    
    
	adcSum/= ADC_COUNT; // Adjust to get average
    adcSum/= 500; // adjust for FVR +REF @ 2.048 to get volts
	
	return adcSum;
}



void checkRxData(void){
	
	nrf24l01SetRXMode(1);
	
	sleep(10);
	
	if (!nrf24l01.RXPending){
		return;
	}

}

void setMessage(nrf24l01Packet_t * packet, const char * topic, float value){
    memset(packet->Message, 0, sizeof(packet->Message));
    
    strcat(packet->Message, romData->name);
    
    strcat(packet->Message, "/");
    strcat(packet->Message, topic);
    
	int status;
    strcat(packet->Message, "/");
    strcat(packet->Message, ftoa(value, &status));
}

void checkTXPower(){
    nrf24l01Packet_t * rxPacket = nrf24l01GetRXPacket();
    
    if (rxPacket->packetData.ACKRPD){
        nrf24l01ChangeTXPower(-1);
    }
}

void loop(){
    
    nrf24l01Packet_t packet;
    
//    setMessage(&packet, "DBG", counter);
//    packet.packetData.byte = 0;
//    packet.packetData.ACKRequest = 0;
//	nrf24l01SendPacket(&packet);
//    checkTXPower();
//	sleep(10);
    
    //Resistor divider on Vbatt
    // 10K / 4.7K  = 2.127659574468085
    // * 1.46 for unknown reasons. Maybe ADC pin sinkign current
    setMessage(&packet, "VBAT", getADCValue(0b000100) * 3.106382978723404);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep(10);
    
    
//    setMessage(&packet, "ANC3mV", getADCValue(0b010011));
//    packet.packetData.byte = 0;
//    packet.packetData.ACKRequest = 1;
//	nrf24l01SendPacket(&packet);
//    checkTXPower();
//	sleep(10);
    
    FVRCONbits.TSEN = 1;
    float vt = (2.048 - getADCValue(0b111101)) / 2;
    FVRCONbits.TSEN = 0;
    
    #define vf 0.6063
    #define tc -0.00132
    float ta = (vt / tc) - (vf / tc) - 40;
    
    
    
	setMessage(&packet, "TEMP", ta);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep(10);
    
    FVRCONbits.TSEN = 1;
	setMessage(&packet, "TEMPR", getADCValue(0b111101));
    FVRCONbits.TSEN = 0;
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep(10);
    
//    n_RF_SETUP_t rfSetup;
//    rfSetup.byte = nrf24l01Send(n_R_REGISTER | n_RF_SETUP, 0);
//    
//    setMessage(&packet, "RFPWR", rfSetup.RF_PWR);
//    packet.packetData.byte = 0;
//    packet.packetData.ACKRequest = 1;
//	nrf24l01SendPacket(&packet);
//    checkTXPower();
//	sleep(10);
    
	
//	checkRxData();
}

 unsigned char nrf24l01GetPipe(char * name){
     unsigned char pipe = 0;
     unsigned char i = 0;
    
     // Calculate a pipe from the name passed
     for (i = 0; i < strlen(name); i++){
         pipe+= name[i];
     }
     
     return (unsigned) pipe % 6;
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
    
    memcpy(romDataMap.bytes, resetRomData.bytes, sizeof(romDataMap_t.bytes));
//    flashRealod();
	
	// This is broken! Use EEPRON since now we have it
//	if (romData.check != ENV_FLASH_VERSION){
//		romData.check = ENV_FLASH_VERSION;
//		strcpy(romData.name, ENV_DEVICE_NAME);
//		romData.bootMode = 0x00;
//		flashUpdate();
//	}
    
//    strcpy(romData.name, ENV_DEVICE_NAME);
    
//    flashRealod();
    
    nrf24l01Init();
    
    unsigned char pipe = nrf24l01GetPipe(romData.name);
    nrf24l01SetTXPipe(pipe);
    nrf24l01SetRXPipe(pipe);
    

    /* Setup ADC */
    ADCON0bits.ADON = 0;
   
    //ANA4
    PORTAbits.RA4 = 0;
    TRISAbits.TRISA4 = 1;
    WPUAbits.WPUA4 = 0;
    ODCONAbits.ODCA4 = 1;
    ANSELAbits.ANSA4 = 1;
    
    //ANC3
    ANSELCbits.ANSC3 = 1;
    TRISCbits.TRISC3 = 1;
    
    /* Configure Temp sensor*/
    FVRCONbits.TSEN = 1;
    FVRCONbits.TSRNG = 1;
    
    /* Configure FVR */
    FVRCONbits.FVREN = 0; // Disable Voltage Reference Module
    FVRCONbits.ADFVR = 0b10; // 2.048V
    
    ADCON1bits.ADCS = 0b111;    
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADPREF = 0b11; // FVR used as + ref
    ADCON1bits.ADNREF = 0b00; // GND used as - ref
    
    
    ADCON0bits.CHS = 3;
    
    
    /* Setup Interrupt Pin */
//	RA2PPSbits.RA2PPS = 0b00010;// A2
    TRISAbits.TRISA2 = 1;
    PIE0bits.INTE = 1;
    INTCONbits.INTEDG = 0;
    
    /* Setup Charge Control */
    TRISAbits.TRISA5 = 0;
    PORTAbits.RA5 = 0;
    
    /* Start Interrupts */
    INTCONbits.PEIE = 1;
    INTCONbits.GIE = 1;
    
    nrf24l01Packet_t packet;
        
    setMessage(&packet, "BOOT", romData.bootMode);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 0;
	nrf24l01SendPacket(&packet);
	sleep(10);
    
    while(1){
        loop();
    }
    
    return;
}
