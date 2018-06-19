#ifndef NRF24L01_H
#define	NRF24L01_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "nRF24L01+_types.h"
#include "flash.h"

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

char nrf24l01TXTopic[8];
char nrf24l01TXValue[8];
char nrf24l01RXTopic[8];
char nrf24l01RXValue[8];
char nrf24l01Name[FLASH_OFFSET_NAME_LENGTH];

unsigned int counter = 0;

typedef struct{
    unsigned waitForTXACK       : 1;
    unsigned TXBusy             : 1;
    unsigned RXPending			: 1;
    unsigned RXMode             : 1;
    
} nrf24l01_t;

volatile nrf24l01_t nrf24l01;

//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 83

void nrf24l01ISR(void);
void nrf24l01Init(void);

void nrf24l01SendString(char waitForAck);
void nrf24l01SetRXMode(unsigned char rxMode);

#endif	/* NRF24L01_H */

