#ifndef INTERFACE_H
#define	INTERFACE_H

#include <xc.h> // include processor files - each processor file is guarded. 

  // NV parameters stored in highest 32 words of program memory.     
 // This is in the special "high endurance" part of Flash.     
 //     
 // The highest address in '1503 is 0x7FF, so...


typedef struct{
        unsigned char check;    //1
        char name[16];          //16
        unsigned int bootMode;  //2
        float tempCalVf;        //4
        float tempCalTc;        //4
        float tempCalOffset;    //4
} romData_t;

typedef union{
    struct{
        romData_t RomData;
    };
    struct{
        unsigned char bytes[sizeof(romData_t)];
    };
} romDataMap_t;

romDataMap_t romDataMap;
romData_t * romData = &romDataMap.RomData;

//static const romData_t resetRomData = {
//     {0xAA},
//     {"UHT"},
//     {0},
//     {0.606},
//     {-0.00132},
//     {40}
//};

#define _XTAL_FREQ 32000000

#define delayUs(x) __delay_us(x)
#define delayMs(x) __delay_ms(x)

#define append(x) x + strlen(x)

void nrf24l01CELow(void);
void nrf24l01CEHigh(void);
void nrf24l01CSLow(void);
void nrf24l01CSHigh(void);

void nrf24l01InterfaceInit(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);

void enableInterrupts(unsigned char enable);

void exception(unsigned char exception);

#endif	/* INTERFACE_H */

