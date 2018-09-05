#include "nrf24l01.h"

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

nrf24l01Packet_t TXPacket, RXPacket, userRXPacket;
nrf24l01Packet_t * lastTXPacket;


unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    // Start the SPI transaction and select the chip
    nrf24l01SPIStart();
    
    // Send the command
    nrf24l01SPISend(command);
    
    // Receive the data
    data        = nrf24l01SPISend(data);
    
    // End the SPI Transaction and release the IC
    nrf24l01SPIEnd();
    
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
    
    // If we want to change to RX mode
    if (rxMode){
        
        if (status.TX == TXSending){
            return;
        }
    }
    
    // If we want to change to TX mode
    if (!rxMode){
        if (status.TX == TXPendingACK){
            return;
        }
    }
//    
    // Get the current IC configuration
//    status.configRegister.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    
    // If the IC is not in the same mode as requested, change it.
    if (status.configRegister.PRIM_RX != rxMode){
        
        // Disable the IC and wait for the IC to disable
        nrf24l01CELow();
        delayUs(120);
        
        // Change the mode of the IC to the mode requested
        status.configRegister.PRIM_RX = rxMode;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, status.configRegister.byte);
        
        // Wait for the IC to update
        delayUs(120);

        // If we changed to receiver mode, re-enable the IC to start listening
        if (rxMode){
        	nrf24l01CEHigh();
            delayUs(120);
        }
    }
}


nrf24l01Packet_t *nrf24l01GetRXPacket(void){
	return &userRXPacket;
}
 
 void nrf24l01SetTXPipe(unsigned char pipe){
    
     // Set the pipe address into the 
     nrf24l01SPIStart();
     nrf24l01SPISend(n_W_REGISTER | n_TX_ADDR);
     nrf24l01SPISend(n_ADDRESS_P0[4] + (unsigned) (pipe * n_ADDRESS_MUL));
     nrf24l01SPISend(n_ADDRESS_P0[3]);
     nrf24l01SPISend(n_ADDRESS_P0[2]);
     nrf24l01SPISend(n_ADDRESS_P0[1]);
     nrf24l01SPISend(n_ADDRESS_P0[0]);
     nrf24l01SPIEnd();
 }

 void nrf24l01SetRXPipe(unsigned char pipe){
    
     n_EN_RXADDR_t enRXAddr;
    
     if (pipe > 5){
         enRXAddr.ERX_P0 = 1;
         enRXAddr.ERX_P1 = 1;
         enRXAddr.ERX_P2 = 1;
         enRXAddr.ERX_P3 = 1;
         enRXAddr.ERX_P4 = 1;
         enRXAddr.ERX_P5 = 1;
     }
     
     else{
         enRXAddr.ERX_P0 = 1;
         enRXAddr.byte = (unsigned) enRXAddr.byte << pipe;
     }
    
     nrf24l01Send(n_W_REGISTER | n_EN_RXADDR, enRXAddr.byte);
 }


void nrf24l01SendPacket(nrf24l01Packet_t * txPacket){
    
    // Wait for the module to become available to send
    unsigned int loopCount = 1000;
    while (status.TX != TXIdle){
        
        delayUs(1000);
        nrf24l01Service();
        
        if (!loopCount--){
//            exception(21);
            break;
        }
    }
	
    // Copy the packet from user space
    strcpy(TXPacket.Message, txPacket->Message);
    TXPacket.packetData.byte = txPacket->packetData.byte;
    
    // Set the transmit flag to send the new packet
    status.TX = TXReady;
    
    // Run the service task to send the packet
    nrf24l01Service();
}

void nrf24l01ISR(void){
    
    // Get the current status of the radio
    status.statusRegister.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    counter++;
	
    // Check id there is a received packet waiting
    if (status.statusRegister.RX_DR){
        
        // If we have processed the last packet, set this one to be accepted
        if (status.RX == RXIdle){
            status.RX = RXPending;
        }
        
        // If we are not ready for the packet,don't clear the interrupt
        else{
            status.statusRegister.RX_DR = 0;
        }
		
        // Run the service task to get the new packet
		nrf24l01Service();
    }
	
    
    // Check if the module has sent the current packet
	if (status.statusRegister.TX_DS){
		
        // If the last TX packet requested an ACK
        // Setup the radio and status to wait for one
		if (lastTXPacket->packetData.ACKRequest){
			status.TX = TXPendingACK;
			status.retryCount = 0xFF;
            nrf24l01SetRXMode(1);
		}
        
        // If the TX packet was an ACK, swap back in to RX mode since we would
        // only send one if we were in RX mode
        else if(lastTXPacket->packetData.IsACK){
            nrf24l01SetRXMode(1);
        }
        
        // If no special requirement was requested, the packet was sent
        else{
			status.TX = TXIdle;
		}
        
        nrf24l01Service();
    }


    
	// Clear the interrupt on the nrf24l01
	nrf24l01Send(n_W_REGISTER | n_STATUS, status.statusRegister.byte);
}

void nrf24l01SendTXBuffer(nrf24l01Packet_t * packet){
	
    // Store the packet in a local pointer so other methods can use it
	lastTXPacket = packet;
	
	unsigned char i;
	
	// Set the radio into transmitter mode
	nrf24l01SetRXMode(0);

	// Setup the SPI bus to send data to the radio
	nrf24l01SPIStart();

	// Send the command to tell the radio we want to send data with no auto ACK.
	nrf24l01SPISend(W_TX_PAYLOAD_NOACK);
    
    // First byte is the packet data byte so send that to the radio
	nrf24l01SPISend(lastTXPacket->packetData.byte);

	// Loop through each character of the name buffer and send it to the radio
	unsigned char width = strlen(lastTXPacket->Message);
	
	for (i = 0; i  < width; i++) {
		nrf24l01SPISend(lastTXPacket->Message[i]);
	}

	// Release the SPI bus from the radio
	nrf24l01SPIEnd();
	
	// Pull the CE pin high on the radio for at least 10us
	nrf24l01CEHigh();
	delayUs(12);
	nrf24l01CELow();
}



void nrf24l01Service(void){
    
    unsigned char i;
            
    if (status.TX == TXReady){
		
		// Setup the status as sending
        status.TX = TXSending;	
		nrf24l01SendTXBuffer(&TXPacket);
    }
	
    // If we were run in a loop and still waiting for an ACK
	if (status.TX == TXPendingACK){
        
        // Decrement the retry count and if its 0, setup to resend
        if (!status.retryCount--){
            status.TX = TXReady;
        }
    }
    
    // If the radio has a packet pending
    if (status.RX == RXPending){
        
        // Clear all the current RX buffers
        memset(RXPacket.Message, 0 ,sizeof(RXPacket.Message));
        RXPacket.packetData.byte = 0x00;

        // Get the with of the data waiting in the RX buffer
        unsigned char width = nrf24l01Send(n_R_RX_PL_WID, 0);

        // Disable the radio IC
        nrf24l01CELow();

        // Start the SPI transaction and select the radio IC
        nrf24l01SPIStart();

        // Send the command to tell the radio IC that we want the received data buffer
        nrf24l01SPISend(n_R_RX_PAYLOAD);

        // Get the packet data byte as the first byte
        RXPacket.packetData.byte = nrf24l01SPISend(0);
        width--;

        for (i = 0; i < width; i++) {
            // Get the byte from the radio IC
            RXPacket.Message[i] = nrf24l01SPISend(0);
        }

        // End the SPI transaction and release the radio IC
        nrf24l01SPIEnd();

        // Re-enable the radio IO to continue receiving
        nrf24l01CEHigh();
        
        // Get the piped the data was recieved on
		RXPacket.packetData.Pipe = status.statusRegister.RX_P_NO;
        
        // Get the Recieved Power Detector bit
		RXPacket.packetData.RPD = nrf24l01Send(n_R_REGISTER | n_RPD, 0);
        
        // Copy the packet for the user space to use in case they modify it
        strcpy(userRXPacket.Message, RXPacket.Message);
        userRXPacket.packetData.byte = RXPacket.packetData.byte;
    
        status.RX = RXReady;
    }
    
    // If the receive data is ready to be processed, check if its an ACK
    if (status.RX == RXReady){
        
        // If this RX packet required an ACK, send one
        if (RXPacket.packetData.IsACK){
            
            if (status.TX == TXPendingACK){
            
                if (strcmp(RXPacket.Message, TXPacket.Message) == 0){
                            
                    status.TX = TXIdle;
                    status.RX = RXIdle;
                    // Set the radio into transmitter mode to sleep
					nrf24l01SetRXMode(0);
                    
                }
            }
        }
    }
    
    // If the receive packet is ready, and the remote radio request an ACK
    if (status.RX == RXReady){
		if (RXPacket.packetData.ACKRequest){
			
            // modify the packet to look like an ACK
			RXPacket.packetData.ACKRequest = 0;
			RXPacket.packetData.IsACK = 1;
            
            // Set the transmitter pipe to match the remote
            nrf24l01SetTXPipe(RXPacket.packetData.Pipe);
			
            // Send the packet
			nrf24l01SendTXBuffer(&RXPacket);
		}
    }
	
}

void nrf24l01InitRegisters(){
    
    
    status.configRegister.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    
	status.configRegister.PWR_UP = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, status.configRegister.byte);
    
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
    nrf24l01SetRXPipe(0xFF);

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

	// Setup all data pipes with our custom address
    unsigned int i;
    for (i = 0; i < 6; i++){

        nrf24l01SPIStart();
        nrf24l01SPISend(n_W_REGISTER | (n_RX_ADDR_P0 + i));
        
        nrf24l01SPISend(n_ADDRESS_P0[4] + (n_ADDRESS_MUL * i));
        
        if (i < 2){
            nrf24l01SPISend(n_ADDRESS_P0[3]);
            nrf24l01SPISend(n_ADDRESS_P0[2]);
            nrf24l01SPISend(n_ADDRESS_P0[1]);
            nrf24l01SPISend(n_ADDRESS_P0[0]);
        }
        
        nrf24l01SPIEnd();
    }
    
    nrf24l01SetTXPipe(0);

    
    // clear the interrupt flags in case the radio's still asserting an old unhandled interrupt
    status.statusRegister.byte = 0x00;
    status.statusRegister.RX_DR = 1;
    status.statusRegister.TX_DS = 1;
    status.statusRegister.MAX_RT = 1;
    nrf24l01Send(n_W_REGISTER | n_STATUS, status.statusRegister.byte);
    
    status.statusRegister.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    // flush the FIFOs in case there are old data in them.
    nrf24l01Send(n_FLUSH_TX, 0);
    nrf24l01Send(n_FLUSH_RX, 0);
    
    // Enable 2-byte CRC and power up in receive mode.
	status.configRegister.PRIM_RX = 1;
	status.configRegister.EN_CRC = 1;
    status.configRegister.CRCO = 1;
	status.configRegister.PWR_UP = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, status.configRegister.byte);

}

void nrf24l01Init(void){
    
    
    nrf24l01InterfaceInit();
    
    
    /* SPI INIT */
    
    nrf24l01CELow();
    
    delayUs(1000);
    
    nrf24l01InitRegisters();    
    
    delayUs(1000);

    nrf24l01CEHigh();
    
    status.TX = TXIdle;
    status.RX = RXIdle;
}

