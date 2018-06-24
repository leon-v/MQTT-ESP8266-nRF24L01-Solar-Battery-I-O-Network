#include "nrf24l01.h"

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

char nrf24l01TXName[16];
char nrf24l01TXTopic[8];
char nrf24l01TXValue[8];
packetData_t nrf24l01TXPacketData;

char nrf24l01RXTopic[8];
char nrf24l01RXValue[8];
char nrf24l01RXName[16];
packetData_t nrf24l01RXPacketData;

unsigned int counter = 0;

unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    enableInterrupts(0);
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    enableInterrupts(1);
    
    return data;
}


unsigned char nrf24l01GetPipe(){
    
    unsigned char pipe;
    unsigned char i;
    
    for (i = 0; (nrf24l01TXName[i] != '\0') && (i < sizeof(nrf24l01TXName)); i++){
        pipe+= nrf24l01TXName[i];
    }
    
    pipe %= 5;
    pipe *= n_ADDRESS_MUL;
    
    return pipe;
}


void nrf24l01SetTXAddress(){
    
    nrf24l01SPIStart();

	nrf24l01SPISend(n_TX_ADDR);
    
    unsigned char i;
    for (i = 0; i < sizeof(n_ADDRESS_P0) - 1; i++){
        nrf24l01SPISend(n_ADDRESS_P0[i]);
    }
    
    nrf24l01SPISend(nrf24l01GetPipe());
}


void nrf24l01SetRXMode(unsigned char rxMode){
    n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
            
    if (config.PRIM_RX != rxMode){
        
        nrf24l01CELow();
        delayUs(200);
        
//        if (!rxMode){
//            nrf24l01SetTXAddress();
//        }

        config.PRIM_RX = rxMode;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        delayUs(200);

        if (rxMode){
        	nrf24l01CEHigh();
            delayUs(200);
        }
    }
    nrf24l01.RXMode = rxMode;
}


void nrf24l01ReceiveString(void){
    
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
	for (i = 0; i < sizeof(nrf24l01RXName); i++){
		nrf24l01RXName[i] = '\0';
	}
	
    unsigned char width = nrf24l01Send(n_R_RX_PL_WID, 0);
    
    nrf24l01CELow();
    
	nrf24l01SPIStart();

	nrf24l01SPISend(n_R_RX_PAYLOAD);
    
	for (i = 0; (i < sizeof(nrf24l01RXName)) && (offset + i < width) ; i++){
		
		byte = nrf24l01SPISend(0);
		
		if (byte == '/'){
			offset++;
			break;
		}
		
		nrf24l01RXName[i] = byte;
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
    
    nrf24l01SPIEnd();

    nrf24l01CEHigh();

    // Check for ACK
    
    if (!nrf24l01TXPacketData.ACKRequest){
    	return;
    }

    if (strcmp(nrf24l01TXName, nrf24l01RXName) != 0){
    	return;
    }

    if (strcmp(nrf24l01RXTopic, nrf24l01TXTopic) != 0){
    	return;
    }

    if (strcmp(nrf24l01RXValue, "ACK") != 0){
    	return;
    }

	nrf24l01TXPacketData.ACKRequest = 0;
	nrf24l01.RXPending = 0;
	nrf24l01SetRXMode(0);
}

void nrf24l01SendString(void){
	
	// Initalise an iterator for the many loops
    unsigned char i;
    
    if (counter){
        counter--;
    }
	
	// Define where to re-start the send if the previous one failed
	RESEND:
	
	// Wait for the TXBusy to clear so we know the packet has been sent
	i = 0xFF;
    while (nrf24l01.TXBusy){
        if (!--i) {
            goto RESEND;
        }
        delayUs(50);
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
    
    nrf24l01SPISend(nrf24l01TXPacketData.byte);
    
	// Loop through each character of the name buffer and send it to the radio
    for (i = 0; (nrf24l01TXName[i] != '\0') && (i < sizeof(nrf24l01TXName)); i++){
        nrf24l01SPISend(nrf24l01TXName[i]);
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

    // Wait for the TXBusy to clear so we know the packet has been sent
	i = 0xFF;
    while (nrf24l01.TXBusy){
        if (!--i) {
            goto RESEND;
        }
        delayUs(50);
    }
		
	// Wait for the transmit ACK flag to becode clear so we know we got an ACK
	i = 0xFF;
	while (nrf24l01TXPacketData.ACKRequest){
		if (!--i) {
            counter++;
			goto RESEND;
		}
		delayUs(60);
	}
}


void nrf24l01ISR(void){
   
    n_STATUS_t status;
    status.byte = nrf24l01Send(n_R_REGISTER | n_STATUS, 0);
    
    // I have had the IC lock up and return 0x00, reset it
    if (status.byte == 0x00){
    	exception(1);
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
            if (nrf24l01TXPacketData.ACKRequest){
                // Put the radio into receiver mode so we can get an ACK
                nrf24l01SetRXMode(1);
            }
        }
    }

    // Check id there is a received packet waiting
    if (status.RX_DR){

    	nrf24l01.RXPending = 1;
    }
	
	// Clear the interrupt on the nrf24l01
	nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
}


void nrf24l01InitRegisters(unsigned char isReciever){
    
    n_CONFIG_t config;
    
	config.PWR_UP = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    delayUs(10000);
    
    n_SETUP_AW_t setupAW;
    setupAW.byte = 0x00;
    setupAW.AW = 0b11;
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

void nrf24l01Init(unsigned char isReciever){
    
    
    nrf24l01InterfaceInit();
    
    /* SPI INIT */
    
    nrf24l01CELow();
    
    delayUs(50000);
    
    nrf24l01InitRegisters(isReciever);
    
    delayUs(50000);

    nrf24l01CEHigh();
}

