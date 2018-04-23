#include <xc.h>
#include "nrf24l01spi.h"
#include "nrf24l01.h"

nrf24l01SPIData_t spiData;

void nrf24l01ISR(void){
    nrf24l01SPIISR(spiData);
}

void nrf24l01Init(void){
    nrf24l01SPIInit(spiData);
}
