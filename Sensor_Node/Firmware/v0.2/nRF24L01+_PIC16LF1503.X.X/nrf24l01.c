#include <xc.h>
#include <string.h>

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
    unsigned char offset = 0;
	
	nrf24l01.RXPending = 1;
	
	for (i = 0; i < sizeof(nrf24l01RXTopic); i++){
		nrf24l01RXTopic[i] = '\0';
	}
	for (i = 0; i < sizeof(nrf24l01RXValue); i++){
		nrf24l01RXValue[i] = '\0';
	}
	
    unsigned char width = nrf24l01Send(n_R_RX_PL_WID, 0);
    
    nrf24l01CELow();
    
<<<<<<< HEAD
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
=======
	nrf24l01SPIStart();

	nrf24l01SPISend(n_R_RX_PAYLOAD);
    
	for (i = 0; (i < sizeof(nrf24l01Name)) && (offset + i < width) ; i++){
		
		byte = nrf24l01SPISend(0);
		
		if (byte == '/'){
			offset++;
			break;
		}
		
		if (nrf24l01Name[i] != byte){
			nrf24l01.RXPending = 0;
		}
	}
	offset+= i;
	
	for (i = 0; (i < sizeof(nrf24l01RXTopic)) && (offset + i < width) ; i++){
		
		byte = nrf24l01SPISend(0);
		if (byte == '/'){
			offset++;
			break;
		}
		
		nrf24l01RXTopic[i] = byte;
	}
	offset+= i;
	
	
    for (i = 0; (i < sizeof(nrf24l01RXValue)) && (offset + i < width) ; i++){
		nrf24l01RXValue[i] = nrf24l01SPISend(0);
	}
>>>>>>> 98cceb51537cc0678eebd99d31e008967f4ce7a5
    
    nrf24l01SPIEnd();
    
	if (nrf24l01.waitForTXACK){
		if (strcmp(nrf24l01RXTopic, nrf24l01TXTopic) == 0){
			if (strcmp(nrf24l01RXValue, "ACK") == 0){
				nrf24l01.waitForTXACK = 0;
				nrf24l01.RXPending = 0;
				nrf24l01SetRXMode(0);
			}
		}
	}
}

void nrf24l01ISR(void){
   
    n_STATUS_t status;
    status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
	
    
    // I have had the IC lock up and return 0x00, reset it
    if (status.byte == 0x00){
//        write_flashmem(FLASH_OFFSET_BOOT_REASON, 2003);
        RESET();
    }
    
    // Also reset if we get 0xFF since that likely means there is an SPI error
    if (status.byte == 0xFF){
//        write_flashmem(FLASH_OFFSET_BOOT_REASON, 2004);
        RESET();
    }
	
	if (status.TX_DS){
        
        // Flag PTX as not busy anymore
        nrf24l01.TXBusy = 0;
        
        // If the nrf24l01 is in PTX mode and we are waiting for an ACK
        if (!nrf24l01.RXMode){
            if (nrf24l01.waitForTXACK){
                // Reset the ACK wait counter and set RX mode
                nrf24l01SetRXMode(1);
            }
        }
    }
    
    // Check id there is a received packet waiting
    if (status.RX_DR){
        // Get the RX data into the buffer
        nrf24l01HandleRX();
    }
	
	// Clear the interrupt on the nrf24l01
	nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
}


void nrf24l01SendString(char waitForAck){
	
	// Initalise an iterator for the many loops
    unsigned char i;
	
	// If the function was called to wait for an ACK, then set the 
	// status variable state accordingly
	nrf24l01.waitForTXACK = waitForAck;
	
	// Define where to re-start the send if the previous one failed
	RESEND:
	
	// Wait for the TXBusy to clear so we know the packet has been sent
	i = 0xFF;
    while (nrf24l01.TXBusy){
        if (!--i) {
            goto RESEND;
        }
        delayUs(100);
    }

	
	// Set the transmit busy flag so that the interrupt can clear it later.
	nrf24l01.TXBusy = 1;
    
	// Disable interrupts while sending.
    enableInterrupts(0);
    
	// Set the radio into transmitter mode
    nrf24l01SetRXMode(0);
    
	// Setup the SPI bus to send data to the radio
    nrf24l01SPIStart();
    
	// Send the command to tell the radio we want to send data with no auto ACK.
    nrf24l01SPISend(W_TX_PAYLOAD_NOACK);
    
	// Loop through each character of the name buffer and send it to the radio
    for (i = 0; (nrf24l01Name[i] != '\0') && (i < sizeof(nrf24l01Name)); i++){
        nrf24l01SPISend(nrf24l01Name[i]);
    }
    
	// Send the MQTT topic delimiter.
    nrf24l01SPISend('/');
    
	// Loop through each character of the topic buffer and send it to the radio
    for (i = 0; (nrf24l01TXTopic[i] != '\0') && (i < sizeof(nrf24l01TXTopic)); i++){
        nrf24l01SPISend(nrf24l01TXTopic[i]);
    }
    
	// Send the MQTT topic delimiter.
    nrf24l01SPISend('/');
    
	// Loop through each character of the value buffer and send it to the radio
    for (i = 0; (nrf24l01TXValue[i] != '\0') && (i < sizeof(nrf24l01TXValue)); i++){
        nrf24l01SPISend(nrf24l01TXValue[i]);
    }
    
	// Release the SPI bus from the radio
    nrf24l01SPIEnd();
            
	// Pull the CE pin high on the radio for at least 10us
    nrf24l01CEHigh();
    delayUs(20);
    nrf24l01CELow();
    
	// Re-enable interrupts
    enableInterrupts(1);
		
	// Wait for the transmit ACK flag to becode clear so we know we got an ACK
	i = 0xFF;
	while (nrf24l01.waitForTXACK){
		if (!--i) {
			goto RESEND;
		}
		delayUs(100);
	}
}


void nrf24l01InitRegisters(void){
    
    n_CONFIG_t config;
    
	config.PWR_UP = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    delayUs(10000);
    
    n_SETUP_AW_t setupAW;
    setupAW.byte = 0x00;
    setupAW.AW = 3;
    nrf24l01Send(n_W_REGISTER | n_SETUP_AW, setupAW.byte);
    
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
}

