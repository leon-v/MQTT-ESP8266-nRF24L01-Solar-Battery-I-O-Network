#include <xc.h>
#include "nrf24l01spi.h"
#include "nrf24l01.h"

nrf24l01SPIData_t spiData;

void nrf24l01ISR(void){
    nrf24l01SPIISR(spiData);
}

void nrf24l01Init(void){
    nrf24l01SPIInit(spiData);
    
    while (!nrf24l01SPIComplete()){ NOP(); }
    
    spiData.command = ReadRegister + nrf24l01CONFIG;
    nrf24l01SPISend(spiData);
    
    while (!nrf24l01SPIComplete()){ NOP(); }
}

void nrf24l01RecieveMode(){
    
}

void nrf24l01Transmit(){
    
}