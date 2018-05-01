#include <pic16lf1503.h>
#include <xc.h>
#include "flash.h"

const unsigned char NVMEM[NV_MEM_SIZE]@NV_ADDRESS = {
     0xfe, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff,     
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,     
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,         
     0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff     
 };

void write_flashmem(unsigned int offset, unsigned int data) {
    
    INTCONbits.GIE = 0; //disable interupts incase they interfere
    
    //ERASE SECTION
    PMCON1 = 0x00;     //not configuration space
    
    PMADRL = (char) ((NV_ADDRESS + offset) >> 0);  //least significant bits of address
    PMADRH = (char) ((NV_ADDRESS + offset) >> 8);  //most significant bits of address 
    
    PMCON1bits.FREE = 1; //specify erase operation
    PMCON1bits.WREN = 1; //allow write
    
    PMCON2 = 0x55;  //unlock program memory
    PMCON2 = 0xAA;  //unlock program memory
    
    PMCON1bits.WR = 1; //begin write
    
    NOP();    //to give time to write
    NOP();    //to give time to write
    
    PMCON1bits.WREN = 0; //disallow write
    //END OF ERASE SECTION

    //WRITE SECTION
    PMCON1 = 0x00;     //not configuration space
    
    PMADRL = (char) ((NV_ADDRESS + offset) >> 0);  //least significant bits of address
    PMADRH = (char) ((NV_ADDRESS + offset) >> 8);  //most significant bits of address 
    
    PMCON1bits.FREE = 0;    //selecting write operation
    PMCON1bits.LWLO = 1;    //load write latches only
    PMCON1bits.WREN = 1;    //allow write
    
    PMDATL = (data >> 0);  //write least significant bits of data to latch
    PMDATH = (data >> 8);  //write most significant bits of data to latch
    
    PMCON1bits.LWLO = 0;   //write latches to flash
    
    PMCON2 = 0x55;          //unlock program memory
    PMCON2 = 0xAA;          //unlock program memory
    
    PMCON1bits.WR = 1;      //begin write
    
    NOP();                  //to give time to write
    NOP();                  //to give time to write
    
    PMCON1bits.WREN = 0;    //disallow write
    
    //END OF WRITE SECTION
    INTCONbits.GIE = 1;        //enable interupts again
}

unsigned int read_flashmem(unsigned int offset) {
    
    PMCON1 = 0x00;     //not configuration space
    
    PMADRL = (char) ((NV_ADDRESS + offset) >> 0);  //least significant bits of address
    PMADRH = (char) ((NV_ADDRESS + offset) >> 8);  //most significant bits of address 
    
    PMCON1bits.RD = 1;  //initiate read operation
    
    NOP();              //to give time to read
    NOP();              //to give time to read
    
    return (unsigned) ((PMDATH) << 8) | (PMDATL);  //joins bytes & returns the value stored
}

