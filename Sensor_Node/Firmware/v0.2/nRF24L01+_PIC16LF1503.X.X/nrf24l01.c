#include <xc.h>
#include "interface.h"
#include "nRF24L01+_types.h"
#include "nrf24l01.h"
#include "flash.h"


#pragma interrupt_level 1
unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    return data;
}

void nrf24l01ISR(void){
    
    n_STATUS_t status;
    status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    if (status.TX_DS){
        nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
    }
}

void nrf24l01SetTransmitMode(void){
    
    nrf24l01CELow();
    
    delayUs(200);
    
    n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    if (config.PRIM_RX == 1){
        config.PRIM_RX = 0;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        delayUs(200);
    }
    
}

void nrf24l01SetRecieveMode(void){
    
    nrf24l01CELow();
    
    delayUs(200);
    
    n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    if (config.PRIM_RX == 0){
        config.PRIM_RX = 1;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        nrf24l01CEHigh();
        delayUs(200);
    }
}



void nrf24l01SendStart(void){
    
    nrf24l01SetTransmitMode();
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(n_W_TX_PAYLOAD);
    
    nrf24l01SendFlash(FLASH_OFFSET_NAME);
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
            
    nrf24l01CEHigh();
    
//    delayUs(100);
    delayMs(100);
    // Wait for the IC to trigger INT and wake up
//    SLEEP();
//    NOP();
//    NOP();
    
    nrf24l01CELow();
    
//    if (!STATUSbits.nTO && !STATUSbits.nPD){
//        RESET();
//    }
    
    
}


void nrf24l01InitRegisters(void){
    
    nrf24l01Send(n_W_REGISTER | n_CONFIG, 0x00);
    
    delayMs(10);
    
    n_SETUP_AW_t setupAW;
    setupAW.byte = 0x00;
    setupAW.AW = 3;
    nrf24l01Send(n_W_REGISTER | n_SETUP_AW, setupAW.byte);
    
    
//    n_SETUP_RETR_t setupRetries;
//    setupRetries.ARD = 15; //4000us
//    setupRetries.ARC = 15; //15  retries
//    nrf24l01Send(n_W_REGISTER | n_SETUP_RETR, setupRetries.byte);
    
    // Set Frequency
//     n_RF_CH_t channel;
//     channel.RF_CH = RADIO_FREQUENCY;
//     nrf24l01Send(n_W_REGISTER | n_RF_CH, channel.byte);
    
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
	n_EN_AA_t enAA;
	enAA.byte = nrf24l01Send(n_R_REGISTER | n_EN_AA, 0);
	enAA.ENAA_P0 = 0;
	enAA.ENAA_P1 = 0;
	enAA.ENAA_P2 = 0;
	enAA.ENAA_P3 = 0;
	enAA.ENAA_P4 = 0;
	enAA.ENAA_P5 = 0;
	nrf24l01Send(n_W_REGISTER | n_EN_AA, enAA.byte);
    
    
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
    n_STATUS_t status;
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
    
    
    nrf24l01InterfaceInit();
    
    /* SPI INIT */
    
    nrf24l01CELow();
    
    delayMs(11);
    
    nrf24l01InitRegisters();
    
    delayMs(2);
}

