#include <xc.h>
#include <pic16lf1503.h>
#include "nRF24L01+_types.h"
#include "nrf24l01.h"
#include "config.h"
#include "flash.h"

void nrf24l01ISR(void){
    
}

n_STATUS_t status;

void nrf24l01SPIStart(void){
    PORTAbits.RA1 = 0;
}

unsigned char nrf24l01SPISend(unsigned char data){
    SSP1BUF = data;
    while (!SSP1STATbits.BF){ NOP(); }
    data = SSP1BUF;
    return data;
}

void nrf24l01SPIEnd(void){
    PORTAbits.RA1 = 1;
    __delay_us(5);
}

unsigned char nrf24l01Send(unsigned char command,unsigned char data) {
    
    nrf24l01SPIStart();
    
    status.byte = nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    return data;
}


void nrf24l01SendStart(void){
    
    // Clear config bit
    n_CONFIG_t config;
	config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
	config.PRIM_RX = 0;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(n_W_TX_PAYLOAD);
}
void nrf24l01SendByte(unsigned char payloadByte){
    nrf24l01SPISend(payloadByte);
}

void nrf24l01SendEnd(void){
    
    nrf24l01SPIEnd();

    PORTAbits.RA0 = 1;
    __delay_us(10);
    PORTAbits.RA0 = 0;
}

void nrf24l01Init(void){
    
    // 11 INT
    // 12 CS
    // 13 CE
    
    TRISAbits.TRISA0 = 0; // CE out
    PORTAbits.RA0 = 0;
    
    /* SPI INIT */
    TRISAbits.TRISA1 = 0; // CS out
    PORTAbits.RA1 = 1;
    
    TRISAbits.TRISA1 = 0; // CS out
    PORTAbits.RA1 = 1;
    
    TRISCbits.TRISC1 = 1; //MISO
    TRISCbits.TRISC2 = 0; // MOSI
    
    TRISCbits.TRISC0 = 0; // CLK
    
    SSPCON1bits.SSPEN = 0; 
    SSPCON1bits.CKP = 0;
    SSP1STATbits.CKE = 1;
//    SSP1STATbits.CKE = 0;
    SSPCON1bits.SSPM = 0b0000;
    
    SSPCON1bits.SSPEN = 1;
       
    // Set config bit
    n_CONFIG_t config;
	config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0); //1
	config.PWR_UP = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte); //2
    
    // Set Frequency
    n_RF_CH_t channel;
    channel.RF_CH = RADIO_FREQUENCY;
	nrf24l01Send(n_W_REGISTER | n_RF_CH, channel.byte);
    
    
    unsigned char pipe = 0;
    unsigned char i = 0;
    unsigned char byte;
    
    while (i < 16){
        byte = read_flashmem((unsigned) FLASH_OFFSET_NAME + i);
        
        if (byte == 0){
            break;
        }
        
        pipe+= byte;
        
        i++;
    }
    
    pipe = (unsigned) pipe % 5;
    
    // Set TX_ADDR
    nrf24l01SPIStart();
    status.byte = nrf24l01SPISend(n_W_REGISTER | n_TX_ADDR);
    nrf24l01SPISend(n_ADDRESS_P0[0]);
    nrf24l01SPISend(n_ADDRESS_P0[1]);
    nrf24l01SPISend(n_ADDRESS_P0[2]);
    nrf24l01SPISend(n_ADDRESS_P0[3]);
    nrf24l01SPISend(n_ADDRESS_P0[4] + (unsigned) (pipe * n_ADDRESS_MUL));
    nrf24l01SPIEnd();
    
    // Set RX pipe
    nrf24l01SPIStart();
    status.byte = nrf24l01SPISend(n_W_REGISTER | n_RX_ADDR_P0);
    nrf24l01SPISend(n_ADDRESS_P0[0]);
    nrf24l01SPISend(n_ADDRESS_P0[1]);
    nrf24l01SPISend(n_ADDRESS_P0[2]);
    nrf24l01SPISend(n_ADDRESS_P0[3]);
    nrf24l01SPISend(n_ADDRESS_P0[4] + (unsigned) (pipe * n_ADDRESS_MUL));
    nrf24l01SPIEnd();
    
    
    // Set pipes payload lengths to 32
//	n_RX_PW_t rxPW;
//	rxPW.RX_PW = 32;
//	nrf24l01Send(n_W_REGISTER | n_RX_PW_P0, rxPW.byte); // 7
//	nrf24l01Send(n_W_REGISTER | n_RX_PW_P1, rxPW.byte); // 8
//	nrf24l01Send(n_W_REGISTER | n_RX_PW_P2, rxPW.byte); // 9
//	nrf24l01Send(n_W_REGISTER | n_RX_PW_P3, rxPW.byte); // 10
//	nrf24l01Send(n_W_REGISTER | n_RX_PW_P4, rxPW.byte); // 11
//	nrf24l01Send(n_W_REGISTER | n_RX_PW_P5, rxPW.byte); // 12
    
    // Set dynamic payload length
	n_FEATURE_t feature;
	feature.byte = nrf24l01Send(n_R_REGISTER | n_FEATURE, 0);
	feature.EN_DPL = 1;
	nrf24l01Send(n_W_REGISTER | n_FEATURE, feature.byte); 
}

