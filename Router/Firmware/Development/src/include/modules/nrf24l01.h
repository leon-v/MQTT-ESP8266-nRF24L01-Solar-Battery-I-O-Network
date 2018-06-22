#ifndef NRF24L01_H_
#define	NRF24L01_H_

#include "radio_interface.h"
#include "nRF24L01_Types.h"
#include <string.h>

extern const i_uint8_t n_ADDRESS_P0[];
extern const i_uint8_t n_ADDRESS_MUL;

extern i_int8_t nrf24l01TXName[16];
extern i_int8_t nrf24l01TXTopic[8];
extern i_int8_t nrf24l01TXValue[8];

extern i_int8_t nrf24l01RXTopic[8];
extern i_int8_t nrf24l01RXValue[8];
extern i_int8_t nrf24l01RXName[16];

typedef struct{
    unsigned waitForTXACK       : 1;
    unsigned TXBusy             : 1;
    unsigned RXPending			: 1;
    unsigned RXMode             : 1;
    unsigned Pipe             	: 3;
    
} nrf24l01_t;

volatile nrf24l01_t nrf24l01;

//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 0

void nrf24l01ISR(void);
void nrf24l01Init(i_uint8_t isReciever);

void nrf24l01SendString(i_uint8_t waitForAck);
void nrf24l01SetRXMode(i_uint8_t rxMode);

#endif	/* NRF24L01_H_ */

