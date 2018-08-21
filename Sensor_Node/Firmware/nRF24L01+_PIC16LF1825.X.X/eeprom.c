#include <xc.h>
#include <string.h>
//#include <stdlib.h>
//#include <stdio.h>
#include "eeprom.h"

void EEPROMWrite(unsigned int address, unsigned char data){
	
    unsigned char GIEBitValue = INTCONbits.GIE;

    NVMADRH = ((address >> 8) & 0xFF);
    NVMADRL = (address & 0xFF);
    NVMDATL = data;    
    NVMCON1bits.NVMREGS = 1;
    NVMCON1bits.WREN = 1;
    INTCONbits.GIE = 0;     // Disable interrupts
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    NVMCON1bits.WR = 1;
    // Wait for write to complete
    while (NVMCON1bits.WR){
		NOP();
	}

    NVMCON1bits.WREN = 0;
    INTCONbits.GIE = GIEBitValue;   // restore interrupt enable
}

unsigned char EEPROMRead(unsigned int address){
    NVMADRH = ((address >> 8) & 0xFF);
    NVMADRL = (address & 0xFF);
    NVMCON1bits.NVMREGS = 1;    
    NVMCON1bits.RD = 1;
    NOP();  // NOPs may be required for latency at high frequencies
    NOP();

    return (NVMDATL);
}