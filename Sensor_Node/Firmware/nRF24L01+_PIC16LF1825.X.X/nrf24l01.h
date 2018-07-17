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
    unsigned Pipe               : 3;
} nrf24l01_t;


typedef union{
    struct{
        unsigned int byte       :8;
    };
    struct{
    	unsigned RPD    	:1;
		unsigned ACKRPD    	:1;
        unsigned ACKRequest :1;
        unsigned IsACK      :1;
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
void nrf24l01Init(void);

void nrf24l01SendPacket(nrf24l01Packet_t * Packet);
void nrf24l01SetRXMode(unsigned char rxMode);
nrf24l01Packet_t *nrf24l01GetRXPacket(void);
void nrf24l01SendACK(nrf24l01Packet_t * packet);
void nrf24l01ChangeTXPower(int addPower);
unsigned char nrf24l01Send(unsigned char command, unsigned char data);
void nrf24l01SetTXPipe(char * name);
void nrf24l01SetRXPipe(char * name);

#endif	/* NRF24L01_H_ */

