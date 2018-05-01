#ifndef FLASH_H
#define	FLASH_H
#include <xc.h> // include processor files - each processor file is guarded.  

 #define NV_MEM_SIZE 32 // Erase block size     
 extern const unsigned char NVMEM[NV_MEM_SIZE];         
 
 // NV parameters stored in highest 32 words of program memory.     
 // This is in the special "high endurance" part of Flash.     
 //     
 // The highest address in '1503 is 0x7FF, so...     
 #define NV_ADDRESS (0x800U-NV_MEM_SIZE)  

#endif	/* FLASH_H */

