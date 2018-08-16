#ifndef NRF24L01_H_
#define	NRF24L01_H_

#include "interface.h"
#include "nRF24L01_Types.h"
#include <string.h>

extern const unsigned char n_ADDRESS_P0[];
extern const unsigned char n_ADDRESS_MUL;


typedef struct{
    unsigned char TX;
    unsigned char RX;
    n_STATUS_t statusRegister;
    n_CONFIG_t configRegister;
    unsigned char retryCount;
} nrf24l01State_t;

volatile nrf24l01State_t status;

#define TXIdle 0
#define TXReady 1
#define TXSending 2
#define TXSent 3
#define TXPendingACK 4

#define RXIdle 0
#define RXPending 1
#define RXReady 2
#define RXCheckACKIn 3
#define RXCheckACKOut 4
#define RXUserProcess 5

typedef union{
    struct{
        unsigned int byte       :8;
    };
    struct{
    	unsigned RPD    	: 1;
		unsigned ACKRPD    	: 1;
        unsigned ACKRequest : 1;
        unsigned IsACK      : 1;
        unsigned Pipe		: 3;
    };
} packetData_t;

typedef struct{
    packetData_t packetData;
    char Message[32];
} nrf24l01Packet_t;

//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 0

unsigned char nrf24l01Send(unsigned char command,unsigned char data);
void nrf24l01SetRXPipe(unsigned char pipe);
void nrf24l01SetRXMode(unsigned char rxMode);

void nrf24l01ISR(void);
void nrf24l01Init(void);
void nrf24l01Service(void);
void nrf24l01SetTXPipe(unsigned char pipe);
void nrf24l01SendPacket(nrf24l01Packet_t * txPacket);

#endif	/* NRF24L01_H_ */

