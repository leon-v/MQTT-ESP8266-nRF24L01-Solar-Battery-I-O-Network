#ifndef NRF24L01_H_
#define	NRF24L01_H_

#include "interface.h"
#include "nRF24L01_Types.h"
#include <string.h>

extern const unsigned char n_ADDRESS_P0[];
extern const unsigned char n_ADDRESS_MUL;

typedef union{
    struct{
        unsigned byte       :8;
    };
    struct{
        unsigned ACKRequest :1;
        unsigned IsACK      :1;
        unsigned Always1    :1;
    };
} packetData_t;

extern char nrf24l01TXName[16];
extern char nrf24l01TXTopic[8];
extern char nrf24l01TXValue[8];
extern packetData_t nrf24l01TXPacketData;

extern char nrf24l01RXTopic[8];
extern char nrf24l01RXValue[8];
extern char nrf24l01RXName[16];
extern packetData_t nrf24l01RXPacketData;

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
void nrf24l01Init(unsigned char isReciever);

void nrf24l01SendString(void);
void nrf24l01SetRXMode(unsigned char rxMode);

#endif	/* NRF24L01_H_ */

