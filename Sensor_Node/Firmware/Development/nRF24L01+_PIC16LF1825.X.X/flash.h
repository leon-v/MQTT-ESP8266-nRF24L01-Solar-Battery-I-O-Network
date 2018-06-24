#ifndef FLASH_H
#define	FLASH_H
#include <xc.h> // include processor files - each processor file is guarded.  

unsigned int read_flashmem(unsigned int offset);
void write_flashmem(unsigned int offset, unsigned int data);

 
#endif	/* FLASH_H */

