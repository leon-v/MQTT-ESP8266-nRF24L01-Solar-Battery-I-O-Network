#include "nrf24l01.h"

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

nrf24l01Packet_t * TXPacket;
nrf24l01Packet_t RXPacket;

unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    // Disable interrupts to ensure we are not interrupted
    enableInterrupts(0);
    
    // Start the SPI transaction and select the chip
    nrf24l01SPIStart();
    
    // Send the command
    nrf24l01SPISend(command);
    
    // Receive the data
    data        = nrf24l01SPISend(data);
    
    // End the SPI Transaction and release the IC
    nrf24l01SPIEnd();
    
    // Re-enable interrupts
    enableInterrupts(1);
    
    return data;
}


void nrf24l01ChangeTXPower(int addPower){
    
    n_RF_SETUP_t rfSetup;
    rfSetup.byte = nrf24l01Send(n_R_REGISTER | n_RF_SETUP, 0);
    
    if (addPower > 0){
        if (rfSetup.RF_PWR < 3){
            rfSetup.RF_PWR++;
        }
    }
    
    if (addPower < 0){
        if (rfSetup.RF_PWR > 0){
            rfSetup.RF_PWR--;
        }
    }
    
    nrf24l01Send(n_W_REGISTER | n_RF_SETUP, rfSetup.byte);
    
}

void nrf24l01SetRXMode(unsigned char rxMode){
    
    n_CONFIG_t config;
    
    // Get the current IC configuration
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    
    // If the IC is not in the same mode as requested, change it.
    if (config.PRIM_RX != rxMode){
        
        // Disable the IC and wait for the IC to disable
        nrf24l01CELow();
        delayUs(200);
        
        // Change the mode of the IC to the mode requested
        config.PRIM_RX = rxMode;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        
        // Wait for the IC to update
        delayUs(200);

        // If we changed to receiver mode, re-enable the IC to start listening
        if (rxMode){
        	nrf24l01CEHigh();
            delayUs(200);
        }
    }
    
    // Update the global with the current state
    nrf24l01.RXMode = rxMode;
}

void nrf24l01SendACK(nrf24l01Packet_t * packet){

	packet->packetData.ACKRequest = 0;
	packet->packetData.IsACK = 1;
	packet->packetData.ACKRPD = packet->packetData.RPD;
	

	nrf24l01SendPacket(packet);
}

void nrf24l01CheckACK(void){
    /* Check if the RX packet is an ACK */
    
    // If the current RX packet is not an ACK, skip
    if (!RXPacket.packetData.IsACK){
        return;
    }
    
    // Clear RX Pending flag so we don't try process this packet as a real one
	nrf24l01.RXPending = 0;
    
    // If the current TX packet doesn't require an ACK, skip
    if (!TXPacket->packetData.ACKRequest){
        return;
    }
    
    // If the TX and RX do not match, skip.
    if (strcmp(TXPacket->Message, RXPacket.Message) != 0){
        return;
    }
    
    // We have a valid ACK packet
    
    
    
    // Clear the ACKRequest to signal that we no longer need to wait
	TXPacket->packetData.ACKRequest = 0;

    // Switch the radio back to TX mode so we don't sit there receiving.
	nrf24l01SetRXMode(0);
}


nrf24l01Packet_t *nrf24l01GetRXPacket(void){
	return &RXPacket;
}

void nrf24l01ReceivePacket(void){
	
    // Clear all the current RX buffers
    memset(RXPacket.Message, 0 ,sizeof(RXPacket.Message));
    RXPacket.packetData.byte = 0x00;
    
	// Get the with of the data waiting in the RX buffer
    unsigned char width = nrf24l01Send(n_R_RX_PL_WID, 0);
    unsigned char i = 0;
    
    // Disable the radio IC
    nrf24l01CELow();
    
    // Start the SPI transaction and select the radio IC
	nrf24l01SPIStart();

    // Send the command to tell the radio IC that we want the received data buffer
	nrf24l01SPISend(n_R_RX_PAYLOAD);
    
    // Get the packet data byte as the first byte
    RXPacket.packetData.byte = nrf24l01SPISend(0);
    width--;
    
    for (i = 0; (i < width) && (i < sizeof(RXPacket.Message)); i++){
        // Get the byte from the radio IC
		RXPacket.Message[i] = nrf24l01SPISend(0);
	}
    
    // End the SPI transaction and release the radio IC
    nrf24l01SPIEnd();

    RXPacket.packetData.RPD = nrf24l01Send(n_R_REGISTER | n_RPD, 0);

    // Re-enable the radio IO to continue receiving
    nrf24l01CEHigh();
}

void nrf24l01SendPacket(nrf24l01Packet_t * Packet){
    
    TXPacket = Packet;
	
	// Initalise an iterator for the many loops
    unsigned char i;
    
	
// Define where to re-start the send if the previous one failed
RESEND:
	
//	 Wait for the TXBusy to clear so we know the packet has been sent
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
    
    nrf24l01SPISend(TXPacket->packetData.byte);
    
	// Loop through each character of the name buffer and send it to the radio
    for (i = 0; (i  < strlen(TXPacket->Message)) && (i < sizeof(TXPacket->Message)); i++){
        nrf24l01SPISend(TXPacket->Message[i]);
    }
    
	// Release the SPI bus from the radio
    nrf24l01SPIEnd();
            
	// Pull the CE pin high on the radio for at least 10us
    nrf24l01CEHigh();
    delayUs(20);
    nrf24l01CELow();
    
	// Re-enable interrupts
    enableInterrupts(1);

    // Wait for the TXBusy to clear so we know the packet has been sent
	i = 0xFF;
    while (nrf24l01.TXBusy){
        if (!--i) {
            goto RESEND;
        }
        if (i  > 128){
            nrf24l01ChangeTXPower(1);
        }
        delayUs(100);
    }
    
		
	// Wait for the transmit ACK flag to become clear so we know we got an ACK
	i = 0xFF;
	while (TXPacket->packetData.ACKRequest){
		if (!--i) {
			goto RESEND;
		}
		delayUs(40);
	}
}

void nrf24l01ISR(void){
   
    n_STATUS_t status;
    status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    // I have had the IC lock up and return 0x00, reset it
    if (status.byte == 0x00){
//    	exception(1);
    }
    
    // Also reset if we get 0xFF since that likely means there is an SPI error
    if (status.byte == 0xFF){
		exception(2);
    }
	
	if (status.TX_DS){
        
        // Flag PTX as not busy anymore
        nrf24l01.TXBusy = 0;
        
        // If the nrf24l01 is in PTX mode and we are waiting for an ACK
        if (!nrf24l01.RXMode){
            if (TXPacket->packetData.ACKRequest){

                // Put the radio into receiver mode so we can get an ACK
                nrf24l01SetRXMode(1);
            }
        }
    }

    // Check id there is a received packet waiting
    if (status.RX_DR){
        
        // If the previous RX packet has been delt with
        if (!nrf24l01.RXPending){

        	// Flag the radio state as having a RX packet ready
        	nrf24l01.RXPending = 1;
	        nrf24l01ReceivePacket();
	        nrf24l01CheckACK();
        }

        // If the MCU has not processed the last packet
        else{

        	// We don't want to clear the interrupt so we can pick it up next time
        	status.RX_DR = 0;
        }
        
    }
	
	// Clear the interrupt on the nrf24l01
	nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
}


void nrf24l01InitRegisters(unsigned char isReciever){

    n_CONFIG_t config;
    
	config.PWR_UP = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    n_SETUP_AW_t setupAW;
    setupAW.byte = 0x00;
    setupAW.AW = 0b11;
    nrf24l01Send(n_W_REGISTER | n_SETUP_AW, setupAW.byte);
    
    // Set Frequency
     n_RF_CH_t channel;
     channel.RF_CH = 2;
     nrf24l01Send(n_W_REGISTER | n_RF_CH, channel.byte);
    
    // Set radio to 2 Mbps and high power.  Leave LNA_HCURR at its default.
     n_RF_SETUP_t rfSetup;
     rfSetup.byte = 0x00;
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

void nrf24l01Init(unsigned char isReciever){
    
    
    nrf24l01InterfaceInit();
    
    
    /* SPI INIT */
    
    nrf24l01CELow();
    
    delayUs(50000);
    
    nrf24l01InitRegisters(isReciever);    
    
    delayUs(50000);

    nrf24l01CEHigh();
    
    
}

