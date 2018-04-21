#include <xc.h>
#include <pic16lf1503.h>
#include "spi.h"

void main(void) {
    
    OSCCONbits.IRCF = 0b1111; // 16 MHz
    OSCCONbits.SCS = 0b10; // Internal oscillator block
    
    SPIInit();
    
    
    return;
}
