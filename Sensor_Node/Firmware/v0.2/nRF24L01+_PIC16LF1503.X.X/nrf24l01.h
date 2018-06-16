#ifndef NRF24L01_H
#define	NRF24L01_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "nRF24L01+_types.h"

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

unsigned int counter = 0;

typedef struct{
    n_STATUS_t status;
    unsigned waitForTXACK       : 1;
    unsigned waitForTXACKCount  : 4;
    unsigned TXBusy             : 1;
    unsigned TXBusyCount        : 4;
    unsigned RXPending			: 1;
    unsigned RXMode             : 1;
    char txTopic[6];
    char txValue[8];
    char rxTopic[6];
    char rxValue[8];
    
} nrf24l01_t;

volatile nrf24l01_t nrf24l01;

//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 83

void nrf24l01ISR(void);
void nrf24l01Init(void);

void nrf24l01SendStart(void);
void nrf24l01SendByte(unsigned char payloadByte);
void nrf24l01SendEnd(void);
void nrf24l01SetRecieveMode(void);

void nrf24l01SendString(char waitForAck);
void nrf24l01SendFlash(unsigned char offset);

#endif	/* NRF24L01_H */

