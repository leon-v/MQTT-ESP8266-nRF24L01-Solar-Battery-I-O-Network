#ifndef NRF24L01SPI_H
#define	NRF24L01SPI_H

#include <xc.h> // include processor files - each processor file is guarded.  

typedef struct {
    unsigned char command;
    unsigned char status;
    unsigned int request;
    unsigned int result;
    unsigned char byte;
} nrf24l01SPIData_t;

void nrf24l01SPIInit(nrf24l01SPIData_t spiData);
unsigned char nrf24l01SPIComplete(nrf24l01SPIData_t spiData);
void nrf24l01SPIISR(nrf24l01SPIData_t spiData);
void nrf24l01SPISend(nrf24l01SPIData_t spiData);

#endif	/* NRF24L01SPI_H */

