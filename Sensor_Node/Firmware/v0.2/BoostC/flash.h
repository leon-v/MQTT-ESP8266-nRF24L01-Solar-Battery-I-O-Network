#ifndef FLASH_H
#define	FLASH_H

 #define NV_MEM_SIZE 32 // Erase block size
 extern const unsigned char NVMEM[NV_MEM_SIZE];         

 // NV parameters stored in highest 32 words of program memory.     
 // This is in the special "high endurance" part of Flash.     
 //     
 // The highest address in '1503 is 0x7FF, so...     
 #define NV_ADDRESS (0x800U-NV_MEM_SIZE)  

 const unsigned char NVMEM[NV_MEM_SIZE]@NV_ADDRESS = {
    'U', 'n', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'e', 'd', '1', 0, 0, 0,   //FLASH_OFFSET_NAME
    0x0000,                                                                     //FLASH_OFFSET_BOOT_COUNT
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 };
 
 #define FLASH_OFFSET_NAME          0
 #define FLASH_OFFSET_BOOT_COUNT    16


unsigned int read_flashmem(unsigned int offset);
void write_flashmem(unsigned int offset, unsigned int data);

 
#endif	/* FLASH_H */

