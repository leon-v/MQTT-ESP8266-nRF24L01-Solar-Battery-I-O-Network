#include <xc.h>
#include <pic16lf1503.h>
#include "nRF24L01+_types.h"
#include "nrf24l01.h"
#include "config.h"
#include "flash.h"


#define CEPIN PORTAbits.RA0
#define CELOW() CEPIN = 0
#define CEHIGH() CEPIN = 1

#define CSPIN PORTAbits.RA1
#define CSLOW() CSPIN = 0
#define CSHIGH() CSPIN = 1

n_STATUS_t status;

#pragma interrupt_level 1
void nrf24l01SPIStart(void){
    CSLOW();
    __delay_us(10);
}

#pragma interrupt_level 1
unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    while (!SSP1STATbits.BF){ NOP(); }
    return SSP1BUF;
}

#pragma interrupt_level 1
void nrf24l01SPIEnd(void){
    __delay_us(10);
    CSHIGH();
}

#pragma interrupt_level 1
unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    nrf24l01SPIStart();
    
    status.byte = nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    return data;
}

void nrf24l01ISR(void){
    
    status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    if (status.TX_DS){
        status.TX_DS = 1;
        nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
    }
    
}

void nrf24l01SetTransmitMode(void){
    
    CELOW();
    
    n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    if (config.PRIM_RX == 1){
        config.PRIM_RX = 0;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        __delay_us(130);
    }
    
}

void nrf24l01SetRecieveMode(void){
    
    CELOW();
    
    n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    if (config.PRIM_RX == 0){
        config.PRIM_RX = 1;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        CEHIGH();
        __delay_us(130);
    }
}



void nrf24l01SendStart(void){
    
    nrf24l01SetTransmitMode();
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(n_W_TX_PAYLOAD);
}

void nrf24l01SendString(char * string){
    unsigned char i;
    for (i = 0; string[i] != '\0'; i++){
        nrf24l01SPISend(string[i]);
    }
}

void nrf24l01SendFlash(unsigned char offset){
    
    unsigned char btye = 1;
    unsigned char i = 0;
    
    while (1){
        btye = read_flashmem((unsigned) (offset + i));
        
        if (btye == '\0'){
            break;
        }
        
        nrf24l01SPISend(btye);
        i++;
    }
}

void nrf24l01SendEnd(void){
    
    nrf24l01SPIEnd();
            
    CEHIGH();
    __delay_us(50);
    CELOW();
    
    // Wait for the IC to trigger INT and wake up
    SLEEP();
    NOP();
    NOP();
}


void nrf24l01InitRegisters(void){
    
    nrf24l01Send(n_W_REGISTER | n_CONFIG, 0x00);
    
    __delay_ms(10);
    
    n_SETUP_AW_t setupAW;
    setupAW.byte = 0x00;
    setupAW.AW = 3;
    nrf24l01Send(n_W_REGISTER | n_SETUP_AW, setupAW.byte);
    
    
    n_SETUP_RETR_t setupRetries;
    setupRetries.ARD = 15; //4000us
    setupRetries.ARC = 15; //15  retries
    nrf24l01Send(n_W_REGISTER | n_SETUP_RETR, setupRetries.byte);
    
    // Set Frequency
    // n_RF_CH_t channel;
    // channel.RF_CH = RADIO_FREQUENCY;
    // nrf24l01Send(n_W_REGISTER | n_RF_CH, channel.byte);
    
    // Set radio to 2 Mbps and high power.  Leave LNA_HCURR at its default.
    n_RF_SETUP_t rfSetup;
    rfSetup.RF_DR_LOW = 0;
    rfSetup.RF_DR_HIGH = 1;
    rfSetup.RF_PWR = 3;
    nrf24l01Send(n_W_REGISTER | n_RF_SETUP, rfSetup.byte);
    
    // Enable 2-byte CRC and power up in receive mode.
    n_CONFIG_t config;
	config.PRIM_RX = 1;
	config.EN_CRC = 1;
    config.CRCO = 1;
	config.PWR_UP = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    // Enable all data pipes
	n_EN_RXADDR_t enRXAddr;
	enRXAddr.ERX_P0 = 1;
	enRXAddr.ERX_P1 = 1;
	enRXAddr.ERX_P2 = 1;
	enRXAddr.ERX_P3 = 1;
	enRXAddr.ERX_P4 = 1;
	enRXAddr.ERX_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_EN_RXADDR, enRXAddr.byte);

	// Disable Auto ACK MCU needs to do this
//	n_EN_AA_t enAA;
//	enAA.byte = nrf24l01Send(n_R_REGISTER | n_EN_AA, 0);
//	enAA.ENAA_P0 = 0;
//	enAA.ENAA_P1 = 0;
//	enAA.ENAA_P2 = 0;
//	enAA.ENAA_P3 = 0;
//	enAA.ENAA_P4 = 0;
//	enAA.ENAA_P5 = 0;
//	nrf24l01Send(n_W_REGISTER | n_EN_AA, enAA.byte);
    
    
    // Set dynamic payload length
	n_FEATURE_t feature;
	feature.byte = nrf24l01Send(n_R_REGISTER | n_FEATURE, 0);
	feature.EN_DPL = 1;
	nrf24l01Send(n_W_REGISTER | n_FEATURE, feature.byte);
    
    n_DYNPD_t DynPD;
	DynPD.byte = nrf24l01Send(n_R_REGISTER | n_DYNPD, 0);
	DynPD.DPL_P0 = 1;
	DynPD.DPL_P1 = 1;
	DynPD.DPL_P2 = 1;
	DynPD.DPL_P3 = 1;
	DynPD.DPL_P4 = 1;
	DynPD.DPL_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_DYNPD, DynPD.byte); 
    
    // clear the interrupt flags in case the radio's still asserting an old unhandled interrupt
    status.byte = 0x00;
    status.RX_DR = 1;
    status.TX_DS = 1;
    status.MAX_RT = 1;
    nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
    
    // flush the FIFOs in case there are old data in them.
    nrf24l01Send(n_FLUSH_TX, 0);
    nrf24l01Send(n_FLUSH_RX, 0);
}

void nrf24l01Init(void){
    
    TRISAbits.TRISA0 = 0; // CE out
    
    /* SPI INIT */
    // I Always forget to reset that damn ADC
    ANSELA = 0x00;
    ANSELC = 0x00;
    
    TRISAbits.TRISA1 = 0; // CS out
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    TRISCbits.TRISC0 = 0; // CLK
    
    SSPCON1bits.SSPEN = 0; 
    SSPCON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
    SSPCON1bits.SSPM = 0b0000;
    
    SSPCON1bits.SSPEN = 1;
    
    CELOW();
    
    __delay_ms(11);
    
    nrf24l01InitRegisters();
    
    __delay_ms(2);
}

