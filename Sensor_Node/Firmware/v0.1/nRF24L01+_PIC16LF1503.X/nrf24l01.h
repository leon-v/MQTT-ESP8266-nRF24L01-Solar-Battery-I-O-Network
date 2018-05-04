#ifndef NRF24L01_H
#define	NRF24L01_H

#include <xc.h> // include processor files - each processor file is guarded.  

const unsigned char n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const unsigned char n_ADDRESS_P1[] = {0x9D, 0xBF, 0x97, 0x4D, 0xFB};
const unsigned char n_ADDRESS_MUL = 33;

void nrf24l01ISR(void);
void nrf24l01Init(void);



#endif	/* NRF24L01_H */

