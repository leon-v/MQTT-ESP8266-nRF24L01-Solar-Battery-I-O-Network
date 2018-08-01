#include "nrf24l01.h"

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

nrf24l01Packet_t * TXPacket;
nrf24l01Packet_t RXPacket;


typedef struct{
    unsigned char TX    : 4;
    unsigned char RX    : 4;
    n_STATUS_t statusRegister;
} nrf24l01State_t;

typedef struct{
    unsigned char Idle;
    unsigned char Ready;
    unsigned char Sending;
    unsigned char Sent;
    unsigned char PendingACK;
} nrf24l01TXStates_t;

typedef struct{
    unsigned char Idle;
    unsigned char Pending;
    unsigned char Ready;
    unsigned char CheckACKIn;
    unsigned char CheckACKOut;
    unsigned char UserProcess;
} nrf24l01RXStates_t;

typedef struct{
    nrf24l01TXStates_t TX;
    nrf24l01RXStates_t RX;
} nrf24l01States_t;

static const nrf24l01States_t statuses = {
    {0, 1, 2, 3, 4},
    {0, 1, 2, 3, 4, 5}
};

volatile nrf24l01State_t status;

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
    
//    if (rxMode){
//        if (status.TX == statuses.TX.Sending){
//            return;
//        }
//    }
//    
//    if (!rxMode){
//        if (status.TX == statuses.TX.PendingACK){
//            return;
//        }
//    }
    
    
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
}

//void nrf24l01SendACK(nrf24l01Packet_t * packet){
//	nrf24l01SetTXPipe(packet->packetData.Pipe);
//	packet->packetData.ACKRequest = 0;
//	packet->packetData.IsACK = 1;
//	packet->packetData.ACKRPD = packet->packetData.RPD;
//	
//
//	nrf24l01SendPacket(packet);
//}



//void nrf24l01CheckACK(void){
//    /* Check if the RX packet is an ACK */
//    
//    // If the current RX packet is not an ACK, skip
//    if (!RXPacket.packetData.IsACK){
//        return;
//    }
//    
//    // Clear RX Pending flag so we don't try process this packet as a real one
////	nrf24l01.RXPending = 0;
//    
//    // If the current TX packet doesn't require an ACK, skip
//    if (!TXPacket->packetData.ACKRequest){
//        return;
//    }
//    
//    // If the TX and RX do not match, skip.
//    if (strcmp(TXPacket->Message, RXPacket.Message) != 0){
//        return;
//    }
//    
//    // We have a valid ACK packet
//    
//    
//    
//    // Clear the ACKRequest to signal that we no longer need to wait
//	TXPacket->packetData.ACKRequest = 0;
//
//    // Switch the radio back to TX mode so we don't sit there receiving.
//	nrf24l01SetRXMode(0);
//}


nrf24l01Packet_t *nrf24l01GetRXPacket(void){
	return &RXPacket;
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




unsigned int nrf24l01SendPacket(nrf24l01Packet_t * txPacket){
    
    nrf24l01Service();
    
    if (status.TX == statuses.TX.Idle){
        
        TXPacket = txPacket;
        status.TX = statuses.TX.Ready;
        
        nrf24l01Service();
        
        return 1;
    }
    
    return 0;
}

void nrf24l01ISR(void){
    
    status.statusRegister.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
	
	if (status.statusRegister.TX_DS){
        
        if (status.TX == statuses.TX.Sending){
            status.TX = statuses.TX.Sent;
            nrf24l01Service();
        }
        
        else{
            status.statusRegister.TX_DS = 0;
        }
    }

    // Check id there is a received packet waiting
    if (status.statusRegister.RX_DR){
        if (status.RX == statuses.RX.Idle){
            status.RX = statuses.RX.Pending;
            nrf24l01Service();
        }
        
        else{
            status.statusRegister.RX_DR = 0;
        }
    }
    
	// Clear the interrupt on the nrf24l01
	nrf24l01Send(n_W_REGISTER | n_STATUS, status.statusRegister.byte);
}


void nrf24l01Service(void){
    
    unsigned char i;
            
    if (status.TX == statuses.TX.Ready){

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
        for (i = 0; (i  < strlen(TXPacket->Message)) && (i < 31); i++) {
            nrf24l01SPISend(TXPacket->Message[i]);
        }

        // Release the SPI bus from the radio
        nrf24l01SPIEnd();

        // Setup the status as sending
        status.TX = statuses.TX.Sending;
        
        // Enable interrupts while sending.
        enableInterrupts(1);

        // Pull the CE pin high on the radio for at least 10us
        nrf24l01CEHigh();
        delayUs(12);
        nrf24l01CELow();
    }

    if (status.TX == statuses.TX.Sending){
        // ISR handles this condition
    }

    if (status.TX == statuses.TX.Sent){
        
        // If the transmit data requires an ACK
        if (TXPacket->packetData.ACKRequest){
            status.TX = statuses.TX.PendingACK;
        }

        // If the transmit data does not require an ACK, All done.
        else{
            status.TX = statuses.TX.Idle;
        }
    }


    if (status.TX == statuses.TX.PendingACK){
        
        // Set the radio into receiver mode
        nrf24l01SetRXMode(1);
        
        // Debug
        status.TX = statuses.TX.Idle;
    }
    
    if (status.RX == statuses.RX.Pending){
        
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

        for (i = 0; (i < width) && (i < sizeof(RXPacket.Message)); i++){
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
        
        status.RX = statuses.RX.Ready;
    }
    
    if (status.RX == statuses.RX.Ready){
        
        
        // If this RX packet required an ACK, send one
        
        
    }
    
}

void nrf24l01InitRegisters(){

    n_CONFIG_t config;
    config.byte = 0x00;
    
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
    
    delayUs(50000);
    
    nrf24l01InitRegisters();    
    
    delayUs(50000);

    nrf24l01CEHigh();
    
    status.TX = statuses.TX.Idle;
    status.RX = statuses.RX.Idle;
}

