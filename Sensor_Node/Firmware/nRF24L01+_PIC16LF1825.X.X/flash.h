#ifndef FLASH_H
#define	FLASH_H
#include <xc.h> // include processor files - each processor file is guarded. 
#include "interface.h"

extern romData_t romData;

typedef union{
    struct{
        romData_t RomData;
    };
    struct{
        unsigned char array[romData_s];
    };
}romHolder_t;

#define romLocation (romSize - romData_s)
const unsigned char romArray[romData_s]@romLocation;

void flashRealod(void);
void flashUpdate(void);
 
#endif	/* FLASH_H */

