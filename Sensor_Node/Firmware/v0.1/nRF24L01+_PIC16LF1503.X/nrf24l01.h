#ifndef NRF24L01_H
#define	NRF24L01_H

#include <xc.h> // include processor files - each processor file is guarded.  

#define ReadRegister        0b00000000
#define WriteRegister       0b00100000
#define ReadRXPayload       0b01100001
#define WriteRXPayload      0b10100000
#define FlushTX             0b11100001
#define FlushRX             0b11100010
#define ReuseTXPayload      0b11100011
#define ReadRXPayloadWidth  0b01100000
#define WriteACKPayload     0b10101000
#define WriteTXPayloadNoACK 0b10110000
#define NoOperation         0b11111111

#define nrf24l01CONFIG 0x00 
typedef struct {
    unsigned PRIM_RX       : 1;
    unsigned PWR_UP        : 1;
    unsigned CRCO          : 1;
    unsigned EN_CRC        : 1;
    unsigned MASK_MAX_RT   : 1;
    unsigned MASK_TX_DS    : 1;
    unsigned MASK_INT_DR   : 1;
    unsigned reserved      : 1;
} nrf24l01CONFIGbits_t;


void nrf24l01ISR(void);
void nrf24l01Init(void);



#endif	/* NRF24L01_H */

