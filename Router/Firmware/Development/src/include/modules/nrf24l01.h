#ifndef NRF24L01_H_
#define	NRF24L01_H_

#include "interface.h"
#include "nRF24L01_Types.h"
#include <string.h>

extern const unsigned char n_ADDRESS_P0[];
extern const unsigned char n_ADDRESS_MUL;

typedef struct{
    unsigned TXBusy             : 1;
    unsigned RXPending			: 1;
    unsigned RXMode             : 1;
} nrf24l01_t;

typedef union{
    struct{
        unsigned int byte       :8;
    };
    struct{
        unsigned ACKRequest :1;
        unsigned IsACK      :1;
        unsigned TooLoud    :1;
    };
} packetData_t;

typedef struct{
    packetData_t packetData;
    char Message[32];
} nrf24l01Packet_t;

volatile nrf24l01_t nrf24l01;

//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 0

void nrf24l01ISR(void);
void nrf24l01Init(unsigned char isReciever);

void nrf24l01SendPacket(nrf24l01Packet_t * Packet);
void nrf24l01SetRXMode(unsigned char rxMode);
nrf24l01Packet_t *nrf24l01GetRXPacket(void);
void nrf24l01SendACK(nrf24l01Packet_t * packet);

#endif	/* NRF24L01_H_ */

