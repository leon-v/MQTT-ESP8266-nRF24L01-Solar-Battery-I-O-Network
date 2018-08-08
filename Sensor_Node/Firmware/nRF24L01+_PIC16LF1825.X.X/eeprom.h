#ifndef EEPROM_H
#define	EEPROM_H

#include <xc.h> // include processor files - each processor file is guarded.  

void EEPROMWrite(unsigned int address, unsigned char data);
unsigned char EEPROMRead(unsigned int address);

#endif	/* XC_HEADER_TEMPLATE_H */

