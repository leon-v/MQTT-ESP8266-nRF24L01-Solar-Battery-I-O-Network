#ifndef NRF24L01SPI_H
#define	NRF24L01SPI_H

#include "nRF24L01+_types.h"
#include <xc.h> // include processor files - each processor file is guarded.  


void nrf24l01SPIInit(void);
unsigned char nrf24l01SPISend(unsigned char byte1, unsigned char byte2);

n_STATUS_t status;

#endif	/* NRF24L01SPI_H */

