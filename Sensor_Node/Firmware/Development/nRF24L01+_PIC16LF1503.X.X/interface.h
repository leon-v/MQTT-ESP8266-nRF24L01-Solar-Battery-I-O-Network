#ifndef INTERFACE_H
#define	INTERFACE_H

#include <xc.h> // include processor files - each processor file is guarded.

 #define NV_MEM_SIZE 32 // Erase block size
 extern const unsigned char NVMEM[NV_MEM_SIZE];         

 // NV parameters stored in highest 32 words of program memory.     
 // This is in the special "high endurance" part of Flash.     
 //     
 // The highest address in '1503 is 0x7FF, so...     
 #define NV_ADDRESS (0x800U-NV_MEM_SIZE)  

 const unsigned char NVMEM[NV_MEM_SIZE]@NV_ADDRESS = {
    'U', 'n', 'c', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'e', 'd', 'W', 0, 0, 0,   //FLASH_OFFSET_NAME
    0x0000,                                                                     //FLASH_OFFSET_BOOT_COUNT
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
 };

#define FLASH_OFFSET_NAME_LENGTH		16
#define FLASH_OFFSET_NAME				0
 
#define FLASH_OFFSET_BOOT_REASON_LENGTH	1
#define FLASH_OFFSET_BOOT_REASON		FLASH_OFFSET_NAME + FLASH_OFFSET_NAME_LENGTH

#define _XTAL_FREQ 16000000

#define delayUs(x) __delay_us(x)
#define delayMs(x) __delay_ms(x)

#define append(x) x + strlen(x)

#define nrf24l01CELow() PORTAbits.RA0 = 0
#define nrf24l01CEHigh() PORTAbits.RA0 = 1
#define nrf24l01CSLow() PORTAbits.RA1 = 0
#define nrf24l01CSHigh() PORTAbits.RA1 = 1

void nrf24l01InterfaceInit(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);

void enableInterrupts(unsigned char enable);
void exception(unsigned int value);


#endif	/* INTERFACE_H */

