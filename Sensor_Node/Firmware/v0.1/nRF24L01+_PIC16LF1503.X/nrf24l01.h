#ifndef NRF24L01_H
#define	NRF24L01_H

#include <xc.h> // include processor files - each processor file is guarded.  

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_MUL = 33;

//Transmitters using e.i.r.p.s greater than 0 dBW (1 W)
//must employ frequency hopping or digital modulation techniques.
#define RADIO_FREQUENCY 83

void nrf24l01ISR(void);
void nrf24l01Init(void);

void nrf24l01SendStart(void);
void nrf24l01SendByte(unsigned char payloadByte);
void nrf24l01SendEnd(void);
void nrf24l01SetRecieveMode(void);

void nrf24l01SendString(char * string);
void nrf24l01SendFlash(unsigned char offset);

#endif	/* NRF24L01_H */

