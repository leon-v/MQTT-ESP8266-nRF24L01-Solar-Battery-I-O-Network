#include <xc.h>
#include <string.h>
#include <stdlib.h>

#include "nrf24l01.h"
#include "interface.h"
#include "../../../../shared.h"

unsigned char sleepLoop = 0;
float counter = 0;

// Cahnge ISR to trigger super loop code to do its bidding

void interrupt ISR(void){    
    
    if (PIR0bits.INTF){
        nrf24l01ISR();
        PIR0bits.INTF = 0;
    }
}

void doWDTSleep(unsigned char wdtps){
    
    // Set watchdog
    WDTCONbits.WDTPS = wdtps;
        
    // Start the sleep
    SLEEP();
    NOP();
    NOP();
    
    WDTCONbits.WDTPS = 0b01101; // 8s
    CLRWDT();
}

void handleRXData(void){
    
    nrf24l01Packet_t * RXPacket = nrf24l01GetRXPacket();
    
//    char string[16];
//    char* strings = strtok(RXPacket->Message, "/");
    
//    strcpy(string, strings);
    
//    if (strcmp(string, romData->name) != 0){
        
//        nrf24l01.RXPending = 0;
//        return;
//    }
    
    // If we are the primary hub / reciever, we need to send back ACKs
    if (RXPacket->packetData.ACKRequest){
        nrf24l01SendACK(RXPacket);
    }    
    
//    strings = strtok(NULL, "/");
//    strcpy(string, strings);
//    
//    // Check topic
//    
//    strings = strtok(NULL, "/");
//    strcpy(string, strings);
//    
//    // Check value
//    
//    counter = atof(string);
    
    nrf24l01.RXPending = 0;
}


void sleep(unsigned int milliseconds){
    
    // If no time passed, sleep until interrupt triggered or 1ms
    if (!milliseconds){
        doWDTSleep(0b00000);
        return;
    }
    
    // If there was a valid time passed
        
    // Divide the value by the amount of loops we need to do
    milliseconds = (unsigned int) (milliseconds / (256));

    // Bump it up 1 to make sure we have at least 1
    milliseconds++;
            
    // Loop 
    while (--milliseconds){
        
        // Set the radio to RX mode to check for incoming packets
        nrf24l01SetRXMode(1);

        // Listen for 256mS
        doWDTSleep(0b01000);
        
        // Set the radio to TX mode to go into low power mode
//        nrf24l01SetRXMode(0);

        // Process the packet if there was one
        if (nrf24l01.RXPending){
            handleRXData();
        }
        
        // Do nothing for 256mS
//        doWDTSleep(0b01000);
    }
}

float getADCValue(unsigned char channel){
    
    #define ADC_COUNT 1000
	float adcSum = 0;
	unsigned int adcLoop = ADC_COUNT;
	
	ADCON0bits.CHS = channel;
    FVRCONbits.FVREN = 1; // Enable Voltage Reference Module
    ADCON0bits.ADON = 1;
    
	doWDTSleep(0b00000); //1ms
    
	while (adcLoop--){
		
		ADCON0bits.ADGO = 1;
       
		while (ADCON0bits.ADGO){
            doWDTSleep(0b00000); //1ms
		}
		
		adcSum+= (ADRESL | (ADRESH << 8));
        
	}
    
    FVRCONbits.FVREN = 0; // Disable Voltage Reference Module
    ADCON0bits.ADON = 0;
    
    
	adcSum/= ADC_COUNT; // Adjust to get average
    adcSum/= 500; // adjust for FVR +REF @ 2.048 to get volts
	
	return adcSum;
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
    
#define SLEEP_TIME 2000
    nrf24l01Packet_t packet;
    
    setMessage(&packet, "DBG", counter);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 0;
	nrf24l01SendPacket(&packet);
    checkTXPower();
	sleep(SLEEP_TIME);
    
    
    
    FVRCONbits.TSEN = 1;
    float vt = (2.048 - getADCValue(0b111101)) / (FVRCONbits.TSRNG ? 2 : 4);
    FVRCONbits.TSEN = 0;
    
	#define tempOffset 40
    #define vf 0.6063
    #define tc -0.0014 // 19.601568 betwen max nad min
//    #define tc -0.00132 // 23.226564 From AN1333 PDF
//    #define tc -0.00162 // 11.156252 Min
//    #define tc -0.00118 // 30.835936 MAx
    float ta = (vt / tc) - (vf / tc) - tempOffset;
    
	setMessage(&packet, "TEMP", ta);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
    sleep(SLEEP_TIME);
    
    
    
    //Resistor divider on Vbatt
    // 10K / 4.7K  = 2.127659574468085
    // * 1.46 for unknown reasons. Maybe ADC pin sinkign current
    setMessage(&packet, "VBAT", getADCValue(0b000100) * 3.106382978723404);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 0;
	nrf24l01SendPacket(&packet);
    checkTXPower();
    sleep(SLEEP_TIME);
    
    
    setMessage(&packet, "ANC3mV", getADCValue(0b010011));
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
    sleep(SLEEP_TIME);
    
    
    n_RF_SETUP_t rfSetup;
    rfSetup.byte = nrf24l01Send(n_R_REGISTER | n_RF_SETUP, 0);
    
    setMessage(&packet, "RFPWR", rfSetup.RF_PWR);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 1;
	nrf24l01SendPacket(&packet);
    checkTXPower();
    sleep(SLEEP_TIME);
    
	
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
    
    unsigned char bootStatus = STATUS;
    
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
    
//    memcpy(romDataMap.bytes, resetRomData.bytes, sizeof(romDataMap_t.bytes));
    
	strcpy(romData->name, ENV_DEVICE_NAME);
	
    nrf24l01Init();
    
    unsigned char pipe = nrf24l01GetPipe(romData->name);
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
        
    setMessage(&packet, "BOOT", bootStatus);
    packet.packetData.byte = 0;
    packet.packetData.ACKRequest = 0;
	nrf24l01SendPacket(&packet);
    sleep(3000);
    
    while(1){
        loop();
    }
    
    return;
}
