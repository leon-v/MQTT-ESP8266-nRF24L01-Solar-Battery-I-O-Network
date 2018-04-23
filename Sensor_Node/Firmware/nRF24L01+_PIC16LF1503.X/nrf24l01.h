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

void nrf24l01ISR(void);
void nrf24l01Init(void);



#endif	/* NRF24L01_H */

