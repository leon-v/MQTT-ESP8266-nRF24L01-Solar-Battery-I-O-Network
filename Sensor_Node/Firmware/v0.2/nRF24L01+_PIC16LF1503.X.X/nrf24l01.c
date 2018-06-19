#include <xc.h>
#include "interface.h"
#include "nRF24L01+_types.h"
#include "nrf24l01.h"
#include "flash.h"

#pragma interrupt_level 1
unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    enableInterrupts(0);
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    enableInterrupts(1);
    
    return data;
}

#pragma interrupt_level 1
void nrf24l01SetRXMode(unsigned char rxMode){
     n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    
    nrf24l01.RXMode = rxMode;
            
    if (config.PRIM_RX != nrf24l01.RXMode){
        
        nrf24l01CELow();
        delayUs(200);

        config.PRIM_RX = nrf24l01.RXMode;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        delayUs(200);

        if (nrf24l01.RXMode){
        	nrf24l01CEHigh();
            delayUs(200);
        }
    }
}


void nrf24l01HandleRX(void){
    
    // Check the packet matches this name
    unsigned char byte;
    unsigned char i;
    
    unsigned char width = nrf24l01Send(n_R_RX_PL_WID, 0);
    
    nrf24l01CELow();
    
    nrf24l01SPIStart();

	nrf24l01SPISend(n_R_RX_PAYLOAD);
    
    i = 0;
    while (i < width){
        byte = nrf24l01SPISend(0);
        
//        if (byte == '/'){
//            break;
//        }
//        
//        if (byte != read_flashmem( (unsigned) FLASH_OFFSET_NAME + i)){
//            nrf24l01.RXPending = 0;
//            return;
//        }
        
        i++;
    }
    
    nrf24l01SPIEnd();
    
//    while (i < width){
//        byte = nrf24l01SPISend(0);
//        //nrf24l01.rxBuffer[strlen((char *)nrf24l01.rxBuffer)] = byte;
//        i++;
//    }
    
    nrf24l01.RXPending = 1;
}

void nrf24l01CheckACK(void){
    
//    if (!nrf24l01.waitForTXACK){
//        return;
//    }
//    if (strcmp(string, "ACK") == 0){
//        nrf24l01.RXPending = 0;
//    }
    
    nrf24l01.waitForTXACK = 0;
    nrf24l01.RXPending = 0;
    nrf24l01SetRXMode(0);
}

void nrf24l01ISR(void){
   
    n_STATUS_t tempStatus;
    nrf24l01.status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    // I have had the IC lock up and return 0x00, reset it
    if (nrf24l01.status.byte == 0x00){
        write_flashmem(FLASH_OFFSET_BOOT_REASON, 2003);
        RESET();
    }
    
    // Also reset if we get 0xFF since that likely means there is an SPI error
    if (nrf24l01.status.byte == 0xFF){
        write_flashmem(FLASH_OFFSET_BOOT_REASON, 2004);
        RESET();
    }
    
    // Check id there is a received packet waiting
    if (nrf24l01.status.RX_DR){

        nrf24l01.waitForTXACK = 0;
        
        // Clear the interrupt on the nrf24l01
        tempStatus.byte = 0x00;
        tempStatus.RX_DR = 1;
        nrf24l01Send(n_W_REGISTER | n_STATUS, tempStatus.byte);
        
        counter++;
        
        // Get the RX data into the buffer
        nrf24l01HandleRX();
        
        // Check if the RX data is an ACK
//        nrf24l01CheckACK();
    }
    

    
    if (nrf24l01.status.TX_DS){
        
        // Clear the interrupt on the nrf24l01 and update our status to reflect this
        tempStatus.byte = 0x00;
        tempStatus.TX_DS = 1;
        nrf24l01Send(n_W_REGISTER | n_STATUS, tempStatus.byte);
        
        // Flag PTX as not busy anymore
        nrf24l01.TXBusy = 0;
        
        // If the nrf24l01 is in PTX mode and we are waiting for an ACK
        if (nrf24l01.RXMode == 0){
//            if (nrf24l01.waitForTXACK){
                // Reset the ACK wait counter and set RX mode
                nrf24l01SetRXMode(1);
//            }
        }
    }
}


void nrf24l01SendString(char waitForAck){
    
    if (!waitForAck){
        delayUs(50000);
        delayUs(50000);
        delayUs(50000);
        delayUs(50000);
    }
    
    nrf24l01.TXBusyCount = 0;
    while (nrf24l01.TXBusy){
        if (++nrf24l01.TXBusyCount == 15) {
            write_flashmem(FLASH_OFFSET_BOOT_REASON, 2001);
            RESET();
        }
        delayUs(50000);
    }
    
    nrf24l01.waitForTXACKCount = 0;
    while (nrf24l01.waitForTXACK){
        if (++nrf24l01.waitForTXACKCount == 15) {
            write_flashmem(FLASH_OFFSET_BOOT_REASON, 2002);
            RESET();
        }
        delayUs(1000);
    }
    
    enableInterrupts(0);
    
    unsigned char btye;
    unsigned char i;
    
    nrf24l01SetRXMode(0);
    
    nrf24l01.TXBusy = 1;
    nrf24l01.waitForTXACK = waitForAck;
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(W_TX_PAYLOAD_NOACK);
    
    i = 0;
    while (1){
        btye = read_flashmem((unsigned) FLASH_OFFSET_NAME + i++);
        
        if (btye == '\0'){
            break;
        }
        
        nrf24l01SPISend(btye);
    }
    
    nrf24l01SPISend('/');
    
    for (i = 0; nrf24l01.txTopic[i] != '\0'; i++){
        nrf24l01SPISend(nrf24l01.txTopic[i]);
    }
    
    nrf24l01SPISend('/');
    
    for (i = 0; nrf24l01.txValue[i] != '\0'; i++){
        nrf24l01SPISend(nrf24l01.txValue[i]);
    }
    
    
    nrf24l01SPIEnd();
            
    nrf24l01CEHigh();
    
    delayUs(20);
    
    nrf24l01CELow();
    
    enableInterrupts(1);
}


void nrf24l01InitRegisters(void){
    
// Enable 2-byte CRC and power up in receive mode.
    n_CONFIG_t config;
    
	config.PWR_UP = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    delayUs(10000);
    
//    n_SETUP_AW_t setupAW;
//    setupAW.byte = 0x00;
//    setupAW.AW = 3;
//    nrf24l01Send(n_W_REGISTER | n_SETUP_AW, setupAW.byte);
    
    
//    n_SETUP_RETR_t setupRetries;
//    setupRetries.ARD = 15; //4000us
//    setupRetries.ARC = 15; //15  retries
//    nrf24l01Send(n_W_REGISTER | n_SETUP_RETR, setupRetries.byte);
    
    // Set Frequency
//     n_RF_CH_t channel;
//     channel.RF_CH = RADIO_FREQUENCY;
//     nrf24l01Send(n_W_REGISTER | n_RF_CH, channel.byte);
    
    // Set radio to 2 Mbps and high power.  Leave LNA_HCURR at its default.
    // n_RF_SETUP_t rfSetup;
    // rfSetup.RF_DR_LOW = 0;
    // rfSetup.RF_DR_HIGH = 1;
    // rfSetup.RF_PWR = 3;
    // nrf24l01Send(n_W_REGISTER | n_RF_SETUP, rfSetup.byte);
    
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
    feature.EN_DYN_ACK = 1;
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
    
    // Enable 2-byte CRC and power up in receive mode.
	config.PRIM_RX = 1;
	config.EN_CRC = 1;
    config.CRCO = 1;
	config.PWR_UP = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
}

void nrf24l01Init(void){
    
    
    nrf24l01InterfaceInit();
    
    /* SPI INIT */
    
    nrf24l01CELow();
    
    delayMs(11);
    
    nrf24l01InitRegisters();
    
    delayMs(2);
    
    nrf24l01.status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
}

