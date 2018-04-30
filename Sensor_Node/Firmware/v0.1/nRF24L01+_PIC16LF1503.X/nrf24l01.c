#include <xc.h>
#include "nrf24l01spi.h"
#include "nRF24L01+_types.h"
#include "nrf24l01.h"


void nrf24l01ISR(void){
    
}

void nrf24l01Init(void){
    
    n_CONFIG_t config;
    config.byte = nrf24l01SPISend(n_R_REGISTER | n_CONFIG, 0);
    config.PRIM_RX = 0;
    nrf24l01SPISend(n_W_REGISTER | n_CONFIG, config.byte);
}

void nrf24l01RecieveMode(){
    
}

void nrf24l01Transmit(){
    
}