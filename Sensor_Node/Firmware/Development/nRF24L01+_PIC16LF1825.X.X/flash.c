#include "flash.h"
#include "interface.h"

romHolder_t romHolder;
romData_t romData;


void flashWriteByte(unsigned int offset, unsigned int data) {
    
    unsigned int address;
    
    INTCONbits.GIE = 0; //disable interupts incase they interfere
    
    //ERASE SECTION
    PMCON1 = 0x00;     //not configuration space
    
    address = romLocation + offset;
    PMADRL = (char) (address >> 0);  //least significant bits of address
    PMADRH = (char) (address >> 8);  //most significant bits of address 
    
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
    
    PMADRL = (char) (address >> 0);  //least significant bits of address
    PMADRH = (char) (address >> 8);  //most significant bits of address 
    
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

unsigned int flashReadByte(unsigned int offset) {
    
    unsigned int address;
    
    INTCONbits.GIE = 0; //disable interupts incase they interfere
    
    PMCON1 = 0x00;     //not configuration space
    
    address = romLocation + offset;
    PMADRL = (char) (address >> 0);  //least significant bits of address
    PMADRH = (char) (address >> 8);  //most significant bits of address 
    
    PMCON1bits.RD = 1;  //initiate read operation
    
    NOP();              //to give time to read
    NOP();              //to give time to read
    
    unsigned int result = 0;
    result = PMDATL;
    result|= ( (unsigned) (PMDATH) << 8);
    
    INTCONbits.GIE = 1;        //enable interupts again
    
    return result;
}

void flashRealod(void){
    
    for (unsigned int i = 0; i < romData_s; i++){
        romHolder.array[i] = flashReadByte(i);
    };
}

void flashUpdate(void){
    for (unsigned int i = 0; i < romData_s; i++){
        flashWriteByte(i, romHolder.array[i]);
    };
}