#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "nrf24l01.h"
#include "flash.h"
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
        
        counter++;
        
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

void setMessage(nrf24l01Packet_t * packet, const char * topic, unsigned long value){
    memset(packet->Message, 0, sizeof(packet->Message));
    
    strcat(packet->Message, romData.name);
    
    strcat(packet->Message, "/");
    strcat(packet->Message, topic);
            
    char tempString[16];
    
    ultoa(tempString, value, 10);
    
    strcat(packet->Message, "/");
    strcat(packet->Message, tempString);
}

void checkTXPower(){
    nrf24l01Packet_t * rxPacket = nrf24l01GetRXPacket();
    
    if (rxPacket->packetData.ACKRPD){
        nrf24l01ChangeTXPower(-1);
    }
}

void loop(){
    
	// Write payload data
    CLRWDT();
    
    nrf24l01Packet_t packet;
    
    setMessage(&packet, "DBG", counter);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 0;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep();
    
    setMessage(&packet, "VBAT", getADCValue(0b000100, 2526));
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep();
    
    
    setMessage(&packet, "ANC3", getADCValue(0b010011, 2500));
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep();
    
    setMessage(&packet, "FVR", getADCValue(0b111111, 2500));
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep();
    
    setMessage(&packet, "TEMP", getADCValue(0b111101, 162) - 40000);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep();
    
    n_RF_SETUP_t rfSetup;
    rfSetup.byte = nrf24l01Send(n_R_REGISTER | n_RF_SETUP, 0);
    
    setMessage(&packet, "RFPWR", rfSetup.RF_PWR);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep();
    
	
//	checkRxData();
}

 unsigned char nrf24l01GetPipe(char * name){
     unsigned long pipe = 0;
     unsigned char i = 0;
    
     // Calculate a pipe from the name passed
     for (i = 0; i < strlen(name); i++){
         pipe+= name[i];
     }
     
     pipe%= 6;
     return pipe;
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
    
//    flashRealod();
	
	// This is broken! Use EEPRON since now we have it
//	if (romData.check != ENV_FLASH_VERSION){
//		romData.check = ENV_FLASH_VERSION;
//		strcpy(romData.name, ENV_DEVICE_NAME);
//		romData.bootMode = 0x00;
//		flashUpdate();
//	}
    
    strcpy(romData.name, ENV_DEVICE_NAME);
    
    flashRealod();
    
    nrf24l01Init();
    
    unsigned char pipe = nrf24l01GetPipe(romData.name);
    nrf24l01SetTXPipe(4);
    nrf24l01SetRXPipe(4);
    

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
    FVRCONbits.TSRNG = 0; // 1.8V Low Range
    FVRCONbits.TSEN = 1;
    
    /* Configure FVR */
    FVRCONbits.FVREN = 0; // Disable Voltage Reference Module
    FVRCONbits.ADFVR = 1; // 1.024V
    FVRCONbits.FVREN = 1; // Enable Voltage Reference Module
    
    ADCON1bits.ADCS = 0b111;
    ADCON1bits.ADFM = 1;
    ADCON1bits.ADNREF = 0b0;
    ADCON1bits.ADPREF = 0b00;
    
    ADCON0bits.CHS = 3;
    ADCON0bits.ADON = 1;
    
    
    /* Setup Interrupt Pin */
//	RA2PPSbits.RA2PPS = 0b00010;// A2
    TRISAbits.TRISA2 = 1;
    PIE0bits.INTE = 1;
    INTCONbits.INTEDG = 0;
            
    
    /* Setup WDT*/
    WDTCONbits.WDTPS = 11; //10=1S, 11=2S, 12=4S
    
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
	sleep();
    
    while(1){
        loop();
    }
    
    return;
}
