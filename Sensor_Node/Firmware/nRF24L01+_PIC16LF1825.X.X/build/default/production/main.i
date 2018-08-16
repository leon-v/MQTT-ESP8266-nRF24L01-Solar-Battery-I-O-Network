
# 1 "main.c"

# 18 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\xc.h"
extern const char __xc8_OPTIM_SPEED;

extern double __fpnormalize(double);


# 13 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\xc8debug.h"
#pragma intrinsic(__builtin_software_breakpoint)
extern void __builtin_software_breakpoint(void);

# 52 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\pic16lf18325.h"
extern volatile unsigned char INDF0 __at(0x000);

asm("INDF0 equ 00h");


typedef union {
struct {
unsigned INDF0 :8;
};
} INDF0bits_t;
extern volatile INDF0bits_t INDF0bits __at(0x000);

# 72
extern volatile unsigned char INDF1 __at(0x001);

asm("INDF1 equ 01h");


typedef union {
struct {
unsigned INDF1 :8;
};
} INDF1bits_t;
extern volatile INDF1bits_t INDF1bits __at(0x001);

# 92
extern volatile unsigned char PCL __at(0x002);

asm("PCL equ 02h");


typedef union {
struct {
unsigned PCL :8;
};
} PCLbits_t;
extern volatile PCLbits_t PCLbits __at(0x002);

# 112
extern volatile unsigned char STATUS __at(0x003);

asm("STATUS equ 03h");


typedef union {
struct {
unsigned C :1;
unsigned DC :1;
unsigned Z :1;
unsigned nPD :1;
unsigned nTO :1;
};
struct {
unsigned CARRY :1;
unsigned :1;
unsigned ZERO :1;
};
} STATUSbits_t;
extern volatile STATUSbits_t STATUSbits __at(0x003);

# 171
extern volatile unsigned short FSR0 __at(0x004);



extern volatile unsigned char FSR0L __at(0x004);

asm("FSR0L equ 04h");


typedef union {
struct {
unsigned FSR0L :8;
};
} FSR0Lbits_t;
extern volatile FSR0Lbits_t FSR0Lbits __at(0x004);

# 195
extern volatile unsigned char FSR0H __at(0x005);

asm("FSR0H equ 05h");


typedef union {
struct {
unsigned FSR0H :8;
};
} FSR0Hbits_t;
extern volatile FSR0Hbits_t FSR0Hbits __at(0x005);

# 215
extern volatile unsigned short FSR1 __at(0x006);



extern volatile unsigned char FSR1L __at(0x006);

asm("FSR1L equ 06h");


typedef union {
struct {
unsigned FSR1L :8;
};
} FSR1Lbits_t;
extern volatile FSR1Lbits_t FSR1Lbits __at(0x006);

# 239
extern volatile unsigned char FSR1H __at(0x007);

asm("FSR1H equ 07h");


typedef union {
struct {
unsigned FSR1H :8;
};
} FSR1Hbits_t;
extern volatile FSR1Hbits_t FSR1Hbits __at(0x007);

# 259
extern volatile unsigned char BSR __at(0x008);

asm("BSR equ 08h");


typedef union {
struct {
unsigned BSR :5;
};
struct {
unsigned BSR0 :1;
unsigned BSR1 :1;
unsigned BSR2 :1;
unsigned BSR3 :1;
unsigned BSR4 :1;
};
} BSRbits_t;
extern volatile BSRbits_t BSRbits __at(0x008);

# 311
extern volatile unsigned char WREG __at(0x009);

asm("WREG equ 09h");


typedef union {
struct {
unsigned WREG0 :8;
};
} WREGbits_t;
extern volatile WREGbits_t WREGbits __at(0x009);

# 331
extern volatile unsigned char PCLATH __at(0x00A);

asm("PCLATH equ 0Ah");


typedef union {
struct {
unsigned PCLATH :7;
};
} PCLATHbits_t;
extern volatile PCLATHbits_t PCLATHbits __at(0x00A);

# 351
extern volatile unsigned char INTCON __at(0x00B);

asm("INTCON equ 0Bh");


typedef union {
struct {
unsigned INTEDG :1;
unsigned :5;
unsigned PEIE :1;
unsigned GIE :1;
};
} INTCONbits_t;
extern volatile INTCONbits_t INTCONbits __at(0x00B);

# 384
extern volatile unsigned char PORTA __at(0x00C);

asm("PORTA equ 0Ch");


typedef union {
struct {
unsigned RA0 :1;
unsigned RA1 :1;
unsigned RA2 :1;
unsigned RA3 :1;
unsigned RA4 :1;
unsigned RA5 :1;
};
} PORTAbits_t;
extern volatile PORTAbits_t PORTAbits __at(0x00C);

# 434
extern volatile unsigned char PORTC __at(0x00E);

asm("PORTC equ 0Eh");


typedef union {
struct {
unsigned RC0 :1;
unsigned RC1 :1;
unsigned RC2 :1;
unsigned RC3 :1;
unsigned RC4 :1;
unsigned RC5 :1;
};
} PORTCbits_t;
extern volatile PORTCbits_t PORTCbits __at(0x00E);

# 484
extern volatile unsigned char PIR0 __at(0x010);

asm("PIR0 equ 010h");


typedef union {
struct {
unsigned INTF :1;
unsigned :3;
unsigned IOCIF :1;
unsigned TMR0IF :1;
};
} PIR0bits_t;
extern volatile PIR0bits_t PIR0bits __at(0x010);

# 517
extern volatile unsigned char PIR1 __at(0x011);

asm("PIR1 equ 011h");


typedef union {
struct {
unsigned TMR1IF :1;
unsigned TMR2IF :1;
unsigned BCL1IF :1;
unsigned SSP1IF :1;
unsigned TXIF :1;
unsigned RCIF :1;
unsigned ADIF :1;
unsigned TMR1GIF :1;
};
} PIR1bits_t;
extern volatile PIR1bits_t PIR1bits __at(0x011);

# 579
extern volatile unsigned char PIR2 __at(0x012);

asm("PIR2 equ 012h");


typedef union {
struct {
unsigned NCO1IF :1;
unsigned TMR4IF :1;
unsigned BCL2IF :1;
unsigned SSP2IF :1;
unsigned NVMIF :1;
unsigned C1IF :1;
unsigned C2IF :1;
unsigned TMR6IF :1;
};
} PIR2bits_t;
extern volatile PIR2bits_t PIR2bits __at(0x012);

# 641
extern volatile unsigned char PIR3 __at(0x013);

asm("PIR3 equ 013h");


typedef union {
struct {
unsigned CLC1IF :1;
unsigned CLC2IF :1;
unsigned CLC3IF :1;
unsigned CLC4IF :1;
unsigned TMR3IF :1;
unsigned TMR3GIF :1;
unsigned CSWIF :1;
unsigned OSFIF :1;
};
} PIR3bits_t;
extern volatile PIR3bits_t PIR3bits __at(0x013);

# 703
extern volatile unsigned char PIR4 __at(0x014);

asm("PIR4 equ 014h");


typedef union {
struct {
unsigned CCP1IF :1;
unsigned CCP2IF :1;
unsigned CCP3IF :1;
unsigned CCP4IF :1;
unsigned TMR5IF :1;
unsigned TMR5GIF :1;
unsigned CWG1IF :1;
unsigned CWG2IF :1;
};
} PIR4bits_t;
extern volatile PIR4bits_t PIR4bits __at(0x014);

# 765
extern volatile unsigned char TMR0L __at(0x015);

asm("TMR0L equ 015h");


extern volatile unsigned char TMR0 __at(0x015);

asm("TMR0 equ 015h");


typedef union {
struct {
unsigned TMR0L :8;
};
struct {
unsigned TMR00 :1;
unsigned TMR01 :1;
unsigned TMR02 :1;
unsigned TMR03 :1;
unsigned TMR04 :1;
unsigned TMR05 :1;
unsigned TMR06 :1;
unsigned TMR07 :1;
};
} TMR0Lbits_t;
extern volatile TMR0Lbits_t TMR0Lbits __at(0x015);

# 838
typedef union {
struct {
unsigned TMR0L :8;
};
struct {
unsigned TMR00 :1;
unsigned TMR01 :1;
unsigned TMR02 :1;
unsigned TMR03 :1;
unsigned TMR04 :1;
unsigned TMR05 :1;
unsigned TMR06 :1;
unsigned TMR07 :1;
};
} TMR0bits_t;
extern volatile TMR0bits_t TMR0bits __at(0x015);

# 903
extern volatile unsigned char TMR0H __at(0x016);

asm("TMR0H equ 016h");


extern volatile unsigned char PR0 __at(0x016);

asm("PR0 equ 016h");


typedef union {
struct {
unsigned TMR0H :8;
};
struct {
unsigned TMR08 :1;
unsigned TMR09 :1;
unsigned TMR010 :1;
unsigned TMR011 :1;
unsigned TMR012 :1;
unsigned TMR013 :1;
unsigned TMR014 :1;
unsigned TMR015 :1;
};
struct {
unsigned PR0 :8;
};
} TMR0Hbits_t;
extern volatile TMR0Hbits_t TMR0Hbits __at(0x016);

# 984
typedef union {
struct {
unsigned TMR0H :8;
};
struct {
unsigned TMR08 :1;
unsigned TMR09 :1;
unsigned TMR010 :1;
unsigned TMR011 :1;
unsigned TMR012 :1;
unsigned TMR013 :1;
unsigned TMR014 :1;
unsigned TMR015 :1;
};
struct {
unsigned PR0 :8;
};
} PR0bits_t;
extern volatile PR0bits_t PR0bits __at(0x016);

# 1057
extern volatile unsigned char T0CON0 __at(0x017);

asm("T0CON0 equ 017h");


typedef union {
struct {
unsigned T0OUTPS :4;
unsigned T016BIT :1;
unsigned T0OUT :1;
unsigned :1;
unsigned T0EN :1;
};
struct {
unsigned T0OUTPS0 :1;
unsigned T0OUTPS1 :1;
unsigned T0OUTPS2 :1;
unsigned T0OUTPS3 :1;
};
} T0CON0bits_t;
extern volatile T0CON0bits_t T0CON0bits __at(0x017);

# 1122
extern volatile unsigned char T0CON1 __at(0x018);

asm("T0CON1 equ 018h");


typedef union {
struct {
unsigned T0CKPS :4;
unsigned T0ASYNC :1;
unsigned T0CS :3;
};
struct {
unsigned T0CKPS0 :1;
unsigned T0CKPS1 :1;
unsigned T0CKPS2 :1;
unsigned T0CKPS3 :1;
unsigned :1;
unsigned T0CS0 :1;
unsigned T0CS1 :1;
unsigned T0CS2 :1;
};
} T0CON1bits_t;
extern volatile T0CON1bits_t T0CON1bits __at(0x018);

# 1199
extern volatile unsigned short TMR1 __at(0x019);

asm("TMR1 equ 019h");




extern volatile unsigned char TMR1L __at(0x019);

asm("TMR1L equ 019h");


typedef union {
struct {
unsigned TMR1L :8;
};
} TMR1Lbits_t;
extern volatile TMR1Lbits_t TMR1Lbits __at(0x019);

# 1226
extern volatile unsigned char TMR1H __at(0x01A);

asm("TMR1H equ 01Ah");


typedef union {
struct {
unsigned TMR1H :8;
};
} TMR1Hbits_t;
extern volatile TMR1Hbits_t TMR1Hbits __at(0x01A);

# 1246
extern volatile unsigned char T1CON __at(0x01B);

asm("T1CON equ 01Bh");


typedef union {
struct {
unsigned TMR1ON :1;
unsigned :1;
unsigned T1SYNC :1;
unsigned T1SOSC :1;
unsigned T1CKPS :2;
unsigned TMR1CS :2;
};
struct {
unsigned :4;
unsigned T1CKPS0 :1;
unsigned T1CKPS1 :1;
unsigned TMR1CS0 :1;
unsigned TMR1CS1 :1;
};
} T1CONbits_t;
extern volatile T1CONbits_t T1CONbits __at(0x01B);

# 1318
extern volatile unsigned char T1GCON __at(0x01C);

asm("T1GCON equ 01Ch");


typedef union {
struct {
unsigned T1GSS :2;
unsigned T1GVAL :1;
unsigned T1GGO_nDONE :1;
unsigned T1GSPM :1;
unsigned T1GTM :1;
unsigned T1GPOL :1;
unsigned TMR1GE :1;
};
struct {
unsigned T1GSS0 :1;
unsigned T1GSS1 :1;
};
} T1GCONbits_t;
extern volatile T1GCONbits_t T1GCONbits __at(0x01C);

# 1388
extern volatile unsigned char TMR2 __at(0x01D);

asm("TMR2 equ 01Dh");


typedef union {
struct {
unsigned TMR2 :8;
};
} TMR2bits_t;
extern volatile TMR2bits_t TMR2bits __at(0x01D);

# 1408
extern volatile unsigned char PR2 __at(0x01E);

asm("PR2 equ 01Eh");


typedef union {
struct {
unsigned PR2 :8;
};
} PR2bits_t;
extern volatile PR2bits_t PR2bits __at(0x01E);

# 1428
extern volatile unsigned char T2CON __at(0x01F);

asm("T2CON equ 01Fh");


typedef union {
struct {
unsigned T2CKPS :2;
unsigned TMR2ON :1;
unsigned T2OUTPS :4;
};
struct {
unsigned T2CKPS0 :1;
unsigned T2CKPS1 :1;
unsigned :1;
unsigned T2OUTPS0 :1;
unsigned T2OUTPS1 :1;
unsigned T2OUTPS2 :1;
unsigned T2OUTPS3 :1;
};
} T2CONbits_t;
extern volatile T2CONbits_t T2CONbits __at(0x01F);

# 1499
extern volatile unsigned char TRISA __at(0x08C);

asm("TRISA equ 08Ch");


typedef union {
struct {
unsigned TRISA0 :1;
unsigned TRISA1 :1;
unsigned TRISA2 :1;
unsigned :1;
unsigned TRISA4 :1;
unsigned TRISA5 :1;
};
} TRISAbits_t;
extern volatile TRISAbits_t TRISAbits __at(0x08C);

# 1544
extern volatile unsigned char TRISC __at(0x08E);

asm("TRISC equ 08Eh");


typedef union {
struct {
unsigned TRISC0 :1;
unsigned TRISC1 :1;
unsigned TRISC2 :1;
unsigned TRISC3 :1;
unsigned TRISC4 :1;
unsigned TRISC5 :1;
};
} TRISCbits_t;
extern volatile TRISCbits_t TRISCbits __at(0x08E);

# 1594
extern volatile unsigned char PIE0 __at(0x090);

asm("PIE0 equ 090h");


typedef union {
struct {
unsigned INTE :1;
unsigned :3;
unsigned IOCIE :1;
unsigned TMR0IE :1;
};
} PIE0bits_t;
extern volatile PIE0bits_t PIE0bits __at(0x090);

# 1627
extern volatile unsigned char PIE1 __at(0x091);

asm("PIE1 equ 091h");


typedef union {
struct {
unsigned TMR1IE :1;
unsigned TMR2IE :1;
unsigned BCL1IE :1;
unsigned SSP1IE :1;
unsigned TXIE :1;
unsigned RCIE :1;
unsigned ADIE :1;
unsigned TMR1GIE :1;
};
} PIE1bits_t;
extern volatile PIE1bits_t PIE1bits __at(0x091);

# 1689
extern volatile unsigned char PIE2 __at(0x092);

asm("PIE2 equ 092h");


typedef union {
struct {
unsigned NCO1IE :1;
unsigned TMR4IE :1;
unsigned BCL2IE :1;
unsigned SSP2IE :1;
unsigned NVMIE :1;
unsigned C1IE :1;
unsigned C2IE :1;
unsigned TMR6IE :1;
};
} PIE2bits_t;
extern volatile PIE2bits_t PIE2bits __at(0x092);

# 1751
extern volatile unsigned char PIE3 __at(0x093);

asm("PIE3 equ 093h");


typedef union {
struct {
unsigned CLC1IE :1;
unsigned CLC2IE :1;
unsigned CLC3IE :1;
unsigned CLC4IE :1;
unsigned TMR3IE :1;
unsigned TMR3GIE :1;
unsigned CSWIE :1;
unsigned OSFIE :1;
};
} PIE3bits_t;
extern volatile PIE3bits_t PIE3bits __at(0x093);

# 1813
extern volatile unsigned char PIE4 __at(0x094);

asm("PIE4 equ 094h");


typedef union {
struct {
unsigned CCP1IE :1;
unsigned CCP2IE :1;
unsigned CCP3IE :1;
unsigned CCP4IE :1;
unsigned TMR5IE :1;
unsigned TMR5GIE :1;
unsigned CWG1IE :1;
unsigned CWG2IE :1;
};
} PIE4bits_t;
extern volatile PIE4bits_t PIE4bits __at(0x094);

# 1875
extern volatile unsigned char WDTCON __at(0x097);

asm("WDTCON equ 097h");


typedef union {
struct {
unsigned SWDTEN :1;
unsigned WDTPS :5;
};
struct {
unsigned :1;
unsigned WDTPS0 :1;
unsigned WDTPS1 :1;
unsigned WDTPS2 :1;
unsigned WDTPS3 :1;
unsigned WDTPS4 :1;
};
} WDTCONbits_t;
extern volatile WDTCONbits_t WDTCONbits __at(0x097);

# 1934
extern volatile unsigned short ADRES __at(0x09B);

asm("ADRES equ 09Bh");




extern volatile unsigned char ADRESL __at(0x09B);

asm("ADRESL equ 09Bh");


typedef union {
struct {
unsigned ADRESL :8;
};
} ADRESLbits_t;
extern volatile ADRESLbits_t ADRESLbits __at(0x09B);

# 1961
extern volatile unsigned char ADRESH __at(0x09C);

asm("ADRESH equ 09Ch");


typedef union {
struct {
unsigned ADRESH :8;
};
} ADRESHbits_t;
extern volatile ADRESHbits_t ADRESHbits __at(0x09C);

# 1981
extern volatile unsigned char ADCON0 __at(0x09D);

asm("ADCON0 equ 09Dh");


typedef union {
struct {
unsigned ADON :1;
unsigned GO_nDONE :1;
unsigned CHS :6;
};
struct {
unsigned :1;
unsigned ADGO :1;
unsigned CHS0 :1;
unsigned CHS1 :1;
unsigned CHS2 :1;
unsigned CHS3 :1;
unsigned CHS4 :1;
unsigned CHS5 :1;
};
struct {
unsigned :1;
unsigned GO :1;
};
} ADCON0bits_t;
extern volatile ADCON0bits_t ADCON0bits __at(0x09D);

# 2067
extern volatile unsigned char ADCON1 __at(0x09E);

asm("ADCON1 equ 09Eh");


typedef union {
struct {
unsigned ADPREF :2;
unsigned ADNREF :1;
unsigned :1;
unsigned ADCS :3;
unsigned ADFM :1;
};
struct {
unsigned ADPREF0 :1;
unsigned ADPREF1 :1;
unsigned :2;
unsigned ADCS0 :1;
unsigned ADCS1 :1;
unsigned ADCS2 :1;
};
} ADCON1bits_t;
extern volatile ADCON1bits_t ADCON1bits __at(0x09E);

# 2139
extern volatile unsigned char ADACT __at(0x09F);

asm("ADACT equ 09Fh");


typedef union {
struct {
unsigned ADACT :5;
};
struct {
unsigned ADACT0 :1;
unsigned ADACT1 :1;
unsigned ADACT2 :1;
unsigned ADACT3 :1;
unsigned ADACT4 :1;
};
} ADACTbits_t;
extern volatile ADACTbits_t ADACTbits __at(0x09F);

# 2191
extern volatile unsigned char LATA __at(0x10C);

asm("LATA equ 010Ch");


typedef union {
struct {
unsigned LATA0 :1;
unsigned LATA1 :1;
unsigned LATA2 :1;
unsigned :1;
unsigned LATA4 :1;
unsigned LATA5 :1;
};
} LATAbits_t;
extern volatile LATAbits_t LATAbits __at(0x10C);

# 2236
extern volatile unsigned char LATC __at(0x10E);

asm("LATC equ 010Eh");


typedef union {
struct {
unsigned LATC0 :1;
unsigned LATC1 :1;
unsigned LATC2 :1;
unsigned LATC3 :1;
unsigned LATC4 :1;
unsigned LATC5 :1;
};
} LATCbits_t;
extern volatile LATCbits_t LATCbits __at(0x10E);

# 2286
extern volatile unsigned char CM1CON0 __at(0x111);

asm("CM1CON0 equ 0111h");


typedef union {
struct {
unsigned C1SYNC :1;
unsigned C1HYS :1;
unsigned C1SP :1;
unsigned :1;
unsigned C1POL :1;
unsigned :1;
unsigned C1OUT :1;
unsigned C1ON :1;
};
} CM1CON0bits_t;
extern volatile CM1CON0bits_t CM1CON0bits __at(0x111);

# 2338
extern volatile unsigned char CM1CON1 __at(0x112);

asm("CM1CON1 equ 0112h");


typedef union {
struct {
unsigned C1NCH :3;
unsigned C1PCH :3;
unsigned C1INTN :1;
unsigned C1INTP :1;
};
struct {
unsigned C1NCH0 :1;
unsigned C1NCH1 :1;
unsigned C1NCH2 :1;
unsigned C1PCH0 :1;
unsigned C1PCH1 :1;
unsigned C1PCH2 :1;
};
} CM1CON1bits_t;
extern volatile CM1CON1bits_t CM1CON1bits __at(0x112);

# 2414
extern volatile unsigned char CM2CON0 __at(0x113);

asm("CM2CON0 equ 0113h");


typedef union {
struct {
unsigned C2SYNC :1;
unsigned C2HYS :1;
unsigned C2SP :1;
unsigned :1;
unsigned C2POL :1;
unsigned :1;
unsigned C2OUT :1;
unsigned C2ON :1;
};
} CM2CON0bits_t;
extern volatile CM2CON0bits_t CM2CON0bits __at(0x113);

# 2466
extern volatile unsigned char CM2CON1 __at(0x114);

asm("CM2CON1 equ 0114h");


typedef union {
struct {
unsigned C2NCH :3;
unsigned C2PCH :3;
unsigned C2INTN :1;
unsigned C2INTP :1;
};
struct {
unsigned C2NCH0 :1;
unsigned C2NCH1 :1;
unsigned C2NCH2 :1;
unsigned C2PCH0 :1;
unsigned C2PCH1 :1;
unsigned C2PCH2 :1;
};
} CM2CON1bits_t;
extern volatile CM2CON1bits_t CM2CON1bits __at(0x114);

# 2542
extern volatile unsigned char CMOUT __at(0x115);

asm("CMOUT equ 0115h");


typedef union {
struct {
unsigned MC1OUT :1;
unsigned MC2OUT :1;
};
} CMOUTbits_t;
extern volatile CMOUTbits_t CMOUTbits __at(0x115);

# 2568
extern volatile unsigned char BORCON __at(0x116);

asm("BORCON equ 0116h");


typedef union {
struct {
unsigned BORRDY :1;
unsigned :6;
unsigned SBOREN :1;
};
} BORCONbits_t;
extern volatile BORCONbits_t BORCONbits __at(0x116);

# 2595
extern volatile unsigned char FVRCON __at(0x117);

asm("FVRCON equ 0117h");


typedef union {
struct {
unsigned ADFVR :2;
unsigned CDAFVR :2;
unsigned TSRNG :1;
unsigned TSEN :1;
unsigned FVRRDY :1;
unsigned FVREN :1;
};
struct {
unsigned ADFVR0 :1;
unsigned ADFVR1 :1;
unsigned CDAFVR0 :1;
unsigned CDAFVR1 :1;
};
} FVRCONbits_t;
extern volatile FVRCONbits_t FVRCONbits __at(0x117);

# 2671
extern volatile unsigned char DACCON0 __at(0x118);

asm("DACCON0 equ 0118h");


typedef union {
struct {
unsigned DAC1NSS :1;
unsigned :1;
unsigned DAC1PSS :2;
unsigned :1;
unsigned DAC1OE :1;
unsigned :1;
unsigned DAC1EN :1;
};
struct {
unsigned :2;
unsigned DAC1PSS0 :1;
unsigned DAC1PSS1 :1;
};
} DACCON0bits_t;
extern volatile DACCON0bits_t DACCON0bits __at(0x118);

# 2727
extern volatile unsigned char DACCON1 __at(0x119);

asm("DACCON1 equ 0119h");


typedef union {
struct {
unsigned DAC1R :5;
};
struct {
unsigned DAC1R0 :1;
unsigned DAC1R1 :1;
unsigned DAC1R2 :1;
unsigned DAC1R3 :1;
unsigned DAC1R4 :1;
};
} DACCON1bits_t;
extern volatile DACCON1bits_t DACCON1bits __at(0x119);

# 2779
extern volatile unsigned char ANSELA __at(0x18C);

asm("ANSELA equ 018Ch");


typedef union {
struct {
unsigned ANSA0 :1;
unsigned ANSA1 :1;
unsigned ANSA2 :1;
unsigned :1;
unsigned ANSA4 :1;
unsigned ANSA5 :1;
};
} ANSELAbits_t;
extern volatile ANSELAbits_t ANSELAbits __at(0x18C);

# 2824
extern volatile unsigned char ANSELC __at(0x18E);

asm("ANSELC equ 018Eh");


typedef union {
struct {
unsigned ANSC0 :1;
unsigned ANSC1 :1;
unsigned ANSC2 :1;
unsigned ANSC3 :1;
unsigned ANSC4 :1;
unsigned ANSC5 :1;
};
} ANSELCbits_t;
extern volatile ANSELCbits_t ANSELCbits __at(0x18E);

# 2874
extern volatile unsigned char RC1REG __at(0x199);

asm("RC1REG equ 0199h");


extern volatile unsigned char RCREG __at(0x199);

asm("RCREG equ 0199h");

extern volatile unsigned char RCREG1 __at(0x199);

asm("RCREG1 equ 0199h");


typedef union {
struct {
unsigned RC1REG :8;
};
} RC1REGbits_t;
extern volatile RC1REGbits_t RC1REGbits __at(0x199);

# 2901
typedef union {
struct {
unsigned RC1REG :8;
};
} RCREGbits_t;
extern volatile RCREGbits_t RCREGbits __at(0x199);

# 2913
typedef union {
struct {
unsigned RC1REG :8;
};
} RCREG1bits_t;
extern volatile RCREG1bits_t RCREG1bits __at(0x199);

# 2928
extern volatile unsigned char TX1REG __at(0x19A);

asm("TX1REG equ 019Ah");


extern volatile unsigned char TXREG1 __at(0x19A);

asm("TXREG1 equ 019Ah");

extern volatile unsigned char TXREG __at(0x19A);

asm("TXREG equ 019Ah");


typedef union {
struct {
unsigned TX1REG :8;
};
} TX1REGbits_t;
extern volatile TX1REGbits_t TX1REGbits __at(0x19A);

# 2955
typedef union {
struct {
unsigned TX1REG :8;
};
} TXREG1bits_t;
extern volatile TXREG1bits_t TXREG1bits __at(0x19A);

# 2967
typedef union {
struct {
unsigned TX1REG :8;
};
} TXREGbits_t;
extern volatile TXREGbits_t TXREGbits __at(0x19A);

# 2982
extern volatile unsigned short SP1BRG __at(0x19B);

asm("SP1BRG equ 019Bh");




extern volatile unsigned char SP1BRGL __at(0x19B);

asm("SP1BRGL equ 019Bh");


extern volatile unsigned char SPBRG __at(0x19B);

asm("SPBRG equ 019Bh");

extern volatile unsigned char SPBRG1 __at(0x19B);

asm("SPBRG1 equ 019Bh");

extern volatile unsigned char SPBRGL __at(0x19B);

asm("SPBRGL equ 019Bh");


typedef union {
struct {
unsigned SP1BRGL :8;
};
} SP1BRGLbits_t;
extern volatile SP1BRGLbits_t SP1BRGLbits __at(0x19B);

# 3020
typedef union {
struct {
unsigned SP1BRGL :8;
};
} SPBRGbits_t;
extern volatile SPBRGbits_t SPBRGbits __at(0x19B);

# 3032
typedef union {
struct {
unsigned SP1BRGL :8;
};
} SPBRG1bits_t;
extern volatile SPBRG1bits_t SPBRG1bits __at(0x19B);

# 3044
typedef union {
struct {
unsigned SP1BRGL :8;
};
} SPBRGLbits_t;
extern volatile SPBRGLbits_t SPBRGLbits __at(0x19B);

# 3059
extern volatile unsigned char SP1BRGH __at(0x19C);

asm("SP1BRGH equ 019Ch");


extern volatile unsigned char SPBRGH __at(0x19C);

asm("SPBRGH equ 019Ch");

extern volatile unsigned char SPBRGH1 __at(0x19C);

asm("SPBRGH1 equ 019Ch");


typedef union {
struct {
unsigned SP1BRGH :8;
};
} SP1BRGHbits_t;
extern volatile SP1BRGHbits_t SP1BRGHbits __at(0x19C);

# 3086
typedef union {
struct {
unsigned SP1BRGH :8;
};
} SPBRGHbits_t;
extern volatile SPBRGHbits_t SPBRGHbits __at(0x19C);

# 3098
typedef union {
struct {
unsigned SP1BRGH :8;
};
} SPBRGH1bits_t;
extern volatile SPBRGH1bits_t SPBRGH1bits __at(0x19C);

# 3113
extern volatile unsigned char RC1STA __at(0x19D);

asm("RC1STA equ 019Dh");


extern volatile unsigned char RCSTA1 __at(0x19D);

asm("RCSTA1 equ 019Dh");

extern volatile unsigned char RCSTA __at(0x19D);

asm("RCSTA equ 019Dh");


typedef union {
struct {
unsigned RX9D :1;
unsigned OERR :1;
unsigned FERR :1;
unsigned ADDEN :1;
unsigned CREN :1;
unsigned SREN :1;
unsigned RX9 :1;
unsigned SPEN :1;
};
} RC1STAbits_t;
extern volatile RC1STAbits_t RC1STAbits __at(0x19D);

# 3182
typedef union {
struct {
unsigned RX9D :1;
unsigned OERR :1;
unsigned FERR :1;
unsigned ADDEN :1;
unsigned CREN :1;
unsigned SREN :1;
unsigned RX9 :1;
unsigned SPEN :1;
};
} RCSTA1bits_t;
extern volatile RCSTA1bits_t RCSTA1bits __at(0x19D);

# 3236
typedef union {
struct {
unsigned RX9D :1;
unsigned OERR :1;
unsigned FERR :1;
unsigned ADDEN :1;
unsigned CREN :1;
unsigned SREN :1;
unsigned RX9 :1;
unsigned SPEN :1;
};
} RCSTAbits_t;
extern volatile RCSTAbits_t RCSTAbits __at(0x19D);

# 3293
extern volatile unsigned char TX1STA __at(0x19E);

asm("TX1STA equ 019Eh");


extern volatile unsigned char TXSTA1 __at(0x19E);

asm("TXSTA1 equ 019Eh");

extern volatile unsigned char TXSTA __at(0x19E);

asm("TXSTA equ 019Eh");


typedef union {
struct {
unsigned TX9D :1;
unsigned TRMT :1;
unsigned BRGH :1;
unsigned SENDB :1;
unsigned SYNC :1;
unsigned TXEN :1;
unsigned TX9 :1;
unsigned CSRC :1;
};
} TX1STAbits_t;
extern volatile TX1STAbits_t TX1STAbits __at(0x19E);

# 3362
typedef union {
struct {
unsigned TX9D :1;
unsigned TRMT :1;
unsigned BRGH :1;
unsigned SENDB :1;
unsigned SYNC :1;
unsigned TXEN :1;
unsigned TX9 :1;
unsigned CSRC :1;
};
} TXSTA1bits_t;
extern volatile TXSTA1bits_t TXSTA1bits __at(0x19E);

# 3416
typedef union {
struct {
unsigned TX9D :1;
unsigned TRMT :1;
unsigned BRGH :1;
unsigned SENDB :1;
unsigned SYNC :1;
unsigned TXEN :1;
unsigned TX9 :1;
unsigned CSRC :1;
};
} TXSTAbits_t;
extern volatile TXSTAbits_t TXSTAbits __at(0x19E);

# 3473
extern volatile unsigned char BAUD1CON __at(0x19F);

asm("BAUD1CON equ 019Fh");


extern volatile unsigned char BAUDCON1 __at(0x19F);

asm("BAUDCON1 equ 019Fh");

extern volatile unsigned char BAUDCTL1 __at(0x19F);

asm("BAUDCTL1 equ 019Fh");

extern volatile unsigned char BAUDCON __at(0x19F);

asm("BAUDCON equ 019Fh");

extern volatile unsigned char BAUDCTL __at(0x19F);

asm("BAUDCTL equ 019Fh");


typedef union {
struct {
unsigned ABDEN :1;
unsigned WUE :1;
unsigned :1;
unsigned BRG16 :1;
unsigned SCKP :1;
unsigned :1;
unsigned RCIDL :1;
unsigned ABDOVF :1;
};
} BAUD1CONbits_t;
extern volatile BAUD1CONbits_t BAUD1CONbits __at(0x19F);

# 3540
typedef union {
struct {
unsigned ABDEN :1;
unsigned WUE :1;
unsigned :1;
unsigned BRG16 :1;
unsigned SCKP :1;
unsigned :1;
unsigned RCIDL :1;
unsigned ABDOVF :1;
};
} BAUDCON1bits_t;
extern volatile BAUDCON1bits_t BAUDCON1bits __at(0x19F);

# 3584
typedef union {
struct {
unsigned ABDEN :1;
unsigned WUE :1;
unsigned :1;
unsigned BRG16 :1;
unsigned SCKP :1;
unsigned :1;
unsigned RCIDL :1;
unsigned ABDOVF :1;
};
} BAUDCTL1bits_t;
extern volatile BAUDCTL1bits_t BAUDCTL1bits __at(0x19F);

# 3628
typedef union {
struct {
unsigned ABDEN :1;
unsigned WUE :1;
unsigned :1;
unsigned BRG16 :1;
unsigned SCKP :1;
unsigned :1;
unsigned RCIDL :1;
unsigned ABDOVF :1;
};
} BAUDCONbits_t;
extern volatile BAUDCONbits_t BAUDCONbits __at(0x19F);

# 3672
typedef union {
struct {
unsigned ABDEN :1;
unsigned WUE :1;
unsigned :1;
unsigned BRG16 :1;
unsigned SCKP :1;
unsigned :1;
unsigned RCIDL :1;
unsigned ABDOVF :1;
};
} BAUDCTLbits_t;
extern volatile BAUDCTLbits_t BAUDCTLbits __at(0x19F);

# 3719
extern volatile unsigned char WPUA __at(0x20C);

asm("WPUA equ 020Ch");


typedef union {
struct {
unsigned WPUA0 :1;
unsigned WPUA1 :1;
unsigned WPUA2 :1;
unsigned WPUA3 :1;
unsigned WPUA4 :1;
unsigned WPUA5 :1;
};
} WPUAbits_t;
extern volatile WPUAbits_t WPUAbits __at(0x20C);

# 3769
extern volatile unsigned char WPUC __at(0x20E);

asm("WPUC equ 020Eh");


typedef union {
struct {
unsigned WPUC0 :1;
unsigned WPUC1 :1;
unsigned WPUC2 :1;
unsigned WPUC3 :1;
unsigned WPUC4 :1;
unsigned WPUC5 :1;
};
} WPUCbits_t;
extern volatile WPUCbits_t WPUCbits __at(0x20E);

# 3819
extern volatile unsigned char SSP1BUF __at(0x211);

asm("SSP1BUF equ 0211h");


extern volatile unsigned char SSPBUF __at(0x211);

asm("SSPBUF equ 0211h");


typedef union {
struct {
unsigned SSP1BUF0 :1;
unsigned SSP1BUF1 :1;
unsigned SSP1BUF2 :1;
unsigned SSP1BUF3 :1;
unsigned SSP1BUF4 :1;
unsigned SSP1BUF5 :1;
unsigned SSP1BUF6 :1;
unsigned SSP1BUF7 :1;
};
struct {
unsigned BUF :8;
};
struct {
unsigned BUF0 :1;
unsigned BUF1 :1;
unsigned BUF2 :1;
unsigned BUF3 :1;
unsigned BUF4 :1;
unsigned BUF5 :1;
unsigned BUF6 :1;
unsigned BUF7 :1;
};
struct {
unsigned SSP1BUF :8;
};
} SSP1BUFbits_t;
extern volatile SSP1BUFbits_t SSP1BUFbits __at(0x211);

# 3950
typedef union {
struct {
unsigned SSP1BUF0 :1;
unsigned SSP1BUF1 :1;
unsigned SSP1BUF2 :1;
unsigned SSP1BUF3 :1;
unsigned SSP1BUF4 :1;
unsigned SSP1BUF5 :1;
unsigned SSP1BUF6 :1;
unsigned SSP1BUF7 :1;
};
struct {
unsigned BUF :8;
};
struct {
unsigned BUF0 :1;
unsigned BUF1 :1;
unsigned BUF2 :1;
unsigned BUF3 :1;
unsigned BUF4 :1;
unsigned BUF5 :1;
unsigned BUF6 :1;
unsigned BUF7 :1;
};
struct {
unsigned SSP1BUF :8;
};
} SSPBUFbits_t;
extern volatile SSPBUFbits_t SSPBUFbits __at(0x211);

# 4073
extern volatile unsigned char SSP1ADD __at(0x212);

asm("SSP1ADD equ 0212h");


extern volatile unsigned char SSPADD __at(0x212);

asm("SSPADD equ 0212h");


typedef union {
struct {
unsigned SSP1ADD0 :1;
unsigned SSP1ADD1 :1;
unsigned SSP1ADD2 :1;
unsigned SSP1ADD3 :1;
unsigned SSP1ADD4 :1;
unsigned SSP1ADD5 :1;
unsigned SSP1ADD6 :1;
unsigned SSP1ADD7 :1;
};
struct {
unsigned ADD :8;
};
struct {
unsigned ADD0 :1;
unsigned ADD1 :1;
unsigned ADD2 :1;
unsigned ADD3 :1;
unsigned ADD4 :1;
unsigned ADD5 :1;
unsigned ADD6 :1;
unsigned ADD7 :1;
};
struct {
unsigned SSP1ADD :8;
};
} SSP1ADDbits_t;
extern volatile SSP1ADDbits_t SSP1ADDbits __at(0x212);

# 4204
typedef union {
struct {
unsigned SSP1ADD0 :1;
unsigned SSP1ADD1 :1;
unsigned SSP1ADD2 :1;
unsigned SSP1ADD3 :1;
unsigned SSP1ADD4 :1;
unsigned SSP1ADD5 :1;
unsigned SSP1ADD6 :1;
unsigned SSP1ADD7 :1;
};
struct {
unsigned ADD :8;
};
struct {
unsigned ADD0 :1;
unsigned ADD1 :1;
unsigned ADD2 :1;
unsigned ADD3 :1;
unsigned ADD4 :1;
unsigned ADD5 :1;
unsigned ADD6 :1;
unsigned ADD7 :1;
};
struct {
unsigned SSP1ADD :8;
};
} SSPADDbits_t;
extern volatile SSPADDbits_t SSPADDbits __at(0x212);

# 4327
extern volatile unsigned char SSP1MSK __at(0x213);

asm("SSP1MSK equ 0213h");


extern volatile unsigned char SSPMSK __at(0x213);

asm("SSPMSK equ 0213h");


typedef union {
struct {
unsigned SSP1MSK0 :1;
unsigned SSP1MSK1 :1;
unsigned SSP1MSK2 :1;
unsigned SSP1MSK3 :1;
unsigned SSP1MSK4 :1;
unsigned SSP1MSK5 :1;
unsigned SSP1MSK6 :1;
unsigned SSP1MSK7 :1;
};
struct {
unsigned MSK :8;
};
struct {
unsigned MSK0 :1;
unsigned MSK1 :1;
unsigned MSK2 :1;
unsigned MSK3 :1;
unsigned MSK4 :1;
unsigned MSK5 :1;
unsigned MSK6 :1;
unsigned MSK7 :1;
};
struct {
unsigned SSP1MSK :8;
};
} SSP1MSKbits_t;
extern volatile SSP1MSKbits_t SSP1MSKbits __at(0x213);

# 4458
typedef union {
struct {
unsigned SSP1MSK0 :1;
unsigned SSP1MSK1 :1;
unsigned SSP1MSK2 :1;
unsigned SSP1MSK3 :1;
unsigned SSP1MSK4 :1;
unsigned SSP1MSK5 :1;
unsigned SSP1MSK6 :1;
unsigned SSP1MSK7 :1;
};
struct {
unsigned MSK :8;
};
struct {
unsigned MSK0 :1;
unsigned MSK1 :1;
unsigned MSK2 :1;
unsigned MSK3 :1;
unsigned MSK4 :1;
unsigned MSK5 :1;
unsigned MSK6 :1;
unsigned MSK7 :1;
};
struct {
unsigned SSP1MSK :8;
};
} SSPMSKbits_t;
extern volatile SSPMSKbits_t SSPMSKbits __at(0x213);

# 4581
extern volatile unsigned char SSP1STAT __at(0x214);

asm("SSP1STAT equ 0214h");


extern volatile unsigned char SSPSTAT __at(0x214);

asm("SSPSTAT equ 0214h");


typedef union {
struct {
unsigned BF :1;
unsigned UA :1;
unsigned R_nW :1;
unsigned S :1;
unsigned P :1;
unsigned D_nA :1;
unsigned CKE :1;
unsigned SMP :1;
};
} SSP1STATbits_t;
extern volatile SSP1STATbits_t SSP1STATbits __at(0x214);

# 4646
typedef union {
struct {
unsigned BF :1;
unsigned UA :1;
unsigned R_nW :1;
unsigned S :1;
unsigned P :1;
unsigned D_nA :1;
unsigned CKE :1;
unsigned SMP :1;
};
} SSPSTATbits_t;
extern volatile SSPSTATbits_t SSPSTATbits __at(0x214);

# 4703
extern volatile unsigned char SSP1CON1 __at(0x215);

asm("SSP1CON1 equ 0215h");


extern volatile unsigned char SSPCON __at(0x215);

asm("SSPCON equ 0215h");

extern volatile unsigned char SSPCON1 __at(0x215);

asm("SSPCON1 equ 0215h");

extern volatile unsigned char SSP1CON __at(0x215);

asm("SSP1CON equ 0215h");


typedef union {
struct {
unsigned SSPM :4;
unsigned CKP :1;
unsigned SSPEN :1;
unsigned SSPOV :1;
unsigned WCOL :1;
};
struct {
unsigned SSPM0 :1;
unsigned SSPM1 :1;
unsigned SSPM2 :1;
unsigned SSPM3 :1;
};
} SSP1CON1bits_t;
extern volatile SSP1CON1bits_t SSP1CON1bits __at(0x215);

# 4784
typedef union {
struct {
unsigned SSPM :4;
unsigned CKP :1;
unsigned SSPEN :1;
unsigned SSPOV :1;
unsigned WCOL :1;
};
struct {
unsigned SSPM0 :1;
unsigned SSPM1 :1;
unsigned SSPM2 :1;
unsigned SSPM3 :1;
};
} SSPCONbits_t;
extern volatile SSPCONbits_t SSPCONbits __at(0x215);

# 4846
typedef union {
struct {
unsigned SSPM :4;
unsigned CKP :1;
unsigned SSPEN :1;
unsigned SSPOV :1;
unsigned WCOL :1;
};
struct {
unsigned SSPM0 :1;
unsigned SSPM1 :1;
unsigned SSPM2 :1;
unsigned SSPM3 :1;
};
} SSPCON1bits_t;
extern volatile SSPCON1bits_t SSPCON1bits __at(0x215);

# 4908
typedef union {
struct {
unsigned SSPM :4;
unsigned CKP :1;
unsigned SSPEN :1;
unsigned SSPOV :1;
unsigned WCOL :1;
};
struct {
unsigned SSPM0 :1;
unsigned SSPM1 :1;
unsigned SSPM2 :1;
unsigned SSPM3 :1;
};
} SSP1CONbits_t;
extern volatile SSP1CONbits_t SSP1CONbits __at(0x215);

# 4973
extern volatile unsigned char SSP1CON2 __at(0x216);

asm("SSP1CON2 equ 0216h");


extern volatile unsigned char SSPCON2 __at(0x216);

asm("SSPCON2 equ 0216h");


typedef union {
struct {
unsigned SEN :1;
unsigned RSEN :1;
unsigned PEN :1;
unsigned RCEN :1;
unsigned ACKEN :1;
unsigned ACKDT :1;
unsigned ACKSTAT :1;
unsigned GCEN :1;
};
} SSP1CON2bits_t;
extern volatile SSP1CON2bits_t SSP1CON2bits __at(0x216);

# 5038
typedef union {
struct {
unsigned SEN :1;
unsigned RSEN :1;
unsigned PEN :1;
unsigned RCEN :1;
unsigned ACKEN :1;
unsigned ACKDT :1;
unsigned ACKSTAT :1;
unsigned GCEN :1;
};
} SSPCON2bits_t;
extern volatile SSPCON2bits_t SSPCON2bits __at(0x216);

# 5095
extern volatile unsigned char SSP1CON3 __at(0x217);

asm("SSP1CON3 equ 0217h");


extern volatile unsigned char SSPCON3 __at(0x217);

asm("SSPCON3 equ 0217h");


typedef union {
struct {
unsigned DHEN :1;
unsigned AHEN :1;
unsigned SBCDE :1;
unsigned SDAHT :1;
unsigned BOEN :1;
unsigned SCIE :1;
unsigned PCIE :1;
unsigned ACKTIM :1;
};
} SSP1CON3bits_t;
extern volatile SSP1CON3bits_t SSP1CON3bits __at(0x217);

# 5160
typedef union {
struct {
unsigned DHEN :1;
unsigned AHEN :1;
unsigned SBCDE :1;
unsigned SDAHT :1;
unsigned BOEN :1;
unsigned SCIE :1;
unsigned PCIE :1;
unsigned ACKTIM :1;
};
} SSPCON3bits_t;
extern volatile SSPCON3bits_t SSPCON3bits __at(0x217);

# 5217
extern volatile unsigned char SSP2BUF __at(0x219);

asm("SSP2BUF equ 0219h");


typedef union {
struct {
unsigned SSP2BUF0 :1;
unsigned SSP2BUF1 :1;
unsigned SSP2BUF2 :1;
unsigned SSP2BUF3 :1;
unsigned SSP2BUF4 :1;
unsigned SSP2BUF5 :1;
unsigned SSP2BUF6 :1;
unsigned SSP2BUF7 :1;
};
struct {
unsigned BUF :8;
};
struct {
unsigned BUF0 :1;
unsigned BUF1 :1;
unsigned BUF2 :1;
unsigned BUF3 :1;
unsigned BUF4 :1;
unsigned BUF5 :1;
unsigned BUF6 :1;
unsigned BUF7 :1;
};
struct {
unsigned SSP2BUF :8;
};
} SSP2BUFbits_t;
extern volatile SSP2BUFbits_t SSP2BUFbits __at(0x219);

# 5345
extern volatile unsigned char SSP2ADD __at(0x21A);

asm("SSP2ADD equ 021Ah");


typedef union {
struct {
unsigned SSP2ADD0 :1;
unsigned SSP2ADD1 :1;
unsigned SSP2ADD2 :1;
unsigned SSP2ADD3 :1;
unsigned SSP2ADD4 :1;
unsigned SSP2ADD5 :1;
unsigned SSP2ADD6 :1;
unsigned SSP2ADD7 :1;
};
struct {
unsigned ADD :8;
};
struct {
unsigned ADD0 :1;
unsigned ADD1 :1;
unsigned ADD2 :1;
unsigned ADD3 :1;
unsigned ADD4 :1;
unsigned ADD5 :1;
unsigned ADD6 :1;
unsigned ADD7 :1;
};
struct {
unsigned SSP2ADD :8;
};
} SSP2ADDbits_t;
extern volatile SSP2ADDbits_t SSP2ADDbits __at(0x21A);

# 5473
extern volatile unsigned char SSP2MSK __at(0x21B);

asm("SSP2MSK equ 021Bh");


typedef union {
struct {
unsigned SSP2MSK0 :1;
unsigned SSP2MSK1 :1;
unsigned SSP2MSK2 :1;
unsigned SSP2MSK3 :1;
unsigned SSP2MSK4 :1;
unsigned SSP2MSK5 :1;
unsigned SSP2MSK6 :1;
unsigned SSP2MSK7 :1;
};
struct {
unsigned MSK :8;
};
struct {
unsigned MSK0 :1;
unsigned MSK1 :1;
unsigned MSK2 :1;
unsigned MSK3 :1;
unsigned MSK4 :1;
unsigned MSK5 :1;
unsigned MSK6 :1;
unsigned MSK7 :1;
};
struct {
unsigned SSP2MSK :8;
};
} SSP2MSKbits_t;
extern volatile SSP2MSKbits_t SSP2MSKbits __at(0x21B);

# 5601
extern volatile unsigned char SSP2STAT __at(0x21C);

asm("SSP2STAT equ 021Ch");


typedef union {
struct {
unsigned BF :1;
unsigned UA :1;
unsigned R_nW :1;
unsigned S :1;
unsigned P :1;
unsigned D_nA :1;
unsigned CKE :1;
unsigned SMP :1;
};
} SSP2STATbits_t;
extern volatile SSP2STATbits_t SSP2STATbits __at(0x21C);

# 5663
extern volatile unsigned char SSP2CON1 __at(0x21D);

asm("SSP2CON1 equ 021Dh");


extern volatile unsigned char SSP2CON __at(0x21D);

asm("SSP2CON equ 021Dh");


typedef union {
struct {
unsigned SSPM :4;
unsigned CKP :1;
unsigned SSPEN :1;
unsigned SSPOV :1;
unsigned WCOL :1;
};
struct {
unsigned SSPM0 :1;
unsigned SSPM1 :1;
unsigned SSPM2 :1;
unsigned SSPM3 :1;
};
} SSP2CON1bits_t;
extern volatile SSP2CON1bits_t SSP2CON1bits __at(0x21D);

# 5736
typedef union {
struct {
unsigned SSPM :4;
unsigned CKP :1;
unsigned SSPEN :1;
unsigned SSPOV :1;
unsigned WCOL :1;
};
struct {
unsigned SSPM0 :1;
unsigned SSPM1 :1;
unsigned SSPM2 :1;
unsigned SSPM3 :1;
};
} SSP2CONbits_t;
extern volatile SSP2CONbits_t SSP2CONbits __at(0x21D);

# 5801
extern volatile unsigned char SSP2CON2 __at(0x21E);

asm("SSP2CON2 equ 021Eh");


typedef union {
struct {
unsigned SEN :1;
unsigned RSEN :1;
unsigned PEN :1;
unsigned RCEN :1;
unsigned ACKEN :1;
unsigned ACKDT :1;
unsigned ACKSTAT :1;
unsigned GCEN :1;
};
} SSP2CON2bits_t;
extern volatile SSP2CON2bits_t SSP2CON2bits __at(0x21E);

# 5863
extern volatile unsigned char SSP2CON3 __at(0x21F);

asm("SSP2CON3 equ 021Fh");


typedef union {
struct {
unsigned DHEN :1;
unsigned AHEN :1;
unsigned SBCDE :1;
unsigned SDAHT :1;
unsigned BOEN :1;
unsigned SCIE :1;
unsigned PCIE :1;
unsigned ACKTIM :1;
};
} SSP2CON3bits_t;
extern volatile SSP2CON3bits_t SSP2CON3bits __at(0x21F);

# 5925
extern volatile unsigned char ODCONA __at(0x28C);

asm("ODCONA equ 028Ch");


typedef union {
struct {
unsigned ODCA0 :1;
unsigned ODCA1 :1;
unsigned ODCA2 :1;
unsigned :1;
unsigned ODCA4 :1;
unsigned ODCA5 :1;
};
} ODCONAbits_t;
extern volatile ODCONAbits_t ODCONAbits __at(0x28C);

# 5970
extern volatile unsigned char ODCONC __at(0x28E);

asm("ODCONC equ 028Eh");


typedef union {
struct {
unsigned ODCC0 :1;
unsigned ODCC1 :1;
unsigned ODCC2 :1;
unsigned ODCC3 :1;
unsigned ODCC4 :1;
unsigned ODCC5 :1;
};
} ODCONCbits_t;
extern volatile ODCONCbits_t ODCONCbits __at(0x28E);

# 6020
extern volatile unsigned short CCPR1 __at(0x291);

asm("CCPR1 equ 0291h");




extern volatile unsigned char CCPR1L __at(0x291);

asm("CCPR1L equ 0291h");


typedef union {
struct {
unsigned CCPR1L :8;
};
} CCPR1Lbits_t;
extern volatile CCPR1Lbits_t CCPR1Lbits __at(0x291);

# 6047
extern volatile unsigned char CCPR1H __at(0x292);

asm("CCPR1H equ 0292h");


typedef union {
struct {
unsigned CCPR1H :8;
};
} CCPR1Hbits_t;
extern volatile CCPR1Hbits_t CCPR1Hbits __at(0x292);

# 6067
extern volatile unsigned char CCP1CON __at(0x293);

asm("CCP1CON equ 0293h");


typedef union {
struct {
unsigned CCP1MODE :4;
unsigned CCP1FMT :1;
unsigned CCP1OUT :1;
unsigned :1;
unsigned CCP1EN :1;
};
struct {
unsigned CCP1MODE0 :1;
unsigned CCP1MODE1 :1;
unsigned CCP1MODE2 :1;
unsigned CCP1MODE3 :1;
};
} CCP1CONbits_t;
extern volatile CCP1CONbits_t CCP1CONbits __at(0x293);

# 6132
extern volatile unsigned char CCP1CAP __at(0x294);

asm("CCP1CAP equ 0294h");


typedef union {
struct {
unsigned CCP1CTS :4;
};
struct {
unsigned CCP1CTS0 :1;
unsigned CCP1CTS1 :1;
unsigned CCP1CTS2 :1;
unsigned CCP1CTS3 :1;
};
} CCP1CAPbits_t;
extern volatile CCP1CAPbits_t CCP1CAPbits __at(0x294);

# 6178
extern volatile unsigned short CCPR2 __at(0x295);

asm("CCPR2 equ 0295h");




extern volatile unsigned char CCPR2L __at(0x295);

asm("CCPR2L equ 0295h");


typedef union {
struct {
unsigned CCPR2L :8;
};
} CCPR2Lbits_t;
extern volatile CCPR2Lbits_t CCPR2Lbits __at(0x295);

# 6205
extern volatile unsigned char CCPR2H __at(0x296);

asm("CCPR2H equ 0296h");


typedef union {
struct {
unsigned CCPR2H :8;
};
} CCPR2Hbits_t;
extern volatile CCPR2Hbits_t CCPR2Hbits __at(0x296);

# 6225
extern volatile unsigned char CCP2CON __at(0x297);

asm("CCP2CON equ 0297h");


typedef union {
struct {
unsigned CCP2MODE :4;
unsigned CCP2FMT :1;
unsigned CCP2OUT :1;
unsigned :1;
unsigned CCP2EN :1;
};
struct {
unsigned CCP2MODE0 :1;
unsigned CCP2MODE1 :1;
unsigned CCP2MODE2 :1;
unsigned CCP2MODE3 :1;
};
} CCP2CONbits_t;
extern volatile CCP2CONbits_t CCP2CONbits __at(0x297);

# 6290
extern volatile unsigned char CCP2CAP __at(0x298);

asm("CCP2CAP equ 0298h");


typedef union {
struct {
unsigned CCP1CTS :4;
};
struct {
unsigned CCP2CTS0 :1;
unsigned CCP2CTS1 :1;
unsigned CCP2CTS2 :1;
unsigned CCP2CTS3 :1;
};
} CCP2CAPbits_t;
extern volatile CCP2CAPbits_t CCP2CAPbits __at(0x298);

# 6336
extern volatile unsigned char CCPTMRS __at(0x29F);

asm("CCPTMRS equ 029Fh");


typedef union {
struct {
unsigned C1TSEL :2;
unsigned C2TSEL :2;
unsigned C3TSEL :2;
unsigned C4TSEL :2;
};
struct {
unsigned C1TSEL0 :1;
unsigned C1TSEL1 :1;
unsigned C2TSEL0 :1;
unsigned C2TSEL1 :1;
unsigned C3TSEL0 :1;
unsigned C3TSEL1 :1;
unsigned C4TSEL0 :1;
unsigned C4TSEL1 :1;
};
} CCPTMRSbits_t;
extern volatile CCPTMRSbits_t CCPTMRSbits __at(0x29F);

# 6424
extern volatile unsigned char SLRCONA __at(0x30C);

asm("SLRCONA equ 030Ch");


typedef union {
struct {
unsigned SLRA0 :1;
unsigned SLRA1 :1;
unsigned SLRA2 :1;
unsigned :1;
unsigned SLRA4 :1;
unsigned SLRA5 :1;
};
} SLRCONAbits_t;
extern volatile SLRCONAbits_t SLRCONAbits __at(0x30C);

# 6469
extern volatile unsigned char SLRCONC __at(0x30E);

asm("SLRCONC equ 030Eh");


typedef union {
struct {
unsigned SLRC0 :1;
unsigned SLRC1 :1;
unsigned SLRC2 :1;
unsigned SLRC3 :1;
unsigned SLRC4 :1;
unsigned SLRC5 :1;
};
} SLRCONCbits_t;
extern volatile SLRCONCbits_t SLRCONCbits __at(0x30E);

# 6519
extern volatile unsigned short CCPR3 __at(0x311);

asm("CCPR3 equ 0311h");




extern volatile unsigned char CCPR3L __at(0x311);

asm("CCPR3L equ 0311h");


typedef union {
struct {
unsigned CCPR3L :8;
};
} CCPR3Lbits_t;
extern volatile CCPR3Lbits_t CCPR3Lbits __at(0x311);

# 6546
extern volatile unsigned char CCPR3H __at(0x312);

asm("CCPR3H equ 0312h");


typedef union {
struct {
unsigned CCPR3H :8;
};
} CCPR3Hbits_t;
extern volatile CCPR3Hbits_t CCPR3Hbits __at(0x312);

# 6566
extern volatile unsigned char CCP3CON __at(0x313);

asm("CCP3CON equ 0313h");


typedef union {
struct {
unsigned CCP3MODE :4;
unsigned CCP3FMT :1;
unsigned CCP3OUT :1;
unsigned :1;
unsigned CCP3EN :1;
};
struct {
unsigned CCP3MODE0 :1;
unsigned CCP3MODE1 :1;
unsigned CCP3MODE2 :1;
unsigned CCP3MODE3 :1;
};
} CCP3CONbits_t;
extern volatile CCP3CONbits_t CCP3CONbits __at(0x313);

# 6631
extern volatile unsigned char CCP3CAP __at(0x314);

asm("CCP3CAP equ 0314h");


typedef union {
struct {
unsigned CCP3CTS :4;
};
struct {
unsigned CCAP0 :1;
unsigned CCAP1 :1;
unsigned CCAP2 :1;
unsigned CCAP3 :1;
};
} CCP3CAPbits_t;
extern volatile CCP3CAPbits_t CCP3CAPbits __at(0x314);

# 6677
extern volatile unsigned short CCPR4 __at(0x315);

asm("CCPR4 equ 0315h");




extern volatile unsigned char CCPR4L __at(0x315);

asm("CCPR4L equ 0315h");


typedef union {
struct {
unsigned CCPR4L :8;
};
} CCPR4Lbits_t;
extern volatile CCPR4Lbits_t CCPR4Lbits __at(0x315);

# 6704
extern volatile unsigned char CCPR4H __at(0x316);

asm("CCPR4H equ 0316h");


typedef union {
struct {
unsigned CCPR4H :8;
};
} CCPR4Hbits_t;
extern volatile CCPR4Hbits_t CCPR4Hbits __at(0x316);

# 6724
extern volatile unsigned char CCP4CON __at(0x317);

asm("CCP4CON equ 0317h");


typedef union {
struct {
unsigned CCP4MODE :4;
unsigned CCP4FMT :1;
unsigned CCP4OUT :1;
unsigned :1;
unsigned CCP4EN :1;
};
struct {
unsigned CCP4MODE0 :1;
unsigned CCP4MODE1 :1;
unsigned CCP4MODE2 :1;
unsigned CCP4MODE3 :1;
};
} CCP4CONbits_t;
extern volatile CCP4CONbits_t CCP4CONbits __at(0x317);

# 6789
extern volatile unsigned char CCP4CAP __at(0x318);

asm("CCP4CAP equ 0318h");


typedef union {
struct {
unsigned CCP4CTS :4;
};
struct {
unsigned CCP4CTS0 :1;
unsigned CCP4CTS1 :1;
unsigned CCP4CTS2 :1;
unsigned CCP4CTS3 :1;
};
} CCP4CAPbits_t;
extern volatile CCP4CAPbits_t CCP4CAPbits __at(0x318);

# 6835
extern volatile unsigned char INLVLA __at(0x38C);

asm("INLVLA equ 038Ch");


typedef union {
struct {
unsigned INLVLA0 :1;
unsigned INLVLA1 :1;
unsigned INLVLA2 :1;
unsigned INLVLA3 :1;
unsigned INLVLA4 :1;
unsigned INLVLA5 :1;
};
} INLVLAbits_t;
extern volatile INLVLAbits_t INLVLAbits __at(0x38C);

# 6885
extern volatile unsigned char INLVLC __at(0x38E);

asm("INLVLC equ 038Eh");


typedef union {
struct {
unsigned INLVLC0 :1;
unsigned INLVLC1 :1;
unsigned INLVLC2 :1;
unsigned INLVLC3 :1;
unsigned INLVLC4 :1;
unsigned INLVLC5 :1;
};
} INLVLCbits_t;
extern volatile INLVLCbits_t INLVLCbits __at(0x38E);

# 6935
extern volatile unsigned char IOCAP __at(0x391);

asm("IOCAP equ 0391h");


typedef union {
struct {
unsigned IOCAP0 :1;
unsigned IOCAP1 :1;
unsigned IOCAP2 :1;
unsigned IOCAP3 :1;
unsigned IOCAP4 :1;
unsigned IOCAP5 :1;
};
} IOCAPbits_t;
extern volatile IOCAPbits_t IOCAPbits __at(0x391);

# 6985
extern volatile unsigned char IOCAN __at(0x392);

asm("IOCAN equ 0392h");


typedef union {
struct {
unsigned IOCAN0 :1;
unsigned IOCAN1 :1;
unsigned IOCAN2 :1;
unsigned IOCAN3 :1;
unsigned IOCAN4 :1;
unsigned IOCAN5 :1;
};
} IOCANbits_t;
extern volatile IOCANbits_t IOCANbits __at(0x392);

# 7035
extern volatile unsigned char IOCAF __at(0x393);

asm("IOCAF equ 0393h");


typedef union {
struct {
unsigned IOCAF0 :1;
unsigned IOCAF1 :1;
unsigned IOCAF2 :1;
unsigned IOCAF3 :1;
unsigned IOCAF4 :1;
unsigned IOCAF5 :1;
};
} IOCAFbits_t;
extern volatile IOCAFbits_t IOCAFbits __at(0x393);

# 7085
extern volatile unsigned char IOCCP __at(0x397);

asm("IOCCP equ 0397h");


typedef union {
struct {
unsigned IOCCP0 :1;
unsigned IOCCP1 :1;
unsigned IOCCP2 :1;
unsigned IOCCP3 :1;
unsigned IOCCP4 :1;
unsigned IOCCP5 :1;
};
} IOCCPbits_t;
extern volatile IOCCPbits_t IOCCPbits __at(0x397);

# 7135
extern volatile unsigned char IOCCN __at(0x398);

asm("IOCCN equ 0398h");


typedef union {
struct {
unsigned IOCCN0 :1;
unsigned IOCCN1 :1;
unsigned IOCCN2 :1;
unsigned IOCCN3 :1;
unsigned IOCCN4 :1;
unsigned IOCCN5 :1;
};
} IOCCNbits_t;
extern volatile IOCCNbits_t IOCCNbits __at(0x398);

# 7185
extern volatile unsigned char IOCCF __at(0x399);

asm("IOCCF equ 0399h");


typedef union {
struct {
unsigned IOCCF0 :1;
unsigned IOCCF1 :1;
unsigned IOCCF2 :1;
unsigned IOCCF3 :1;
unsigned IOCCF4 :1;
unsigned IOCCF5 :1;
};
} IOCCFbits_t;
extern volatile IOCCFbits_t IOCCFbits __at(0x399);

# 7235
extern volatile unsigned char CLKRCON __at(0x39A);

asm("CLKRCON equ 039Ah");


typedef union {
struct {
unsigned CLKRDIV :3;
unsigned CLKRDC :2;
unsigned :2;
unsigned CLKREN :1;
};
struct {
unsigned CLKRDIV0 :1;
unsigned CLKRDIV1 :1;
unsigned CLKRDIV2 :1;
unsigned CLKRDC0 :1;
unsigned CLKRDC1 :1;
};
} CLKRCONbits_t;
extern volatile CLKRCONbits_t CLKRCONbits __at(0x39A);

# 7300
extern volatile unsigned char MDCON __at(0x39C);

asm("MDCON equ 039Ch");


typedef union {
struct {
unsigned MDBIT :1;
unsigned :2;
unsigned MDOUT :1;
unsigned MDOPOL :1;
unsigned :2;
unsigned MDEN :1;
};
} MDCONbits_t;
extern volatile MDCONbits_t MDCONbits __at(0x39C);

# 7340
extern volatile unsigned char MDSRC __at(0x39D);

asm("MDSRC equ 039Dh");


typedef union {
struct {
unsigned MDMS :4;
};
struct {
unsigned MDMS0 :1;
unsigned MDMS1 :1;
unsigned MDMS2 :1;
unsigned MDMS3 :1;
};
} MDSRCbits_t;
extern volatile MDSRCbits_t MDSRCbits __at(0x39D);

# 7386
extern volatile unsigned char MDCARH __at(0x39E);

asm("MDCARH equ 039Eh");


typedef union {
struct {
unsigned MDCH :4;
unsigned :1;
unsigned MDCHSYNC :1;
unsigned MDCHPOL :1;
};
struct {
unsigned MDCH0 :1;
unsigned MDCH1 :1;
unsigned MDCH2 :1;
unsigned MDCH3 :1;
};
} MDCARHbits_t;
extern volatile MDCARHbits_t MDCARHbits __at(0x39E);

# 7445
extern volatile unsigned char MDCARL __at(0x39F);

asm("MDCARL equ 039Fh");


typedef union {
struct {
unsigned MDCL :4;
unsigned :1;
unsigned MDCLSYNC :1;
unsigned MDCLPOL :1;
};
struct {
unsigned MDCL0 :1;
unsigned MDCL1 :1;
unsigned MDCL2 :1;
unsigned MDCL3 :1;
};
} MDCARLbits_t;
extern volatile MDCARLbits_t MDCARLbits __at(0x39F);

# 7504
extern volatile unsigned short TMR3 __at(0x411);

asm("TMR3 equ 0411h");




extern volatile unsigned char TMR3L __at(0x411);

asm("TMR3L equ 0411h");


typedef union {
struct {
unsigned TMR3L :8;
};
} TMR3Lbits_t;
extern volatile TMR3Lbits_t TMR3Lbits __at(0x411);

# 7531
extern volatile unsigned char TMR3H __at(0x412);

asm("TMR3H equ 0412h");


typedef union {
struct {
unsigned TMR3H :8;
};
} TMR3Hbits_t;
extern volatile TMR3Hbits_t TMR3Hbits __at(0x412);

# 7551
extern volatile unsigned char T3CON __at(0x413);

asm("T3CON equ 0413h");


typedef union {
struct {
unsigned TMR3ON :1;
unsigned :1;
unsigned T3SYNC :1;
unsigned T3SOSC :1;
unsigned T3CKPS :2;
unsigned TMR3CS :2;
};
struct {
unsigned :4;
unsigned T3CKPS0 :1;
unsigned T3CKPS1 :1;
unsigned TMR3CS0 :1;
unsigned TMR3CS1 :1;
};
} T3CONbits_t;
extern volatile T3CONbits_t T3CONbits __at(0x413);

# 7623
extern volatile unsigned char T3GCON __at(0x414);

asm("T3GCON equ 0414h");


typedef union {
struct {
unsigned T3GSS :2;
unsigned T3GVAL :1;
unsigned T3GGO_nDONE :1;
unsigned T3GSPM :1;
unsigned T3GTM :1;
unsigned T3GPOL :1;
unsigned TMR3GE :1;
};
struct {
unsigned T3GSS0 :1;
unsigned T3GSS1 :1;
};
} T3GCONbits_t;
extern volatile T3GCONbits_t T3GCONbits __at(0x414);

# 7693
extern volatile unsigned char TMR4 __at(0x415);

asm("TMR4 equ 0415h");


typedef union {
struct {
unsigned TMR4 :8;
};
} TMR4bits_t;
extern volatile TMR4bits_t TMR4bits __at(0x415);

# 7713
extern volatile unsigned char PR4 __at(0x416);

asm("PR4 equ 0416h");


typedef union {
struct {
unsigned PR4 :8;
};
} PR4bits_t;
extern volatile PR4bits_t PR4bits __at(0x416);

# 7733
extern volatile unsigned char T4CON __at(0x417);

asm("T4CON equ 0417h");


typedef union {
struct {
unsigned T4CKPS :2;
unsigned TMR4ON :1;
unsigned T4OUTPS :4;
};
struct {
unsigned T4CKPS0 :1;
unsigned T4CKPS1 :1;
unsigned :1;
unsigned T4OUTPS0 :1;
unsigned T4OUTPS1 :1;
unsigned T4OUTPS2 :1;
unsigned T4OUTPS3 :1;
};
} T4CONbits_t;
extern volatile T4CONbits_t T4CONbits __at(0x417);

# 7804
extern volatile unsigned short TMR5 __at(0x418);

asm("TMR5 equ 0418h");




extern volatile unsigned char TMR5L __at(0x418);

asm("TMR5L equ 0418h");


typedef union {
struct {
unsigned TMR5L :8;
};
} TMR5Lbits_t;
extern volatile TMR5Lbits_t TMR5Lbits __at(0x418);

# 7831
extern volatile unsigned char TMR5H __at(0x419);

asm("TMR5H equ 0419h");


typedef union {
struct {
unsigned TMR5H :8;
};
} TMR5Hbits_t;
extern volatile TMR5Hbits_t TMR5Hbits __at(0x419);

# 7851
extern volatile unsigned char T5CON __at(0x41A);

asm("T5CON equ 041Ah");


typedef union {
struct {
unsigned TMR5ON :1;
unsigned :1;
unsigned T5SYNC :1;
unsigned T5SOSC :1;
unsigned T5CKPS :2;
unsigned TMR5CS :2;
};
struct {
unsigned :4;
unsigned T5CKPS0 :1;
unsigned T5CKPS1 :1;
unsigned TMR5CS0 :1;
unsigned TMR5CS1 :1;
};
} T5CONbits_t;
extern volatile T5CONbits_t T5CONbits __at(0x41A);

# 7923
extern volatile unsigned char T5GCON __at(0x41B);

asm("T5GCON equ 041Bh");


typedef union {
struct {
unsigned T5GSS :2;
unsigned T5GVAL :1;
unsigned T5GGO_nDONE :1;
unsigned T5GSPM :1;
unsigned T5GTM :1;
unsigned T5GPOL :1;
unsigned TMR5GE :1;
};
struct {
unsigned T5GSS0 :1;
unsigned T5GSS1 :1;
};
} T5GCONbits_t;
extern volatile T5GCONbits_t T5GCONbits __at(0x41B);

# 7993
extern volatile unsigned char TMR6 __at(0x41C);

asm("TMR6 equ 041Ch");


typedef union {
struct {
unsigned TMR6 :8;
};
} TMR6bits_t;
extern volatile TMR6bits_t TMR6bits __at(0x41C);

# 8013
extern volatile unsigned char PR6 __at(0x41D);

asm("PR6 equ 041Dh");


typedef union {
struct {
unsigned PR6 :8;
};
} PR6bits_t;
extern volatile PR6bits_t PR6bits __at(0x41D);

# 8033
extern volatile unsigned char T6CON __at(0x41E);

asm("T6CON equ 041Eh");


typedef union {
struct {
unsigned T6CKPS :2;
unsigned TMR6ON :1;
unsigned T6OUTPS :4;
};
struct {
unsigned T6CKPS0 :1;
unsigned T6CKPS1 :1;
unsigned :1;
unsigned T6OUTPS0 :1;
unsigned T6OUTPS1 :1;
unsigned T6OUTPS2 :1;
unsigned T6OUTPS3 :1;
};
} T6CONbits_t;
extern volatile T6CONbits_t T6CONbits __at(0x41E);

# 8104
extern volatile unsigned char CCDCON __at(0x41F);

asm("CCDCON equ 041Fh");


typedef union {
struct {
unsigned CCDS :2;
unsigned :5;
unsigned CCDEN :1;
};
struct {
unsigned CCDS0 :1;
unsigned CCDS1 :1;
};
} CCDCONbits_t;
extern volatile CCDCONbits_t CCDCONbits __at(0x41F);

# 8146
extern volatile __uint24 NCO1ACC __at(0x498);


asm("NCO1ACC equ 0498h");




extern volatile unsigned char NCO1ACCL __at(0x498);

asm("NCO1ACCL equ 0498h");


typedef union {
struct {
unsigned NCO1ACC :8;
};
} NCO1ACCLbits_t;
extern volatile NCO1ACCLbits_t NCO1ACCLbits __at(0x498);

# 8174
extern volatile unsigned char NCO1ACCH __at(0x499);

asm("NCO1ACCH equ 0499h");


typedef union {
struct {
unsigned NCO1ACC :8;
};
} NCO1ACCHbits_t;
extern volatile NCO1ACCHbits_t NCO1ACCHbits __at(0x499);

# 8194
extern volatile unsigned char NCO1ACCU __at(0x49A);

asm("NCO1ACCU equ 049Ah");


typedef union {
struct {
unsigned NCO1ACC :4;
};
} NCO1ACCUbits_t;
extern volatile NCO1ACCUbits_t NCO1ACCUbits __at(0x49A);

# 8215
extern volatile __uint24 NCO1INC __at(0x49B);


asm("NCO1INC equ 049Bh");




extern volatile unsigned char NCO1INCL __at(0x49B);

asm("NCO1INCL equ 049Bh");


typedef union {
struct {
unsigned NCO1INC :8;
};
} NCO1INCLbits_t;
extern volatile NCO1INCLbits_t NCO1INCLbits __at(0x49B);

# 8243
extern volatile unsigned char NCO1INCH __at(0x49C);

asm("NCO1INCH equ 049Ch");


typedef union {
struct {
unsigned NCO1INC :8;
};
} NCO1INCHbits_t;
extern volatile NCO1INCHbits_t NCO1INCHbits __at(0x49C);

# 8263
extern volatile unsigned char NCO1INCU __at(0x49D);

asm("NCO1INCU equ 049Dh");


typedef union {
struct {
unsigned NCO1INC :4;
};
} NCO1INCUbits_t;
extern volatile NCO1INCUbits_t NCO1INCUbits __at(0x49D);

# 8283
extern volatile unsigned char NCO1CON __at(0x49E);

asm("NCO1CON equ 049Eh");


typedef union {
struct {
unsigned N1PFM :1;
unsigned :3;
unsigned N1POL :1;
unsigned N1OUT :1;
unsigned :1;
unsigned N1EN :1;
};
} NCO1CONbits_t;
extern volatile NCO1CONbits_t NCO1CONbits __at(0x49E);

# 8323
extern volatile unsigned char NCO1CLK __at(0x49F);

asm("NCO1CLK equ 049Fh");


typedef union {
struct {
unsigned N1CKS :2;
unsigned :3;
unsigned N1PWS :3;
};
} NCO1CLKbits_t;
extern volatile NCO1CLKbits_t NCO1CLKbits __at(0x49F);

# 8350
extern volatile unsigned char PWM5DCL __at(0x617);

asm("PWM5DCL equ 0617h");


typedef union {
struct {
unsigned :6;
unsigned PWM5DCL :2;
};
struct {
unsigned :6;
unsigned PWM5DCL0 :1;
unsigned PWM5DCL1 :1;
};
} PWM5DCLbits_t;
extern volatile PWM5DCLbits_t PWM5DCLbits __at(0x617);

# 8386
extern volatile unsigned char PWM5DCH __at(0x618);

asm("PWM5DCH equ 0618h");


typedef union {
struct {
unsigned PWM5DCH :8;
};
struct {
unsigned PWM5DCH0 :1;
unsigned PWM5DCH1 :1;
unsigned PWM5DCH2 :1;
unsigned PWM5DCH3 :1;
unsigned PWM5DCH4 :1;
unsigned PWM5DCH5 :1;
unsigned PWM5DCH6 :1;
unsigned PWM5DCH7 :1;
};
} PWM5DCHbits_t;
extern volatile PWM5DCHbits_t PWM5DCHbits __at(0x618);

# 8456
extern volatile unsigned char PWM5CON __at(0x619);

asm("PWM5CON equ 0619h");


extern volatile unsigned char PWM5CON0 __at(0x619);

asm("PWM5CON0 equ 0619h");


typedef union {
struct {
unsigned :4;
unsigned PWM5POL :1;
unsigned PWM5OUT :1;
unsigned :1;
unsigned PWM5EN :1;
};
} PWM5CONbits_t;
extern volatile PWM5CONbits_t PWM5CONbits __at(0x619);

# 8493
typedef union {
struct {
unsigned :4;
unsigned PWM5POL :1;
unsigned PWM5OUT :1;
unsigned :1;
unsigned PWM5EN :1;
};
} PWM5CON0bits_t;
extern volatile PWM5CON0bits_t PWM5CON0bits __at(0x619);

# 8522
extern volatile unsigned char PWM6DCL __at(0x61A);

asm("PWM6DCL equ 061Ah");


typedef union {
struct {
unsigned :6;
unsigned PWM6DCL :2;
};
struct {
unsigned :6;
unsigned PWM6DCL0 :1;
unsigned PWM6DCL1 :1;
};
} PWM6DCLbits_t;
extern volatile PWM6DCLbits_t PWM6DCLbits __at(0x61A);

# 8558
extern volatile unsigned char PWM6DCH __at(0x61B);

asm("PWM6DCH equ 061Bh");


typedef union {
struct {
unsigned PWM6DCH :8;
};
struct {
unsigned PWM6DCH0 :1;
unsigned PWM6DCH1 :1;
unsigned PWM6DCH2 :1;
unsigned PWM6DCH3 :1;
unsigned PWM6DCH4 :1;
unsigned PWM6DCH5 :1;
unsigned PWM6DCH6 :1;
unsigned PWM6DCH7 :1;
};
} PWM6DCHbits_t;
extern volatile PWM6DCHbits_t PWM6DCHbits __at(0x61B);

# 8628
extern volatile unsigned char PWM6CON __at(0x61C);

asm("PWM6CON equ 061Ch");


extern volatile unsigned char PWM6CON0 __at(0x61C);

asm("PWM6CON0 equ 061Ch");


typedef union {
struct {
unsigned :4;
unsigned PWM6POL :1;
unsigned PWM6OUT :1;
unsigned :1;
unsigned PWM6EN :1;
};
} PWM6CONbits_t;
extern volatile PWM6CONbits_t PWM6CONbits __at(0x61C);

# 8665
typedef union {
struct {
unsigned :4;
unsigned PWM6POL :1;
unsigned PWM6OUT :1;
unsigned :1;
unsigned PWM6EN :1;
};
} PWM6CON0bits_t;
extern volatile PWM6CON0bits_t PWM6CON0bits __at(0x61C);

# 8694
extern volatile unsigned char PWMTMRS __at(0x61F);

asm("PWMTMRS equ 061Fh");


typedef union {
struct {
unsigned P5TSEL :2;
unsigned P6TSEL :2;
};
struct {
unsigned P5TSEL0 :1;
unsigned P5TSEL1 :1;
unsigned P6TSEL0 :1;
unsigned P6TSEL1 :1;
};
} PWMTMRSbits_t;
extern volatile PWMTMRSbits_t PWMTMRSbits __at(0x61F);

# 8746
extern volatile unsigned char CWG1CLKCON __at(0x691);

asm("CWG1CLKCON equ 0691h");


typedef union {
struct {
unsigned CS :1;
};
struct {
unsigned CWG1CS :1;
};
} CWG1CLKCONbits_t;
extern volatile CWG1CLKCONbits_t CWG1CLKCONbits __at(0x691);

# 8774
extern volatile unsigned char CWG1DAT __at(0x692);

asm("CWG1DAT equ 0692h");


typedef union {
struct {
unsigned DAT :4;
};
struct {
unsigned CWG1DAT0 :1;
unsigned CWG1DAT1 :1;
unsigned CWG1DAT2 :1;
unsigned CWG1DAT3 :1;
};
} CWG1DATbits_t;
extern volatile CWG1DATbits_t CWG1DATbits __at(0x692);

# 8820
extern volatile unsigned char CWG1DBR __at(0x693);

asm("CWG1DBR equ 0693h");


typedef union {
struct {
unsigned DBR :6;
};
struct {
unsigned DBR0 :1;
unsigned DBR1 :1;
unsigned DBR2 :1;
unsigned DBR3 :1;
unsigned DBR4 :1;
unsigned DBR5 :1;
};
struct {
unsigned CWG1DBR :6;
};
struct {
unsigned CWG1DBR0 :1;
unsigned CWG1DBR1 :1;
unsigned CWG1DBR2 :1;
unsigned CWG1DBR3 :1;
unsigned CWG1DBR4 :1;
unsigned CWG1DBR5 :1;
};
} CWG1DBRbits_t;
extern volatile CWG1DBRbits_t CWG1DBRbits __at(0x693);

# 8924
extern volatile unsigned char CWG1DBF __at(0x694);

asm("CWG1DBF equ 0694h");


typedef union {
struct {
unsigned DBF :6;
};
struct {
unsigned DBF0 :1;
unsigned DBF1 :1;
unsigned DBF2 :1;
unsigned DBF3 :1;
unsigned DBF4 :1;
unsigned DBF5 :1;
};
struct {
unsigned CWG1DBF :6;
};
struct {
unsigned CWG1DBF0 :1;
unsigned CWG1DBF1 :1;
unsigned CWG1DBF2 :1;
unsigned CWG1DBF3 :1;
unsigned CWG1DBF4 :1;
unsigned CWG1DBF5 :1;
};
} CWG1DBFbits_t;
extern volatile CWG1DBFbits_t CWG1DBFbits __at(0x694);

# 9028
extern volatile unsigned char CWG1CON0 __at(0x695);

asm("CWG1CON0 equ 0695h");


typedef union {
struct {
unsigned MODE :3;
unsigned :3;
unsigned LD :1;
unsigned EN :1;
};
struct {
unsigned MODE0 :1;
unsigned MODE1 :1;
unsigned MODE2 :1;
unsigned :4;
unsigned G1EN :1;
};
struct {
unsigned CWG1MODE :3;
unsigned :3;
unsigned CWG1LD :1;
unsigned CWG1EN :1;
};
struct {
unsigned CWG1MODE0 :1;
unsigned CWG1MODE1 :1;
unsigned CWG1MODE2 :1;
};
} CWG1CON0bits_t;
extern volatile CWG1CON0bits_t CWG1CON0bits __at(0x695);

# 9129
extern volatile unsigned char CWG1CON1 __at(0x696);

asm("CWG1CON1 equ 0696h");


typedef union {
struct {
unsigned POLA :1;
unsigned POLB :1;
unsigned POLC :1;
unsigned POLD :1;
unsigned :1;
unsigned IN :1;
};
struct {
unsigned CWG1POLA :1;
unsigned CWG1POLB :1;
unsigned CWG1POLC :1;
unsigned CWG1POLD :1;
unsigned :1;
unsigned CWG1IN :1;
};
} CWG1CON1bits_t;
extern volatile CWG1CON1bits_t CWG1CON1bits __at(0x696);

# 9207
extern volatile unsigned char CWG1AS0 __at(0x697);

asm("CWG1AS0 equ 0697h");


typedef union {
struct {
unsigned :2;
unsigned LSAC :2;
unsigned LSBD :2;
unsigned REN :1;
unsigned SHUTDOWN :1;
};
struct {
unsigned :2;
unsigned LSAC0 :1;
unsigned LSAC1 :1;
unsigned LSBD0 :1;
unsigned LSBD1 :1;
};
struct {
unsigned :2;
unsigned CWG1LSAC :2;
unsigned CWG1LSBD :2;
unsigned CWG1REN :1;
unsigned CWG1SHUTDOWN :1;
};
struct {
unsigned :2;
unsigned CWG1LSAC0 :1;
unsigned CWG1LSAC1 :1;
unsigned CWG1LSBD0 :1;
unsigned CWG1LSBD1 :1;
};
} CWG1AS0bits_t;
extern volatile CWG1AS0bits_t CWG1AS0bits __at(0x697);

# 9327
extern volatile unsigned char CWG1AS1 __at(0x698);

asm("CWG1AS1 equ 0698h");


typedef union {
struct {
unsigned AS0E :1;
unsigned AS1E :1;
unsigned AS2E :1;
unsigned AS3E :1;
unsigned AS4E :1;
};
} CWG1AS1bits_t;
extern volatile CWG1AS1bits_t CWG1AS1bits __at(0x698);

# 9371
extern volatile unsigned char CWG1STR __at(0x699);

asm("CWG1STR equ 0699h");


typedef union {
struct {
unsigned STRA :1;
unsigned STRB :1;
unsigned STRC :1;
unsigned STRD :1;
unsigned OVRA :1;
unsigned OVRB :1;
unsigned OVRC :1;
unsigned OVRD :1;
};
struct {
unsigned CWG1STRA :1;
unsigned CWG1STRB :1;
unsigned CWG1STRC :1;
unsigned CWG1STRD :1;
unsigned CWG1OVRA :1;
unsigned CWG1OVRB :1;
unsigned CWG1OVRC :1;
unsigned CWG1OVRD :1;
};
} CWG1STRbits_t;
extern volatile CWG1STRbits_t CWG1STRbits __at(0x699);

# 9483
extern volatile unsigned char CWG2CLKCON __at(0x711);

asm("CWG2CLKCON equ 0711h");


typedef union {
struct {
unsigned CS :1;
};
struct {
unsigned CWG2CS :1;
};
} CWG2CLKCONbits_t;
extern volatile CWG2CLKCONbits_t CWG2CLKCONbits __at(0x711);

# 9511
extern volatile unsigned char CWG2DAT __at(0x712);

asm("CWG2DAT equ 0712h");


typedef union {
struct {
unsigned DAT :4;
};
struct {
unsigned CWG2DAT0 :1;
unsigned CWG2DAT1 :1;
unsigned CWG2DAT2 :1;
unsigned CWG2DAT3 :1;
};
} CWG2DATbits_t;
extern volatile CWG2DATbits_t CWG2DATbits __at(0x712);

# 9557
extern volatile unsigned char CWG2DBR __at(0x713);

asm("CWG2DBR equ 0713h");


typedef union {
struct {
unsigned DBR :6;
};
struct {
unsigned DBR0 :1;
unsigned DBR1 :1;
unsigned DBR2 :1;
unsigned DBR3 :1;
unsigned DBR4 :1;
unsigned DBR5 :1;
};
struct {
unsigned CWG2DBR :6;
};
struct {
unsigned CWG2DBR0 :1;
unsigned CWG2DBR1 :1;
unsigned CWG2DBR2 :1;
unsigned CWG2DBR3 :1;
unsigned CWG2DBR4 :1;
unsigned CWG2DBR5 :1;
};
} CWG2DBRbits_t;
extern volatile CWG2DBRbits_t CWG2DBRbits __at(0x713);

# 9661
extern volatile unsigned char CWG2DBF __at(0x714);

asm("CWG2DBF equ 0714h");


typedef union {
struct {
unsigned DBF :6;
};
struct {
unsigned DBF0 :1;
unsigned DBF1 :1;
unsigned DBF2 :1;
unsigned DBF3 :1;
unsigned DBF4 :1;
unsigned DBF5 :1;
};
struct {
unsigned CWG2DBF :6;
};
struct {
unsigned CWG2DBF0 :1;
unsigned CWG2DBF1 :1;
unsigned CWG2DBF2 :1;
unsigned CWG2DBF3 :1;
unsigned CWG2DBF4 :1;
unsigned CWG2DBF5 :1;
};
} CWG2DBFbits_t;
extern volatile CWG2DBFbits_t CWG2DBFbits __at(0x714);

# 9765
extern volatile unsigned char CWG2CON0 __at(0x715);

asm("CWG2CON0 equ 0715h");


typedef union {
struct {
unsigned MODE :3;
unsigned :3;
unsigned LD :1;
unsigned EN :1;
};
struct {
unsigned MODE0 :1;
unsigned MODE1 :1;
unsigned MODE2 :1;
unsigned :4;
unsigned G2EN :1;
};
struct {
unsigned CWG2MODE :3;
unsigned :3;
unsigned CWG2LD :1;
unsigned CWG2EN :1;
};
struct {
unsigned CWG2MODE0 :1;
unsigned CWG2MODE1 :1;
unsigned CWG2MODE2 :1;
};
} CWG2CON0bits_t;
extern volatile CWG2CON0bits_t CWG2CON0bits __at(0x715);

# 9866
extern volatile unsigned char CWG2CON1 __at(0x716);

asm("CWG2CON1 equ 0716h");


typedef union {
struct {
unsigned POLA :1;
unsigned POLB :1;
unsigned POLC :1;
unsigned POLD :1;
unsigned :1;
unsigned IN :1;
};
struct {
unsigned CWG2POLA :1;
unsigned CWG2POLB :1;
unsigned CWG2POLC :1;
unsigned CWG2POLD :1;
unsigned :1;
unsigned CWG2IN :1;
};
} CWG2CON1bits_t;
extern volatile CWG2CON1bits_t CWG2CON1bits __at(0x716);

# 9944
extern volatile unsigned char CWG2AS0 __at(0x717);

asm("CWG2AS0 equ 0717h");


typedef union {
struct {
unsigned :2;
unsigned LSAC :2;
unsigned LSBD :2;
unsigned REN :1;
unsigned SHUTDOWN :1;
};
struct {
unsigned :2;
unsigned LSAC0 :1;
unsigned LSAC1 :1;
unsigned LSBD0 :1;
unsigned LSBD1 :1;
};
struct {
unsigned :2;
unsigned CWG2LSAC :2;
unsigned CWG2LSBD :2;
unsigned CWG2REN :1;
unsigned CWG2SHUTDOWN :1;
};
struct {
unsigned :2;
unsigned CWG2LSAC0 :1;
unsigned CWG2LSAC1 :1;
unsigned CWG2LSBD0 :1;
unsigned CWG2LSBD1 :1;
};
} CWG2AS0bits_t;
extern volatile CWG2AS0bits_t CWG2AS0bits __at(0x717);

# 10064
extern volatile unsigned char CWG2AS1 __at(0x718);

asm("CWG2AS1 equ 0718h");


typedef union {
struct {
unsigned AS0E :1;
unsigned AS1E :1;
unsigned AS2E :1;
unsigned AS3E :1;
unsigned AS4E :1;
};
} CWG2AS1bits_t;
extern volatile CWG2AS1bits_t CWG2AS1bits __at(0x718);

# 10108
extern volatile unsigned char CWG2STR __at(0x719);

asm("CWG2STR equ 0719h");


typedef union {
struct {
unsigned STRA :1;
unsigned STRB :1;
unsigned STRC :1;
unsigned STRD :1;
unsigned OVRA :1;
unsigned OVRB :1;
unsigned OVRC :1;
unsigned OVRD :1;
};
struct {
unsigned CWG2STRA :1;
unsigned CWG2STRB :1;
unsigned CWG2STRC :1;
unsigned CWG2STRD :1;
unsigned CWG2OVRA :1;
unsigned CWG2OVRB :1;
unsigned CWG2OVRC :1;
unsigned CWG2OVRD :1;
};
} CWG2STRbits_t;
extern volatile CWG2STRbits_t CWG2STRbits __at(0x719);

# 10220
extern volatile unsigned short NVMADR __at(0x891);

asm("NVMADR equ 0891h");


extern volatile unsigned short EEADR __at(0x891);

asm("EEADR equ 0891h");

extern volatile unsigned short PMADR __at(0x891);

asm("PMADR equ 0891h");




extern volatile unsigned char NVMADRL __at(0x891);

asm("NVMADRL equ 0891h");


extern volatile unsigned char EEADRL __at(0x891);

asm("EEADRL equ 0891h");

extern volatile unsigned char PMADRL __at(0x891);

asm("PMADRL equ 0891h");


typedef union {
struct {
unsigned NVMADRL :8;
};
struct {
unsigned NVMADR0 :1;
unsigned NVMADR1 :1;
unsigned NVMADR2 :1;
unsigned NVMADR3 :1;
unsigned NVMADR4 :1;
unsigned NVMADR5 :1;
unsigned NVMADR6 :1;
unsigned NVMADR7 :1;
};
struct {
unsigned EEADRL :8;
};
struct {
unsigned PMADRL :8;
};
} NVMADRLbits_t;
extern volatile NVMADRLbits_t NVMADRLbits __at(0x891);

# 10329
typedef union {
struct {
unsigned NVMADRL :8;
};
struct {
unsigned NVMADR0 :1;
unsigned NVMADR1 :1;
unsigned NVMADR2 :1;
unsigned NVMADR3 :1;
unsigned NVMADR4 :1;
unsigned NVMADR5 :1;
unsigned NVMADR6 :1;
unsigned NVMADR7 :1;
};
struct {
unsigned EEADRL :8;
};
struct {
unsigned PMADRL :8;
};
} EEADRLbits_t;
extern volatile EEADRLbits_t EEADRLbits __at(0x891);

# 10407
typedef union {
struct {
unsigned NVMADRL :8;
};
struct {
unsigned NVMADR0 :1;
unsigned NVMADR1 :1;
unsigned NVMADR2 :1;
unsigned NVMADR3 :1;
unsigned NVMADR4 :1;
unsigned NVMADR5 :1;
unsigned NVMADR6 :1;
unsigned NVMADR7 :1;
};
struct {
unsigned EEADRL :8;
};
struct {
unsigned PMADRL :8;
};
} PMADRLbits_t;
extern volatile PMADRLbits_t PMADRLbits __at(0x891);

# 10488
extern volatile unsigned char NVMADRH __at(0x892);

asm("NVMADRH equ 0892h");


extern volatile unsigned char EEADRH __at(0x892);

asm("EEADRH equ 0892h");

extern volatile unsigned char PMADRH __at(0x892);

asm("PMADRH equ 0892h");


typedef union {
struct {
unsigned NVMADRH :7;
};
struct {
unsigned NVMADR8 :1;
unsigned NVMADR9 :1;
unsigned NVMADR10 :1;
unsigned NVMADR11 :1;
unsigned NVMADR12 :1;
unsigned NVMADR13 :1;
unsigned NVMADR14 :1;
};
struct {
unsigned EEADRH :7;
};
struct {
unsigned PMADRH :7;
};
} NVMADRHbits_t;
extern volatile NVMADRHbits_t NVMADRHbits __at(0x892);

# 10575
typedef union {
struct {
unsigned NVMADRH :7;
};
struct {
unsigned NVMADR8 :1;
unsigned NVMADR9 :1;
unsigned NVMADR10 :1;
unsigned NVMADR11 :1;
unsigned NVMADR12 :1;
unsigned NVMADR13 :1;
unsigned NVMADR14 :1;
};
struct {
unsigned EEADRH :7;
};
struct {
unsigned PMADRH :7;
};
} EEADRHbits_t;
extern volatile EEADRHbits_t EEADRHbits __at(0x892);

# 10647
typedef union {
struct {
unsigned NVMADRH :7;
};
struct {
unsigned NVMADR8 :1;
unsigned NVMADR9 :1;
unsigned NVMADR10 :1;
unsigned NVMADR11 :1;
unsigned NVMADR12 :1;
unsigned NVMADR13 :1;
unsigned NVMADR14 :1;
};
struct {
unsigned EEADRH :7;
};
struct {
unsigned PMADRH :7;
};
} PMADRHbits_t;
extern volatile PMADRHbits_t PMADRHbits __at(0x892);

# 10722
extern volatile unsigned short NVMDAT __at(0x893);

asm("NVMDAT equ 0893h");


extern volatile unsigned short EEDAT __at(0x893);

asm("EEDAT equ 0893h");

extern volatile unsigned short PMDAT __at(0x893);

asm("PMDAT equ 0893h");




extern volatile unsigned char NVMDATL __at(0x893);

asm("NVMDATL equ 0893h");


extern volatile unsigned char EEDATL __at(0x893);

asm("EEDATL equ 0893h");

extern volatile unsigned char PMDATL __at(0x893);

asm("PMDATL equ 0893h");


typedef union {
struct {
unsigned NVMDATL :8;
};
struct {
unsigned NVMDAT0 :1;
unsigned NVMDAT1 :1;
unsigned NVMDAT2 :1;
unsigned NVMDAT3 :1;
unsigned NVMDAT4 :1;
unsigned NVMDAT5 :1;
unsigned NVMDAT6 :1;
unsigned NVMDAT7 :1;
};
struct {
unsigned EEDATL :8;
};
struct {
unsigned PMDATL :8;
};
} NVMDATLbits_t;
extern volatile NVMDATLbits_t NVMDATLbits __at(0x893);

# 10831
typedef union {
struct {
unsigned NVMDATL :8;
};
struct {
unsigned NVMDAT0 :1;
unsigned NVMDAT1 :1;
unsigned NVMDAT2 :1;
unsigned NVMDAT3 :1;
unsigned NVMDAT4 :1;
unsigned NVMDAT5 :1;
unsigned NVMDAT6 :1;
unsigned NVMDAT7 :1;
};
struct {
unsigned EEDATL :8;
};
struct {
unsigned PMDATL :8;
};
} EEDATLbits_t;
extern volatile EEDATLbits_t EEDATLbits __at(0x893);

# 10909
typedef union {
struct {
unsigned NVMDATL :8;
};
struct {
unsigned NVMDAT0 :1;
unsigned NVMDAT1 :1;
unsigned NVMDAT2 :1;
unsigned NVMDAT3 :1;
unsigned NVMDAT4 :1;
unsigned NVMDAT5 :1;
unsigned NVMDAT6 :1;
unsigned NVMDAT7 :1;
};
struct {
unsigned EEDATL :8;
};
struct {
unsigned PMDATL :8;
};
} PMDATLbits_t;
extern volatile PMDATLbits_t PMDATLbits __at(0x893);

# 10990
extern volatile unsigned char NVMDATH __at(0x894);

asm("NVMDATH equ 0894h");


extern volatile unsigned char EEDATH __at(0x894);

asm("EEDATH equ 0894h");

extern volatile unsigned char PMDATH __at(0x894);

asm("PMDATH equ 0894h");


typedef union {
struct {
unsigned NVMDATH :6;
};
struct {
unsigned NVMDAT8 :1;
unsigned NVMDAT9 :1;
unsigned NVMDAT10 :1;
unsigned NVMDAT11 :1;
unsigned NVMDAT12 :1;
unsigned NVMDAT13 :1;
};
struct {
unsigned EEDATH :6;
};
struct {
unsigned PMDATH :6;
};
} NVMDATHbits_t;
extern volatile NVMDATHbits_t NVMDATHbits __at(0x894);

# 11071
typedef union {
struct {
unsigned NVMDATH :6;
};
struct {
unsigned NVMDAT8 :1;
unsigned NVMDAT9 :1;
unsigned NVMDAT10 :1;
unsigned NVMDAT11 :1;
unsigned NVMDAT12 :1;
unsigned NVMDAT13 :1;
};
struct {
unsigned EEDATH :6;
};
struct {
unsigned PMDATH :6;
};
} EEDATHbits_t;
extern volatile EEDATHbits_t EEDATHbits __at(0x894);

# 11137
typedef union {
struct {
unsigned NVMDATH :6;
};
struct {
unsigned NVMDAT8 :1;
unsigned NVMDAT9 :1;
unsigned NVMDAT10 :1;
unsigned NVMDAT11 :1;
unsigned NVMDAT12 :1;
unsigned NVMDAT13 :1;
};
struct {
unsigned EEDATH :6;
};
struct {
unsigned PMDATH :6;
};
} PMDATHbits_t;
extern volatile PMDATHbits_t PMDATHbits __at(0x894);

# 11206
extern volatile unsigned char NVMCON1 __at(0x895);

asm("NVMCON1 equ 0895h");


extern volatile unsigned char EECON1 __at(0x895);

asm("EECON1 equ 0895h");

extern volatile unsigned char PMCON1 __at(0x895);

asm("PMCON1 equ 0895h");


typedef union {
struct {
unsigned RD :1;
unsigned WR :1;
unsigned WREN :1;
unsigned WRERR :1;
unsigned FREE :1;
unsigned LWLO :1;
unsigned NVMREGS :1;
};
struct {
unsigned :6;
unsigned CFGS :1;
};
} NVMCON1bits_t;
extern volatile NVMCON1bits_t NVMCON1bits __at(0x895);

# 11278
typedef union {
struct {
unsigned RD :1;
unsigned WR :1;
unsigned WREN :1;
unsigned WRERR :1;
unsigned FREE :1;
unsigned LWLO :1;
unsigned NVMREGS :1;
};
struct {
unsigned :6;
unsigned CFGS :1;
};
} EECON1bits_t;
extern volatile EECON1bits_t EECON1bits __at(0x895);

# 11335
typedef union {
struct {
unsigned RD :1;
unsigned WR :1;
unsigned WREN :1;
unsigned WRERR :1;
unsigned FREE :1;
unsigned LWLO :1;
unsigned NVMREGS :1;
};
struct {
unsigned :6;
unsigned CFGS :1;
};
} PMCON1bits_t;
extern volatile PMCON1bits_t PMCON1bits __at(0x895);

# 11395
extern volatile unsigned char NVMCON2 __at(0x896);

asm("NVMCON2 equ 0896h");


extern volatile unsigned char EECON2 __at(0x896);

asm("EECON2 equ 0896h");

extern volatile unsigned char PMCON2 __at(0x896);

asm("PMCON2 equ 0896h");


typedef union {
struct {
unsigned NVMCON2 :8;
};
struct {
unsigned EECON2 :8;
};
struct {
unsigned PMCON2 :8;
};
} NVMCON2bits_t;
extern volatile NVMCON2bits_t NVMCON2bits __at(0x896);

# 11438
typedef union {
struct {
unsigned NVMCON2 :8;
};
struct {
unsigned EECON2 :8;
};
struct {
unsigned PMCON2 :8;
};
} EECON2bits_t;
extern volatile EECON2bits_t EECON2bits __at(0x896);

# 11466
typedef union {
struct {
unsigned NVMCON2 :8;
};
struct {
unsigned EECON2 :8;
};
struct {
unsigned PMCON2 :8;
};
} PMCON2bits_t;
extern volatile PMCON2bits_t PMCON2bits __at(0x896);

# 11497
extern volatile unsigned char PCON0 __at(0x89B);

asm("PCON0 equ 089Bh");


typedef union {
struct {
unsigned nBOR :1;
unsigned nPOR :1;
unsigned nRI :1;
unsigned nRMCLR :1;
unsigned nRWDT :1;
unsigned :1;
unsigned STKUNF :1;
unsigned STKOVF :1;
};
} PCON0bits_t;
extern volatile PCON0bits_t PCON0bits __at(0x89B);

# 11554
extern volatile unsigned char PMD0 __at(0x911);

asm("PMD0 equ 0911h");


typedef union {
struct {
unsigned IOCMD :1;
unsigned CLKRMD :1;
unsigned NVMMD :1;
unsigned :3;
unsigned FVRMD :1;
unsigned SYSCMD :1;
};
} PMD0bits_t;
extern volatile PMD0bits_t PMD0bits __at(0x911);

# 11599
extern volatile unsigned char PMD1 __at(0x912);

asm("PMD1 equ 0912h");


typedef union {
struct {
unsigned TMR0MD :1;
unsigned TMR1MD :1;
unsigned TMR2MD :1;
unsigned TMR3MD :1;
unsigned TMR4MD :1;
unsigned TMR5MD :1;
unsigned TMR6MD :1;
unsigned NCOMD :1;
};
} PMD1bits_t;
extern volatile PMD1bits_t PMD1bits __at(0x912);

# 11661
extern volatile unsigned char PMD2 __at(0x913);

asm("PMD2 equ 0913h");


typedef union {
struct {
unsigned :1;
unsigned CMP1MD :1;
unsigned CMP2MD :1;
unsigned :2;
unsigned ADCMD :1;
unsigned DACMD :1;
};
} PMD2bits_t;
extern volatile PMD2bits_t PMD2bits __at(0x913);

# 11701
extern volatile unsigned char PMD3 __at(0x914);

asm("PMD3 equ 0914h");


typedef union {
struct {
unsigned CCP1MD :1;
unsigned CCP2MD :1;
unsigned CCP3MD :1;
unsigned CCP4MD :1;
unsigned PWM5MD :1;
unsigned PWM6MD :1;
unsigned CWG1MD :1;
unsigned CWG2MD :1;
};
} PMD3bits_t;
extern volatile PMD3bits_t PMD3bits __at(0x914);

# 11763
extern volatile unsigned char PMD4 __at(0x915);

asm("PMD4 equ 0915h");


typedef union {
struct {
unsigned :1;
unsigned MSSP1MD :1;
unsigned MSSP2MD :1;
unsigned :2;
unsigned UART1MD :1;
};
} PMD4bits_t;
extern volatile PMD4bits_t PMD4bits __at(0x915);

# 11797
extern volatile unsigned char PMD5 __at(0x916);

asm("PMD5 equ 0916h");


typedef union {
struct {
unsigned DSMMD :1;
unsigned CLC1MD :1;
unsigned CLC2MD :1;
unsigned CLC3MD :1;
unsigned CLC4MD :1;
};
} PMD5bits_t;
extern volatile PMD5bits_t PMD5bits __at(0x916);

# 11841
extern volatile unsigned char CPUDOZE __at(0x918);

asm("CPUDOZE equ 0918h");


typedef union {
struct {
unsigned DOZE :3;
unsigned :1;
unsigned DOE :1;
unsigned ROI :1;
unsigned DOZEN :1;
unsigned IDLEN :1;
};
struct {
unsigned DOZE0 :1;
unsigned DOZE1 :1;
unsigned DOZE2 :1;
};
} CPUDOZEbits_t;
extern volatile CPUDOZEbits_t CPUDOZEbits __at(0x918);

# 11906
extern volatile unsigned char OSCCON1 __at(0x919);

asm("OSCCON1 equ 0919h");


typedef union {
struct {
unsigned NDIV :4;
unsigned NOSC :3;
};
struct {
unsigned NDIV0 :1;
unsigned NDIV1 :1;
unsigned NDIV2 :1;
unsigned NDIV3 :1;
unsigned NOSC0 :1;
unsigned NOSC1 :1;
unsigned NOSC2 :1;
};
} OSCCON1bits_t;
extern volatile OSCCON1bits_t OSCCON1bits __at(0x919);

# 11976
extern volatile unsigned char OSCCON2 __at(0x91A);

asm("OSCCON2 equ 091Ah");


typedef union {
struct {
unsigned CDIV :4;
unsigned COSC :3;
};
struct {
unsigned CDIV0 :1;
unsigned CDIV1 :1;
unsigned CDIV2 :1;
unsigned CDIV3 :1;
unsigned COSC0 :1;
unsigned COSC1 :1;
unsigned COSC2 :1;
};
} OSCCON2bits_t;
extern volatile OSCCON2bits_t OSCCON2bits __at(0x91A);

# 12046
extern volatile unsigned char OSCCON3 __at(0x91B);

asm("OSCCON3 equ 091Bh");


typedef union {
struct {
unsigned :3;
unsigned NOSCR :1;
unsigned ORDY :1;
unsigned SOSCBE :1;
unsigned SOSCPWR :1;
unsigned CSWHOLD :1;
};
} OSCCON3bits_t;
extern volatile OSCCON3bits_t OSCCON3bits __at(0x91B);

# 12091
extern volatile unsigned char OSCSTAT1 __at(0x91C);

asm("OSCSTAT1 equ 091Ch");


typedef union {
struct {
unsigned PLLR :1;
unsigned :1;
unsigned ADOR :1;
unsigned SOR :1;
unsigned LFOR :1;
unsigned :1;
unsigned HFOR :1;
unsigned EXTOR :1;
};
} OSCSTAT1bits_t;
extern volatile OSCSTAT1bits_t OSCSTAT1bits __at(0x91C);

# 12143
extern volatile unsigned char OSCEN __at(0x91D);

asm("OSCEN equ 091Dh");


typedef union {
struct {
unsigned :2;
unsigned ADOEN :1;
unsigned SOSCEN :1;
unsigned LFOEN :1;
unsigned :1;
unsigned HFOEN :1;
unsigned EXTOEN :1;
};
} OSCENbits_t;
extern volatile OSCENbits_t OSCENbits __at(0x91D);

# 12189
extern volatile unsigned char OSCTUNE __at(0x91E);

asm("OSCTUNE equ 091Eh");


typedef union {
struct {
unsigned HFTUN :6;
};
struct {
unsigned HFTUN0 :1;
unsigned HFTUN1 :1;
unsigned HFTUN2 :1;
unsigned HFTUN3 :1;
unsigned HFTUN4 :1;
unsigned HFTUN5 :1;
};
} OSCTUNEbits_t;
extern volatile OSCTUNEbits_t OSCTUNEbits __at(0x91E);

# 12247
extern volatile unsigned char OSCFRQ __at(0x91F);

asm("OSCFRQ equ 091Fh");


typedef union {
struct {
unsigned HFFRQ :4;
};
struct {
unsigned HFFRQ0 :1;
unsigned HFFRQ1 :1;
unsigned HFFRQ2 :1;
unsigned HFFRQ3 :1;
};
} OSCFRQbits_t;
extern volatile OSCFRQbits_t OSCFRQbits __at(0x91F);

# 12293
extern volatile unsigned char PPSLOCK __at(0xE0F);

asm("PPSLOCK equ 0E0Fh");


typedef union {
struct {
unsigned PPSLOCKED :1;
};
} PPSLOCKbits_t;
extern volatile PPSLOCKbits_t PPSLOCKbits __at(0xE0F);

# 12313
extern volatile unsigned char INTPPS __at(0xE10);

asm("INTPPS equ 0E10h");


typedef union {
struct {
unsigned INTPPS :5;
};
struct {
unsigned INTPPS0 :1;
unsigned INTPPS1 :1;
unsigned INTPPS2 :1;
unsigned INTPPS3 :1;
unsigned INTPPS4 :1;
};
} INTPPSbits_t;
extern volatile INTPPSbits_t INTPPSbits __at(0xE10);

# 12365
extern volatile unsigned char T0CKIPPS __at(0xE11);

asm("T0CKIPPS equ 0E11h");


typedef union {
struct {
unsigned T0CKIPPS :5;
};
struct {
unsigned T0CKIPPS0 :1;
unsigned T0CKIPPS1 :1;
unsigned T0CKIPPS2 :1;
unsigned T0CKIPPS3 :1;
unsigned T0CKIPPS4 :1;
};
} T0CKIPPSbits_t;
extern volatile T0CKIPPSbits_t T0CKIPPSbits __at(0xE11);

# 12417
extern volatile unsigned char T1CKIPPS __at(0xE12);

asm("T1CKIPPS equ 0E12h");


typedef union {
struct {
unsigned T1CKIPPS :5;
};
struct {
unsigned T1CKIPPS0 :1;
unsigned T1CKIPPS1 :1;
unsigned T1CKIPPS2 :1;
unsigned T1CKIPPS3 :1;
unsigned T1CKIPPS4 :1;
};
} T1CKIPPSbits_t;
extern volatile T1CKIPPSbits_t T1CKIPPSbits __at(0xE12);

# 12469
extern volatile unsigned char T1GPPS __at(0xE13);

asm("T1GPPS equ 0E13h");


typedef union {
struct {
unsigned T1GPPS :5;
};
struct {
unsigned T1GPPS0 :1;
unsigned T1GPPS1 :1;
unsigned T1GPPS2 :1;
unsigned T1GPPS3 :1;
unsigned T1GPPS4 :1;
};
} T1GPPSbits_t;
extern volatile T1GPPSbits_t T1GPPSbits __at(0xE13);

# 12521
extern volatile unsigned char CCP1PPS __at(0xE14);

asm("CCP1PPS equ 0E14h");


typedef union {
struct {
unsigned CCP1PPS :5;
};
struct {
unsigned CCP1PPS0 :1;
unsigned CCP1PPS1 :1;
unsigned CCP1PPS2 :1;
unsigned CCP1PPS3 :1;
unsigned CCP1PPS4 :1;
};
} CCP1PPSbits_t;
extern volatile CCP1PPSbits_t CCP1PPSbits __at(0xE14);

# 12573
extern volatile unsigned char CCP2PPS __at(0xE15);

asm("CCP2PPS equ 0E15h");


typedef union {
struct {
unsigned CCP2PPS :5;
};
struct {
unsigned CCP2PPS0 :1;
unsigned CCP2PPS1 :1;
unsigned CCP2PPS2 :1;
unsigned CCP2PPS3 :1;
unsigned CCP2PPS4 :1;
};
} CCP2PPSbits_t;
extern volatile CCP2PPSbits_t CCP2PPSbits __at(0xE15);

# 12625
extern volatile unsigned char CCP3PPS __at(0xE16);

asm("CCP3PPS equ 0E16h");


typedef union {
struct {
unsigned CCP3PPS :5;
};
struct {
unsigned CCP3PPS0 :1;
unsigned CCP3PPS1 :1;
unsigned CCP3PPS2 :1;
unsigned CCP3PPS3 :1;
unsigned CCP3PPS4 :1;
};
} CCP3PPSbits_t;
extern volatile CCP3PPSbits_t CCP3PPSbits __at(0xE16);

# 12677
extern volatile unsigned char CCP4PPS __at(0xE17);

asm("CCP4PPS equ 0E17h");


typedef union {
struct {
unsigned CCP4PPS :5;
};
struct {
unsigned CCP4PPS0 :1;
unsigned CCP4PPS1 :1;
unsigned CCP4PPS2 :1;
unsigned CCP4PPS3 :1;
unsigned CCP4PPS4 :1;
};
} CCP4PPSbits_t;
extern volatile CCP4PPSbits_t CCP4PPSbits __at(0xE17);

# 12729
extern volatile unsigned char CWG1PPS __at(0xE18);

asm("CWG1PPS equ 0E18h");


typedef union {
struct {
unsigned CWG1PPS :5;
};
struct {
unsigned CWG1PPS0 :1;
unsigned CWG1PPS1 :1;
unsigned CWG1PPS2 :1;
unsigned CWG1PPS3 :1;
unsigned CWG1PPS4 :1;
};
} CWG1PPSbits_t;
extern volatile CWG1PPSbits_t CWG1PPSbits __at(0xE18);

# 12781
extern volatile unsigned char CWG2PPS __at(0xE19);

asm("CWG2PPS equ 0E19h");


typedef union {
struct {
unsigned CWG2PPS :5;
};
struct {
unsigned CWG2PPS0 :1;
unsigned CWG2PPS1 :1;
unsigned CWG2PPS2 :1;
unsigned CWG2PPS3 :1;
unsigned CWG2PPS4 :1;
};
} CWG2PPSbits_t;
extern volatile CWG2PPSbits_t CWG2PPSbits __at(0xE19);

# 12833
extern volatile unsigned char MDCIN1PPS __at(0xE1A);

asm("MDCIN1PPS equ 0E1Ah");


typedef union {
struct {
unsigned MDCIN1PPS :5;
};
struct {
unsigned MDCIN1PPS0 :1;
unsigned MDCIN1PPS1 :1;
unsigned MDCIN1PPS2 :1;
unsigned MDCIN1PPS3 :1;
unsigned MDCIN1PPS4 :1;
};
} MDCIN1PPSbits_t;
extern volatile MDCIN1PPSbits_t MDCIN1PPSbits __at(0xE1A);

# 12885
extern volatile unsigned char MDCIN2PPS __at(0xE1B);

asm("MDCIN2PPS equ 0E1Bh");


typedef union {
struct {
unsigned MDCIN2PPS :5;
};
struct {
unsigned MDCIN2PPS0 :1;
unsigned MDCIN2PPS1 :1;
unsigned MDCIN2PPS2 :1;
unsigned MDCIN2PPS3 :1;
unsigned MDCIN2PPS4 :1;
};
} MDCIN2PPSbits_t;
extern volatile MDCIN2PPSbits_t MDCIN2PPSbits __at(0xE1B);

# 12937
extern volatile unsigned char MDMINPPS __at(0xE1C);

asm("MDMINPPS equ 0E1Ch");


typedef union {
struct {
unsigned MDMINPPS :5;
};
struct {
unsigned MDMINPPS0 :1;
unsigned MDMINPPS1 :1;
unsigned MDMINPPS2 :1;
unsigned MDMINPPS3 :1;
unsigned MDMINPPS4 :1;
};
} MDMINPPSbits_t;
extern volatile MDMINPPSbits_t MDMINPPSbits __at(0xE1C);

# 12989
extern volatile unsigned char SSP2CLKPPS __at(0xE1D);

asm("SSP2CLKPPS equ 0E1Dh");


typedef union {
struct {
unsigned SSP2CLKPPS :5;
};
struct {
unsigned SSP2CLKPPS0 :1;
unsigned SSP2CLKPPS1 :1;
unsigned SSP2CLKPPS2 :1;
unsigned SSP2CLKPPS3 :1;
unsigned SSP2CLKPPS4 :1;
};
} SSP2CLKPPSbits_t;
extern volatile SSP2CLKPPSbits_t SSP2CLKPPSbits __at(0xE1D);

# 13041
extern volatile unsigned char SSP2DATPPS __at(0xE1E);

asm("SSP2DATPPS equ 0E1Eh");


typedef union {
struct {
unsigned SSP2DATPPS :5;
};
struct {
unsigned SSP2DATPPS0 :1;
unsigned SSP2DATPPS1 :1;
unsigned SSP2DATPPS2 :1;
unsigned SSP2DATPPS3 :1;
unsigned SSP2DATPPS4 :1;
};
} SSP2DATPPSbits_t;
extern volatile SSP2DATPPSbits_t SSP2DATPPSbits __at(0xE1E);

# 13093
extern volatile unsigned char SSP2SSPPS __at(0xE1F);

asm("SSP2SSPPS equ 0E1Fh");


typedef union {
struct {
unsigned SSP2SSPPS :5;
};
struct {
unsigned SSP2SSPPS0 :1;
unsigned SSP2SSPPS1 :1;
unsigned SSP2SSPPS2 :1;
unsigned SSP2SSPPS3 :1;
unsigned SSP2SSPPS4 :1;
};
} SSP2SSPPSbits_t;
extern volatile SSP2SSPPSbits_t SSP2SSPPSbits __at(0xE1F);

# 13145
extern volatile unsigned char SSP1CLKPPS __at(0xE20);

asm("SSP1CLKPPS equ 0E20h");


typedef union {
struct {
unsigned SSP1CLKPPS :5;
};
struct {
unsigned SSP1CLKPPS0 :1;
unsigned SSP1CLKPPS1 :1;
unsigned SSP1CLKPPS2 :1;
unsigned SSP1CLKPPS3 :1;
unsigned SSP1CLKPPS4 :1;
};
} SSP1CLKPPSbits_t;
extern volatile SSP1CLKPPSbits_t SSP1CLKPPSbits __at(0xE20);

# 13197
extern volatile unsigned char SSP1DATPPS __at(0xE21);

asm("SSP1DATPPS equ 0E21h");


typedef union {
struct {
unsigned SSP1DATPPS :5;
};
struct {
unsigned SSP1DATPPS0 :1;
unsigned SSP1DATPPS1 :1;
unsigned SSP1DATPPS2 :1;
unsigned SSP1DATPPS3 :1;
unsigned SSP1DATPPS4 :1;
};
} SSP1DATPPSbits_t;
extern volatile SSP1DATPPSbits_t SSP1DATPPSbits __at(0xE21);

# 13249
extern volatile unsigned char SSP1SSPPS __at(0xE22);

asm("SSP1SSPPS equ 0E22h");


typedef union {
struct {
unsigned SSP1SSPPS :5;
};
struct {
unsigned SSP1SSPPS0 :1;
unsigned SSP1SSPPS1 :1;
unsigned SSP1SSPPS2 :1;
unsigned SSP1SSPPS3 :1;
unsigned SSP1SSPPS4 :1;
};
} SSP1SSPPSbits_t;
extern volatile SSP1SSPPSbits_t SSP1SSPPSbits __at(0xE22);

# 13301
extern volatile unsigned char RXPPS __at(0xE24);

asm("RXPPS equ 0E24h");


typedef union {
struct {
unsigned RXPPS :5;
};
struct {
unsigned RXDTPPS0 :1;
unsigned RXDTPPS1 :1;
unsigned RXDTPPS2 :1;
unsigned RXDTPPS3 :1;
unsigned RXDTPPS4 :1;
};
} RXPPSbits_t;
extern volatile RXPPSbits_t RXPPSbits __at(0xE24);

# 13353
extern volatile unsigned char TXPPS __at(0xE25);

asm("TXPPS equ 0E25h");


typedef union {
struct {
unsigned TXPPS :5;
};
struct {
unsigned TXCKPPS0 :1;
unsigned TXCKPPS1 :1;
unsigned TXCKPPS2 :1;
unsigned TXCKPPS3 :1;
unsigned TXCKPPS4 :1;
};
} TXPPSbits_t;
extern volatile TXPPSbits_t TXPPSbits __at(0xE25);

# 13405
extern volatile unsigned char CLCIN0PPS __at(0xE28);

asm("CLCIN0PPS equ 0E28h");


typedef union {
struct {
unsigned CLCIN0PPS :5;
};
struct {
unsigned CLCIN0PPS0 :1;
unsigned CLCIN0PPS1 :1;
unsigned CLCIN0PPS2 :1;
unsigned CLCIN0PPS3 :1;
unsigned CLCIN0PPS4 :1;
};
} CLCIN0PPSbits_t;
extern volatile CLCIN0PPSbits_t CLCIN0PPSbits __at(0xE28);

# 13457
extern volatile unsigned char CLCIN1PPS __at(0xE29);

asm("CLCIN1PPS equ 0E29h");


typedef union {
struct {
unsigned CLCIN1PPS :5;
};
struct {
unsigned CLCIN1PPS0 :1;
unsigned CLCIN1PPS1 :1;
unsigned CLCIN1PPS2 :1;
unsigned CLCIN1PPS3 :1;
unsigned CLCIN1PPS4 :1;
};
} CLCIN1PPSbits_t;
extern volatile CLCIN1PPSbits_t CLCIN1PPSbits __at(0xE29);

# 13509
extern volatile unsigned char CLCIN2PPS __at(0xE2A);

asm("CLCIN2PPS equ 0E2Ah");


typedef union {
struct {
unsigned CLCIN2PPS :5;
};
struct {
unsigned CLCIN2PPS0 :1;
unsigned CLCIN2PPS1 :1;
unsigned CLCIN2PPS2 :1;
unsigned CLCIN2PPS3 :1;
unsigned CLCIN2PPS4 :1;
};
} CLCIN2PPSbits_t;
extern volatile CLCIN2PPSbits_t CLCIN2PPSbits __at(0xE2A);

# 13561
extern volatile unsigned char CLCIN3PPS __at(0xE2B);

asm("CLCIN3PPS equ 0E2Bh");


typedef union {
struct {
unsigned CLCIN3PPS :5;
};
struct {
unsigned CLCIN3PPS0 :1;
unsigned CLCIN3PPS1 :1;
unsigned CLCIN3PPS2 :1;
unsigned CLCIN3PPS3 :1;
unsigned CLCIN3PPS4 :1;
};
} CLCIN3PPSbits_t;
extern volatile CLCIN3PPSbits_t CLCIN3PPSbits __at(0xE2B);

# 13613
extern volatile unsigned char T3CKIPPS __at(0xE2C);

asm("T3CKIPPS equ 0E2Ch");


typedef union {
struct {
unsigned T3CKIPPS :5;
};
} T3CKIPPSbits_t;
extern volatile T3CKIPPSbits_t T3CKIPPSbits __at(0xE2C);

# 13633
extern volatile unsigned char T3GPPS __at(0xE2D);

asm("T3GPPS equ 0E2Dh");


typedef union {
struct {
unsigned T3GPPS :5;
};
} T3GPPSbits_t;
extern volatile T3GPPSbits_t T3GPPSbits __at(0xE2D);

# 13653
extern volatile unsigned char T5CKIPPS __at(0xE2E);

asm("T5CKIPPS equ 0E2Eh");


typedef union {
struct {
unsigned T5CKIPPS :5;
};
} T5CKIPPSbits_t;
extern volatile T5CKIPPSbits_t T5CKIPPSbits __at(0xE2E);

# 13673
extern volatile unsigned char T5GPPS __at(0xE2F);

asm("T5GPPS equ 0E2Fh");


typedef union {
struct {
unsigned T5GPPS :5;
};
} T5GPPSbits_t;
extern volatile T5GPPSbits_t T5GPPSbits __at(0xE2F);

# 13693
extern volatile unsigned char RA0PPS __at(0xE90);

asm("RA0PPS equ 0E90h");


typedef union {
struct {
unsigned RA0PPS :5;
};
struct {
unsigned RA0PPS0 :1;
unsigned RA0PPS1 :1;
unsigned RA0PPS2 :1;
unsigned RA0PPS3 :1;
unsigned RA0PPS4 :1;
};
} RA0PPSbits_t;
extern volatile RA0PPSbits_t RA0PPSbits __at(0xE90);

# 13745
extern volatile unsigned char RA1PPS __at(0xE91);

asm("RA1PPS equ 0E91h");


typedef union {
struct {
unsigned RA1PPS :5;
};
struct {
unsigned RA1PPS0 :1;
unsigned RA1PPS1 :1;
unsigned RA1PPS2 :1;
unsigned RA1PPS3 :1;
unsigned RA1PPS4 :1;
};
} RA1PPSbits_t;
extern volatile RA1PPSbits_t RA1PPSbits __at(0xE91);

# 13797
extern volatile unsigned char RA2PPS __at(0xE92);

asm("RA2PPS equ 0E92h");


typedef union {
struct {
unsigned RA2PPS :5;
};
struct {
unsigned RA2PPS0 :1;
unsigned RA2PPS1 :1;
unsigned RA2PPS2 :1;
unsigned RA2PPS3 :1;
unsigned RA2PPS4 :1;
};
} RA2PPSbits_t;
extern volatile RA2PPSbits_t RA2PPSbits __at(0xE92);

# 13849
extern volatile unsigned char RA4PPS __at(0xE94);

asm("RA4PPS equ 0E94h");


typedef union {
struct {
unsigned RA4PPS :5;
};
struct {
unsigned RA4PPS0 :1;
unsigned RA4PPS1 :1;
unsigned RA4PPS2 :1;
unsigned RA4PPS3 :1;
unsigned RA4PPS4 :1;
};
} RA4PPSbits_t;
extern volatile RA4PPSbits_t RA4PPSbits __at(0xE94);

# 13901
extern volatile unsigned char RA5PPS __at(0xE95);

asm("RA5PPS equ 0E95h");


typedef union {
struct {
unsigned RA5PPS :5;
};
struct {
unsigned RA5PPS0 :1;
unsigned RA5PPS1 :1;
unsigned RA5PPS2 :1;
unsigned RA5PPS3 :1;
unsigned RA5PPS4 :1;
};
} RA5PPSbits_t;
extern volatile RA5PPSbits_t RA5PPSbits __at(0xE95);

# 13953
extern volatile unsigned char RC0PPS __at(0xEA0);

asm("RC0PPS equ 0EA0h");


typedef union {
struct {
unsigned RC0PPS :5;
};
struct {
unsigned RC0PPS0 :1;
unsigned RC0PPS1 :1;
unsigned RC0PPS2 :1;
unsigned RC0PPS3 :1;
unsigned RC0PPS4 :1;
};
} RC0PPSbits_t;
extern volatile RC0PPSbits_t RC0PPSbits __at(0xEA0);

# 14005
extern volatile unsigned char RC1PPS __at(0xEA1);

asm("RC1PPS equ 0EA1h");


typedef union {
struct {
unsigned RC1PPS :5;
};
struct {
unsigned RC1PPS0 :1;
unsigned RC1PPS1 :1;
unsigned RC1PPS2 :1;
unsigned RC1PPS3 :1;
unsigned RC1PPS4 :1;
};
} RC1PPSbits_t;
extern volatile RC1PPSbits_t RC1PPSbits __at(0xEA1);

# 14057
extern volatile unsigned char RC2PPS __at(0xEA2);

asm("RC2PPS equ 0EA2h");


typedef union {
struct {
unsigned RC2PPS :5;
};
struct {
unsigned RC2PPS0 :1;
unsigned RC2PPS1 :1;
unsigned RC2PPS2 :1;
unsigned RC2PPS3 :1;
unsigned RC2PPS4 :1;
};
} RC2PPSbits_t;
extern volatile RC2PPSbits_t RC2PPSbits __at(0xEA2);

# 14109
extern volatile unsigned char RC3PPS __at(0xEA3);

asm("RC3PPS equ 0EA3h");


typedef union {
struct {
unsigned RC3PPS :5;
};
struct {
unsigned RC3PPS0 :1;
unsigned RC3PPS1 :1;
unsigned RC3PPS2 :1;
unsigned RC3PPS3 :1;
unsigned RC3PPS4 :1;
};
} RC3PPSbits_t;
extern volatile RC3PPSbits_t RC3PPSbits __at(0xEA3);

# 14161
extern volatile unsigned char RC4PPS __at(0xEA4);

asm("RC4PPS equ 0EA4h");


typedef union {
struct {
unsigned RC4PPS :5;
};
struct {
unsigned RC4PPS0 :1;
unsigned RC4PPS1 :1;
unsigned RC4PPS2 :1;
unsigned RC4PPS3 :1;
unsigned RC4PPS4 :1;
};
} RC4PPSbits_t;
extern volatile RC4PPSbits_t RC4PPSbits __at(0xEA4);

# 14213
extern volatile unsigned char RC5PPS __at(0xEA5);

asm("RC5PPS equ 0EA5h");


typedef union {
struct {
unsigned RC5PPS :5;
};
struct {
unsigned RC5PPS0 :1;
unsigned RC5PPS1 :1;
unsigned RC5PPS2 :1;
unsigned RC5PPS3 :1;
unsigned RC5PPS4 :1;
};
} RC5PPSbits_t;
extern volatile RC5PPSbits_t RC5PPSbits __at(0xEA5);

# 14265
extern volatile unsigned char CLCDATA __at(0xF0F);

asm("CLCDATA equ 0F0Fh");


typedef union {
struct {
unsigned MLC1OUT :1;
unsigned MLC2OUT :1;
unsigned MLC3OUT :1;
unsigned MLC4OUT :1;
};
} CLCDATAbits_t;
extern volatile CLCDATAbits_t CLCDATAbits __at(0xF0F);

# 14303
extern volatile unsigned char CLC1CON __at(0xF10);

asm("CLC1CON equ 0F10h");


typedef union {
struct {
unsigned LC1MODE :3;
unsigned LC1INTN :1;
unsigned LC1INTP :1;
unsigned LC1OUT :1;
unsigned :1;
unsigned LC1EN :1;
};
struct {
unsigned LC1MODE0 :1;
unsigned LC1MODE1 :1;
unsigned LC1MODE2 :1;
};
struct {
unsigned MODE :3;
unsigned INTN :1;
unsigned INTP :1;
unsigned OUT :1;
unsigned :1;
unsigned EN :1;
};
struct {
unsigned MODE0 :1;
unsigned MODE1 :1;
unsigned MODE2 :1;
};
} CLC1CONbits_t;
extern volatile CLC1CONbits_t CLC1CONbits __at(0xF10);

# 14421
extern volatile unsigned char CLC1POL __at(0xF11);

asm("CLC1POL equ 0F11h");


typedef union {
struct {
unsigned LC1G1POL :1;
unsigned LC1G2POL :1;
unsigned LC1G3POL :1;
unsigned LC1G4POL :1;
unsigned :3;
unsigned LC1POL :1;
};
struct {
unsigned G1POL :1;
unsigned G2POL :1;
unsigned G3POL :1;
unsigned G4POL :1;
unsigned :3;
unsigned POL :1;
};
} CLC1POLbits_t;
extern volatile CLC1POLbits_t CLC1POLbits __at(0xF11);

# 14499
extern volatile unsigned char CLC1SEL0 __at(0xF12);

asm("CLC1SEL0 equ 0F12h");


typedef union {
struct {
unsigned LC1D1S0 :1;
unsigned LC1D1S1 :1;
unsigned LC1D1S2 :1;
unsigned LC1D1S3 :1;
unsigned LC1D1S4 :1;
unsigned LC1D1S5 :1;
};
struct {
unsigned LC1D1S :8;
};
struct {
unsigned D1S :8;
};
struct {
unsigned D1S0 :1;
unsigned D1S1 :1;
unsigned D1S2 :1;
unsigned D1S3 :1;
unsigned D1S4 :1;
unsigned D1S5 :1;
};
} CLC1SEL0bits_t;
extern volatile CLC1SEL0bits_t CLC1SEL0bits __at(0xF12);

# 14603
extern volatile unsigned char CLC1SEL1 __at(0xF13);

asm("CLC1SEL1 equ 0F13h");


typedef union {
struct {
unsigned LC1D2S0 :1;
unsigned LC1D2S1 :1;
unsigned LC1D2S2 :1;
unsigned LC1D2S3 :1;
unsigned LC1D2S4 :1;
unsigned LC1D2S5 :1;
};
struct {
unsigned LC1D2S :8;
};
struct {
unsigned D2S :8;
};
struct {
unsigned D2S0 :1;
unsigned D2S1 :1;
unsigned D2S2 :1;
unsigned D2S3 :1;
unsigned D2S4 :1;
unsigned D2S5 :1;
};
} CLC1SEL1bits_t;
extern volatile CLC1SEL1bits_t CLC1SEL1bits __at(0xF13);

# 14707
extern volatile unsigned char CLC1SEL2 __at(0xF14);

asm("CLC1SEL2 equ 0F14h");


typedef union {
struct {
unsigned LC1D3S0 :1;
unsigned LC1D3S1 :1;
unsigned LC1D3S2 :1;
unsigned LC1D3S3 :1;
unsigned LC1D3S4 :1;
unsigned LC1D3S5 :1;
};
struct {
unsigned LC1D3S :8;
};
struct {
unsigned D3S :8;
};
struct {
unsigned D3S0 :1;
unsigned D3S1 :1;
unsigned D3S2 :1;
unsigned D3S3 :1;
unsigned D3S4 :1;
unsigned D3S5 :1;
};
} CLC1SEL2bits_t;
extern volatile CLC1SEL2bits_t CLC1SEL2bits __at(0xF14);

# 14811
extern volatile unsigned char CLC1SEL3 __at(0xF15);

asm("CLC1SEL3 equ 0F15h");


typedef union {
struct {
unsigned LC1D4S0 :1;
unsigned LC1D4S1 :1;
unsigned LC1D4S2 :1;
unsigned LC1D4S3 :1;
unsigned LC1D4S4 :1;
unsigned LC1D4S5 :1;
};
struct {
unsigned LC1D4S :8;
};
struct {
unsigned D4S :8;
};
struct {
unsigned D4S0 :1;
unsigned D4S1 :1;
unsigned D4S2 :1;
unsigned D4S3 :1;
unsigned D4S4 :1;
unsigned D4S5 :1;
};
} CLC1SEL3bits_t;
extern volatile CLC1SEL3bits_t CLC1SEL3bits __at(0xF15);

# 14915
extern volatile unsigned char CLC1GLS0 __at(0xF16);

asm("CLC1GLS0 equ 0F16h");


typedef union {
struct {
unsigned LC1G1D1N :1;
unsigned LC1G1D1T :1;
unsigned LC1G1D2N :1;
unsigned LC1G1D2T :1;
unsigned LC1G1D3N :1;
unsigned LC1G1D3T :1;
unsigned LC1G1D4N :1;
unsigned LC1G1D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC1GLS0bits_t;
extern volatile CLC1GLS0bits_t CLC1GLS0bits __at(0xF16);

# 15027
extern volatile unsigned char CLC1GLS1 __at(0xF17);

asm("CLC1GLS1 equ 0F17h");


typedef union {
struct {
unsigned LC1G2D1N :1;
unsigned LC1G2D1T :1;
unsigned LC1G2D2N :1;
unsigned LC1G2D2T :1;
unsigned LC1G2D3N :1;
unsigned LC1G2D3T :1;
unsigned LC1G2D4N :1;
unsigned LC1G2D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC1GLS1bits_t;
extern volatile CLC1GLS1bits_t CLC1GLS1bits __at(0xF17);

# 15139
extern volatile unsigned char CLC1GLS2 __at(0xF18);

asm("CLC1GLS2 equ 0F18h");


typedef union {
struct {
unsigned LC1G3D1N :1;
unsigned LC1G3D1T :1;
unsigned LC1G3D2N :1;
unsigned LC1G3D2T :1;
unsigned LC1G3D3N :1;
unsigned LC1G3D3T :1;
unsigned LC1G3D4N :1;
unsigned LC1G3D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC1GLS2bits_t;
extern volatile CLC1GLS2bits_t CLC1GLS2bits __at(0xF18);

# 15251
extern volatile unsigned char CLC1GLS3 __at(0xF19);

asm("CLC1GLS3 equ 0F19h");


typedef union {
struct {
unsigned LC1G4D1N :1;
unsigned LC1G4D1T :1;
unsigned LC1G4D2N :1;
unsigned LC1G4D2T :1;
unsigned LC1G4D3N :1;
unsigned LC1G4D3T :1;
unsigned LC1G4D4N :1;
unsigned LC1G4D4T :1;
};
struct {
unsigned G4D1N :1;
unsigned G4D1T :1;
unsigned G4D2N :1;
unsigned G4D2T :1;
unsigned G4D3N :1;
unsigned G4D3T :1;
unsigned G4D4N :1;
unsigned G4D4T :1;
};
} CLC1GLS3bits_t;
extern volatile CLC1GLS3bits_t CLC1GLS3bits __at(0xF19);

# 15363
extern volatile unsigned char CLC2CON __at(0xF1A);

asm("CLC2CON equ 0F1Ah");


typedef union {
struct {
unsigned LC2MODE :3;
unsigned LC2INTN :1;
unsigned LC2INTP :1;
unsigned LC2OUT :1;
unsigned :1;
unsigned LC2EN :1;
};
struct {
unsigned LC2MODE0 :1;
unsigned LC2MODE1 :1;
unsigned LC2MODE2 :1;
};
struct {
unsigned MODE :3;
unsigned INTN :1;
unsigned INTP :1;
unsigned OUT :1;
unsigned :1;
unsigned EN :1;
};
struct {
unsigned MODE0 :1;
unsigned MODE1 :1;
unsigned MODE2 :1;
};
} CLC2CONbits_t;
extern volatile CLC2CONbits_t CLC2CONbits __at(0xF1A);

# 15481
extern volatile unsigned char CLC2POL __at(0xF1B);

asm("CLC2POL equ 0F1Bh");


typedef union {
struct {
unsigned LC2G1POL :1;
unsigned LC2G2POL :1;
unsigned LC2G3POL :1;
unsigned LC2G4POL :1;
unsigned :3;
unsigned LC2POL :1;
};
struct {
unsigned G1POL :1;
unsigned G2POL :1;
unsigned G3POL :1;
unsigned G4POL :1;
unsigned :3;
unsigned POL :1;
};
} CLC2POLbits_t;
extern volatile CLC2POLbits_t CLC2POLbits __at(0xF1B);

# 15559
extern volatile unsigned char CLC2SEL0 __at(0xF1C);

asm("CLC2SEL0 equ 0F1Ch");


typedef union {
struct {
unsigned LC2D1S0 :1;
unsigned LC2D1S1 :1;
unsigned LC2D1S2 :1;
unsigned LC2D1S3 :1;
unsigned LC2D1S4 :1;
unsigned LC2D1S5 :1;
};
struct {
unsigned LC2D1S :8;
};
struct {
unsigned D1S :8;
};
struct {
unsigned D1S0 :1;
unsigned D1S1 :1;
unsigned D1S2 :1;
unsigned D1S3 :1;
unsigned D1S4 :1;
unsigned D1S5 :1;
};
} CLC2SEL0bits_t;
extern volatile CLC2SEL0bits_t CLC2SEL0bits __at(0xF1C);

# 15663
extern volatile unsigned char CLC2SEL1 __at(0xF1D);

asm("CLC2SEL1 equ 0F1Dh");


typedef union {
struct {
unsigned LC2D2S0 :1;
unsigned LC2D2S1 :1;
unsigned LC2D2S2 :1;
unsigned LC2D2S3 :1;
unsigned LC2D2S4 :1;
unsigned LC2D2S5 :1;
};
struct {
unsigned LC2D2S :8;
};
struct {
unsigned D2S :8;
};
struct {
unsigned D2S0 :1;
unsigned D2S1 :1;
unsigned D2S2 :1;
unsigned D2S3 :1;
unsigned D2S4 :1;
unsigned D2S5 :1;
};
} CLC2SEL1bits_t;
extern volatile CLC2SEL1bits_t CLC2SEL1bits __at(0xF1D);

# 15767
extern volatile unsigned char CLC2SEL2 __at(0xF1E);

asm("CLC2SEL2 equ 0F1Eh");


typedef union {
struct {
unsigned LC2D3S0 :1;
unsigned LC2D3S1 :1;
unsigned LC2D3S2 :1;
unsigned LC2D3S3 :1;
unsigned LC2D3S4 :1;
unsigned LC2D3S5 :1;
};
struct {
unsigned LC2D3S :8;
};
struct {
unsigned D3S :8;
};
struct {
unsigned D3S0 :1;
unsigned D3S1 :1;
unsigned D3S2 :1;
unsigned D3S3 :1;
unsigned D3S4 :1;
unsigned D3S5 :1;
};
} CLC2SEL2bits_t;
extern volatile CLC2SEL2bits_t CLC2SEL2bits __at(0xF1E);

# 15871
extern volatile unsigned char CLC2SEL3 __at(0xF1F);

asm("CLC2SEL3 equ 0F1Fh");


typedef union {
struct {
unsigned LC2D4S0 :1;
unsigned LC2D4S1 :1;
unsigned LC2D4S2 :1;
unsigned LC2D4S3 :1;
unsigned LC2D4S4 :1;
unsigned LC2D4S5 :1;
};
struct {
unsigned LC2D4S :8;
};
struct {
unsigned D4S :8;
};
struct {
unsigned D4S0 :1;
unsigned D4S1 :1;
unsigned D4S2 :1;
unsigned D4S3 :1;
unsigned D4S4 :1;
unsigned D4S5 :1;
};
} CLC2SEL3bits_t;
extern volatile CLC2SEL3bits_t CLC2SEL3bits __at(0xF1F);

# 15975
extern volatile unsigned char CLC2GLS0 __at(0xF20);

asm("CLC2GLS0 equ 0F20h");


typedef union {
struct {
unsigned LC2G1D1N :1;
unsigned LC2G1D1T :1;
unsigned LC2G1D2N :1;
unsigned LC2G1D2T :1;
unsigned LC2G1D3N :1;
unsigned LC2G1D3T :1;
unsigned LC2G1D4N :1;
unsigned LC2G1D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC2GLS0bits_t;
extern volatile CLC2GLS0bits_t CLC2GLS0bits __at(0xF20);

# 16087
extern volatile unsigned char CLC2GLS1 __at(0xF21);

asm("CLC2GLS1 equ 0F21h");


typedef union {
struct {
unsigned LC2G2D1N :1;
unsigned LC2G2D1T :1;
unsigned LC2G2D2N :1;
unsigned LC2G2D2T :1;
unsigned LC2G2D3N :1;
unsigned LC2G2D3T :1;
unsigned LC2G2D4N :1;
unsigned LC2G2D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC2GLS1bits_t;
extern volatile CLC2GLS1bits_t CLC2GLS1bits __at(0xF21);

# 16199
extern volatile unsigned char CLC2GLS2 __at(0xF22);

asm("CLC2GLS2 equ 0F22h");


typedef union {
struct {
unsigned LC2G3D1N :1;
unsigned LC2G3D1T :1;
unsigned LC2G3D2N :1;
unsigned LC2G3D2T :1;
unsigned LC2G3D3N :1;
unsigned LC2G3D3T :1;
unsigned LC2G3D4N :1;
unsigned LC2G3D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC2GLS2bits_t;
extern volatile CLC2GLS2bits_t CLC2GLS2bits __at(0xF22);

# 16311
extern volatile unsigned char CLC2GLS3 __at(0xF23);

asm("CLC2GLS3 equ 0F23h");


typedef union {
struct {
unsigned LC2G4D1N :1;
unsigned LC2G4D1T :1;
unsigned LC2G4D2N :1;
unsigned LC2G4D2T :1;
unsigned LC2G4D3N :1;
unsigned LC2G4D3T :1;
unsigned LC2G4D4N :1;
unsigned LC2G4D4T :1;
};
struct {
unsigned G4D1N :1;
unsigned G4D1T :1;
unsigned G4D2N :1;
unsigned G4D2T :1;
unsigned G4D3N :1;
unsigned G4D3T :1;
unsigned G4D4N :1;
unsigned G4D4T :1;
};
} CLC2GLS3bits_t;
extern volatile CLC2GLS3bits_t CLC2GLS3bits __at(0xF23);

# 16423
extern volatile unsigned char CLC3CON __at(0xF24);

asm("CLC3CON equ 0F24h");


typedef union {
struct {
unsigned LC3MODE :3;
unsigned LC3INTN :1;
unsigned LC3INTP :1;
unsigned LC3OUT :1;
unsigned :1;
unsigned LC3EN :1;
};
struct {
unsigned LC3MODE0 :1;
unsigned LC3MODE1 :1;
unsigned LC3MODE2 :1;
};
struct {
unsigned MODE :3;
unsigned INTN :1;
unsigned INTP :1;
unsigned OUT :1;
unsigned :1;
unsigned EN :1;
};
struct {
unsigned MODE0 :1;
unsigned MODE1 :1;
unsigned MODE2 :1;
};
} CLC3CONbits_t;
extern volatile CLC3CONbits_t CLC3CONbits __at(0xF24);

# 16541
extern volatile unsigned char CLC3POL __at(0xF25);

asm("CLC3POL equ 0F25h");


typedef union {
struct {
unsigned LC3G1POL :1;
unsigned LC3G2POL :1;
unsigned LC3G3POL :1;
unsigned LC3G4POL :1;
unsigned :3;
unsigned LC3POL :1;
};
struct {
unsigned G1POL :1;
unsigned G2POL :1;
unsigned G3POL :1;
unsigned G4POL :1;
unsigned :3;
unsigned POL :1;
};
} CLC3POLbits_t;
extern volatile CLC3POLbits_t CLC3POLbits __at(0xF25);

# 16619
extern volatile unsigned char CLC3SEL0 __at(0xF26);

asm("CLC3SEL0 equ 0F26h");


typedef union {
struct {
unsigned LC3D1S0 :1;
unsigned LC3D1S1 :1;
unsigned LC3D1S2 :1;
unsigned LC3D1S3 :1;
unsigned LC3D1S4 :1;
unsigned LC3D1S5 :1;
};
struct {
unsigned LC3D1S :8;
};
struct {
unsigned D1S :8;
};
struct {
unsigned D1S0 :1;
unsigned D1S1 :1;
unsigned D1S2 :1;
unsigned D1S3 :1;
unsigned D1S4 :1;
unsigned D1S5 :1;
};
} CLC3SEL0bits_t;
extern volatile CLC3SEL0bits_t CLC3SEL0bits __at(0xF26);

# 16723
extern volatile unsigned char CLC3SEL1 __at(0xF27);

asm("CLC3SEL1 equ 0F27h");


typedef union {
struct {
unsigned LC3D2S0 :1;
unsigned LC3D2S1 :1;
unsigned LC3D2S2 :1;
unsigned LC3D2S3 :1;
unsigned LC3D2S4 :1;
unsigned LC3D2S5 :1;
};
struct {
unsigned LC3D2S :8;
};
struct {
unsigned D2S :8;
};
struct {
unsigned D2S0 :1;
unsigned D2S1 :1;
unsigned D2S2 :1;
unsigned D2S3 :1;
unsigned D2S4 :1;
unsigned D2S5 :1;
};
} CLC3SEL1bits_t;
extern volatile CLC3SEL1bits_t CLC3SEL1bits __at(0xF27);

# 16827
extern volatile unsigned char CLC3SEL2 __at(0xF28);

asm("CLC3SEL2 equ 0F28h");


typedef union {
struct {
unsigned LC3D3S0 :1;
unsigned LC3D3S1 :1;
unsigned LC3D3S2 :1;
unsigned LC3D3S3 :1;
unsigned LC3D3S4 :1;
unsigned LC3D3S5 :1;
};
struct {
unsigned LC3D3S :8;
};
struct {
unsigned D3S :8;
};
struct {
unsigned D3S0 :1;
unsigned D3S1 :1;
unsigned D3S2 :1;
unsigned D3S3 :1;
unsigned D3S4 :1;
unsigned D3S5 :1;
};
} CLC3SEL2bits_t;
extern volatile CLC3SEL2bits_t CLC3SEL2bits __at(0xF28);

# 16931
extern volatile unsigned char CLC3SEL3 __at(0xF29);

asm("CLC3SEL3 equ 0F29h");


typedef union {
struct {
unsigned LC3D4S0 :1;
unsigned LC3D4S1 :1;
unsigned LC3D4S2 :1;
unsigned LC3D4S3 :1;
unsigned LC3D4S4 :1;
unsigned LC3D4S5 :1;
};
struct {
unsigned LC3D4S :8;
};
struct {
unsigned D4S :8;
};
struct {
unsigned D4S0 :1;
unsigned D4S1 :1;
unsigned D4S2 :1;
unsigned D4S3 :1;
unsigned D4S4 :1;
unsigned D4S5 :1;
};
} CLC3SEL3bits_t;
extern volatile CLC3SEL3bits_t CLC3SEL3bits __at(0xF29);

# 17035
extern volatile unsigned char CLC3GLS0 __at(0xF2A);

asm("CLC3GLS0 equ 0F2Ah");


typedef union {
struct {
unsigned LC3G1D1N :1;
unsigned LC3G1D1T :1;
unsigned LC3G1D2N :1;
unsigned LC3G1D2T :1;
unsigned LC3G1D3N :1;
unsigned LC3G1D3T :1;
unsigned LC3G1D4N :1;
unsigned LC3G1D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC3GLS0bits_t;
extern volatile CLC3GLS0bits_t CLC3GLS0bits __at(0xF2A);

# 17147
extern volatile unsigned char CLC3GLS1 __at(0xF2B);

asm("CLC3GLS1 equ 0F2Bh");


typedef union {
struct {
unsigned LC3G2D1N :1;
unsigned LC3G2D1T :1;
unsigned LC3G2D2N :1;
unsigned LC3G2D2T :1;
unsigned LC3G2D3N :1;
unsigned LC3G2D3T :1;
unsigned LC3G2D4N :1;
unsigned LC3G2D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC3GLS1bits_t;
extern volatile CLC3GLS1bits_t CLC3GLS1bits __at(0xF2B);

# 17259
extern volatile unsigned char CLC3GLS2 __at(0xF2C);

asm("CLC3GLS2 equ 0F2Ch");


typedef union {
struct {
unsigned LC3G3D1N :1;
unsigned LC3G3D1T :1;
unsigned LC3G3D2N :1;
unsigned LC3G3D2T :1;
unsigned LC3G3D3N :1;
unsigned LC3G3D3T :1;
unsigned LC3G3D4N :1;
unsigned LC3G3D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC3GLS2bits_t;
extern volatile CLC3GLS2bits_t CLC3GLS2bits __at(0xF2C);

# 17371
extern volatile unsigned char CLC3GLS3 __at(0xF2D);

asm("CLC3GLS3 equ 0F2Dh");


typedef union {
struct {
unsigned LC3G4D1N :1;
unsigned LC3G4D1T :1;
unsigned LC3G4D2N :1;
unsigned LC3G4D2T :1;
unsigned LC3G4D3N :1;
unsigned LC3G4D3T :1;
unsigned LC3G4D4N :1;
unsigned LC3G4D4T :1;
};
struct {
unsigned G4D1N :1;
unsigned G4D1T :1;
unsigned G4D2N :1;
unsigned G4D2T :1;
unsigned G4D3N :1;
unsigned G4D3T :1;
unsigned G4D4N :1;
unsigned G4D4T :1;
};
} CLC3GLS3bits_t;
extern volatile CLC3GLS3bits_t CLC3GLS3bits __at(0xF2D);

# 17483
extern volatile unsigned char CLC4CON __at(0xF2E);

asm("CLC4CON equ 0F2Eh");


typedef union {
struct {
unsigned LC4MODE :3;
unsigned LC4INTN :1;
unsigned LC4INTP :1;
unsigned LC4OUT :1;
unsigned :1;
unsigned LC4EN :1;
};
struct {
unsigned LC4MODE0 :1;
unsigned LC4MODE1 :1;
unsigned LC4MODE2 :1;
};
struct {
unsigned MODE :3;
unsigned INTN :1;
unsigned INTP :1;
unsigned OUT :1;
unsigned :1;
unsigned EN :1;
};
struct {
unsigned MODE0 :1;
unsigned MODE1 :1;
unsigned MODE2 :1;
};
} CLC4CONbits_t;
extern volatile CLC4CONbits_t CLC4CONbits __at(0xF2E);

# 17601
extern volatile unsigned char CLC4POL __at(0xF2F);

asm("CLC4POL equ 0F2Fh");


typedef union {
struct {
unsigned LC4G1POL :1;
unsigned LC4G2POL :1;
unsigned LC4G3POL :1;
unsigned LC4G4POL :1;
unsigned :3;
unsigned LC4POL :1;
};
struct {
unsigned G1POL :1;
unsigned G2POL :1;
unsigned G3POL :1;
unsigned G4POL :1;
unsigned :3;
unsigned POL :1;
};
} CLC4POLbits_t;
extern volatile CLC4POLbits_t CLC4POLbits __at(0xF2F);

# 17679
extern volatile unsigned char CLC4SEL0 __at(0xF30);

asm("CLC4SEL0 equ 0F30h");


typedef union {
struct {
unsigned LC4D1S0 :1;
unsigned LC4D1S1 :1;
unsigned LC4D1S2 :1;
unsigned LC4D1S3 :1;
unsigned LC4D1S4 :1;
unsigned LC4D1S5 :1;
};
struct {
unsigned LC4D1S :8;
};
struct {
unsigned D1S :8;
};
struct {
unsigned D1S0 :1;
unsigned D1S1 :1;
unsigned D1S2 :1;
unsigned D1S3 :1;
unsigned D1S4 :1;
unsigned D1S5 :1;
};
} CLC4SEL0bits_t;
extern volatile CLC4SEL0bits_t CLC4SEL0bits __at(0xF30);

# 17783
extern volatile unsigned char CLC4SEL1 __at(0xF31);

asm("CLC4SEL1 equ 0F31h");


typedef union {
struct {
unsigned LC4D2S0 :1;
unsigned LC4D2S1 :1;
unsigned LC4D2S2 :1;
unsigned LC4D2S3 :1;
unsigned LC4D2S4 :1;
unsigned LC4D2S5 :1;
};
struct {
unsigned LC4D2S :8;
};
struct {
unsigned D2S :8;
};
struct {
unsigned D2S0 :1;
unsigned D2S1 :1;
unsigned D2S2 :1;
unsigned D2S3 :1;
unsigned D2S4 :1;
unsigned D2S5 :1;
};
} CLC4SEL1bits_t;
extern volatile CLC4SEL1bits_t CLC4SEL1bits __at(0xF31);

# 17887
extern volatile unsigned char CLC4SEL2 __at(0xF32);

asm("CLC4SEL2 equ 0F32h");


typedef union {
struct {
unsigned LC4D3S0 :1;
unsigned LC4D3S1 :1;
unsigned LC4D3S2 :1;
unsigned LC4D3S3 :1;
unsigned LC4D3S4 :1;
unsigned LC4D3S5 :1;
};
struct {
unsigned LC4D3S :8;
};
struct {
unsigned D3S :8;
};
struct {
unsigned D3S0 :1;
unsigned D3S1 :1;
unsigned D3S2 :1;
unsigned D3S3 :1;
unsigned D3S4 :1;
unsigned D3S5 :1;
};
} CLC4SEL2bits_t;
extern volatile CLC4SEL2bits_t CLC4SEL2bits __at(0xF32);

# 17991
extern volatile unsigned char CLC4SEL3 __at(0xF33);

asm("CLC4SEL3 equ 0F33h");


typedef union {
struct {
unsigned LC4D4S0 :1;
unsigned LC4D4S1 :1;
unsigned LC4D4S2 :1;
unsigned LC4D4S3 :1;
unsigned LC4D4S4 :1;
unsigned LC4D4S5 :1;
};
struct {
unsigned LC4D4S :8;
};
struct {
unsigned D4S :8;
};
struct {
unsigned D4S0 :1;
unsigned D4S1 :1;
unsigned D4S2 :1;
unsigned D4S3 :1;
unsigned D4S4 :1;
unsigned D4S5 :1;
};
} CLC4SEL3bits_t;
extern volatile CLC4SEL3bits_t CLC4SEL3bits __at(0xF33);

# 18095
extern volatile unsigned char CLC4GLS0 __at(0xF34);

asm("CLC4GLS0 equ 0F34h");


typedef union {
struct {
unsigned LC4G1D1N :1;
unsigned LC4G1D1T :1;
unsigned LC4G1D2N :1;
unsigned LC4G1D2T :1;
unsigned LC4G1D3N :1;
unsigned LC4G1D3T :1;
unsigned LC4G1D4N :1;
unsigned LC4G1D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC4GLS0bits_t;
extern volatile CLC4GLS0bits_t CLC4GLS0bits __at(0xF34);

# 18207
extern volatile unsigned char CLC4GLS1 __at(0xF35);

asm("CLC4GLS1 equ 0F35h");


typedef union {
struct {
unsigned LC4G2D1N :1;
unsigned LC4G2D1T :1;
unsigned LC4G2D2N :1;
unsigned LC4G2D2T :1;
unsigned LC4G2D3N :1;
unsigned LC4G2D3T :1;
unsigned LC4G2D4N :1;
unsigned LC4G2D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC4GLS1bits_t;
extern volatile CLC4GLS1bits_t CLC4GLS1bits __at(0xF35);

# 18319
extern volatile unsigned char CLC4GLS2 __at(0xF36);

asm("CLC4GLS2 equ 0F36h");


typedef union {
struct {
unsigned LC4G3D1N :1;
unsigned LC4G3D1T :1;
unsigned LC4G3D2N :1;
unsigned LC4G3D2T :1;
unsigned LC4G3D3N :1;
unsigned LC4G3D3T :1;
unsigned LC4G3D4N :1;
unsigned LC4G3D4T :1;
};
struct {
unsigned D1N :1;
unsigned D1T :1;
unsigned D2N :1;
unsigned D2T :1;
unsigned D3N :1;
unsigned D3T :1;
unsigned D4N :1;
unsigned D4T :1;
};
} CLC4GLS2bits_t;
extern volatile CLC4GLS2bits_t CLC4GLS2bits __at(0xF36);

# 18431
extern volatile unsigned char CLC4GLS3 __at(0xF37);

asm("CLC4GLS3 equ 0F37h");


typedef union {
struct {
unsigned LC4G4D1N :1;
unsigned LC4G4D1T :1;
unsigned LC4G4D2N :1;
unsigned LC4G4D2T :1;
unsigned LC4G4D3N :1;
unsigned LC4G4D3T :1;
unsigned LC4G4D4N :1;
unsigned LC4G4D4T :1;
};
struct {
unsigned G4D1N :1;
unsigned G4D1T :1;
unsigned G4D2N :1;
unsigned G4D2T :1;
unsigned G4D3N :1;
unsigned G4D3T :1;
unsigned G4D4N :1;
unsigned G4D4T :1;
};
} CLC4GLS3bits_t;
extern volatile CLC4GLS3bits_t CLC4GLS3bits __at(0xF37);

# 18543
extern volatile unsigned char STATUS_SHAD __at(0xFE4);

asm("STATUS_SHAD equ 0FE4h");


typedef union {
struct {
unsigned C_SHAD :1;
unsigned DC_SHAD :1;
unsigned Z_SHAD :1;
};
} STATUS_SHADbits_t;
extern volatile STATUS_SHADbits_t STATUS_SHADbits __at(0xFE4);

# 18575
extern volatile unsigned char WREG_SHAD __at(0xFE5);

asm("WREG_SHAD equ 0FE5h");


typedef union {
struct {
unsigned WREG_SHAD :8;
};
} WREG_SHADbits_t;
extern volatile WREG_SHADbits_t WREG_SHADbits __at(0xFE5);

# 18595
extern volatile unsigned char BSR_SHAD __at(0xFE6);

asm("BSR_SHAD equ 0FE6h");


typedef union {
struct {
unsigned BSR_SHAD :5;
};
} BSR_SHADbits_t;
extern volatile BSR_SHADbits_t BSR_SHADbits __at(0xFE6);

# 18615
extern volatile unsigned char PCLATH_SHAD __at(0xFE7);

asm("PCLATH_SHAD equ 0FE7h");


typedef union {
struct {
unsigned PCLATH_SHAD :7;
};
} PCLATH_SHADbits_t;
extern volatile PCLATH_SHADbits_t PCLATH_SHADbits __at(0xFE7);

# 18635
extern volatile unsigned char FSR0L_SHAD __at(0xFE8);

asm("FSR0L_SHAD equ 0FE8h");


typedef union {
struct {
unsigned FSR0L_SHAD :8;
};
} FSR0L_SHADbits_t;
extern volatile FSR0L_SHADbits_t FSR0L_SHADbits __at(0xFE8);

# 18655
extern volatile unsigned char FSR0H_SHAD __at(0xFE9);

asm("FSR0H_SHAD equ 0FE9h");


typedef union {
struct {
unsigned FSR0H_SHAD :8;
};
} FSR0H_SHADbits_t;
extern volatile FSR0H_SHADbits_t FSR0H_SHADbits __at(0xFE9);

# 18675
extern volatile unsigned char FSR1L_SHAD __at(0xFEA);

asm("FSR1L_SHAD equ 0FEAh");


typedef union {
struct {
unsigned FSR1L_SHAD :8;
};
} FSR1L_SHADbits_t;
extern volatile FSR1L_SHADbits_t FSR1L_SHADbits __at(0xFEA);

# 18695
extern volatile unsigned char FSR1H_SHAD __at(0xFEB);

asm("FSR1H_SHAD equ 0FEBh");


typedef union {
struct {
unsigned FSR1H_SHAD :8;
};
} FSR1H_SHADbits_t;
extern volatile FSR1H_SHADbits_t FSR1H_SHADbits __at(0xFEB);

# 18715
extern volatile unsigned char STKPTR __at(0xFED);

asm("STKPTR equ 0FEDh");


typedef union {
struct {
unsigned STKPTR :5;
};
} STKPTRbits_t;
extern volatile STKPTRbits_t STKPTRbits __at(0xFED);

# 18735
extern volatile unsigned char TOSL __at(0xFEE);

asm("TOSL equ 0FEEh");


typedef union {
struct {
unsigned TOSL :8;
};
} TOSLbits_t;
extern volatile TOSLbits_t TOSLbits __at(0xFEE);

# 18755
extern volatile unsigned char TOSH __at(0xFEF);

asm("TOSH equ 0FEFh");


typedef union {
struct {
unsigned TOSH :7;
};
} TOSHbits_t;
extern volatile TOSHbits_t TOSHbits __at(0xFEF);

# 18781
extern volatile __bit ABDEN __at(0xCF8);


extern volatile __bit ABDOVF __at(0xCFF);


extern volatile __bit ADACT0 __at(0x4F8);


extern volatile __bit ADACT1 __at(0x4F9);


extern volatile __bit ADACT2 __at(0x4FA);


extern volatile __bit ADACT3 __at(0x4FB);


extern volatile __bit ADACT4 __at(0x4FC);


extern volatile __bit ADCMD __at(0x489D);


extern volatile __bit ADCS0 __at(0x4F4);


extern volatile __bit ADCS1 __at(0x4F5);


extern volatile __bit ADCS2 __at(0x4F6);


extern volatile __bit ADDEN __at(0xCEB);


extern volatile __bit ADFM __at(0x4F7);


extern volatile __bit ADFVR0 __at(0x8B8);


extern volatile __bit ADFVR1 __at(0x8B9);


extern volatile __bit ADGO __at(0x4E9);


extern volatile __bit ADIE __at(0x48E);


extern volatile __bit ADIF __at(0x8E);


extern volatile __bit ADNREF __at(0x4F2);


extern volatile __bit ADOEN __at(0x48EA);


extern volatile __bit ADON __at(0x4E8);


extern volatile __bit ADOR __at(0x48E2);


extern volatile __bit ADPREF0 __at(0x4F0);


extern volatile __bit ADPREF1 __at(0x4F1);


extern volatile __bit ANSA0 __at(0xC60);


extern volatile __bit ANSA1 __at(0xC61);


extern volatile __bit ANSA2 __at(0xC62);


extern volatile __bit ANSA4 __at(0xC64);


extern volatile __bit ANSA5 __at(0xC65);


extern volatile __bit ANSC0 __at(0xC70);


extern volatile __bit ANSC1 __at(0xC71);


extern volatile __bit ANSC2 __at(0xC72);


extern volatile __bit ANSC3 __at(0xC73);


extern volatile __bit ANSC4 __at(0xC74);


extern volatile __bit ANSC5 __at(0xC75);


extern volatile __bit BCL1IE __at(0x48A);


extern volatile __bit BCL1IF __at(0x8A);


extern volatile __bit BCL2IE __at(0x492);


extern volatile __bit BCL2IF __at(0x92);


extern volatile __bit BORRDY __at(0x8B0);


extern volatile __bit BRG16 __at(0xCFB);


extern volatile __bit BRGH __at(0xCF2);


extern volatile __bit BSR0 __at(0x40);


extern volatile __bit BSR1 __at(0x41);


extern volatile __bit BSR2 __at(0x42);


extern volatile __bit BSR3 __at(0x43);


extern volatile __bit BSR4 __at(0x44);


extern volatile __bit C1HYS __at(0x889);


extern volatile __bit C1IE __at(0x495);


extern volatile __bit C1IF __at(0x95);


extern volatile __bit C1INTN __at(0x896);


extern volatile __bit C1INTP __at(0x897);


extern volatile __bit C1NCH0 __at(0x890);


extern volatile __bit C1NCH1 __at(0x891);


extern volatile __bit C1NCH2 __at(0x892);


extern volatile __bit C1ON __at(0x88F);


extern volatile __bit C1OUT __at(0x88E);


extern volatile __bit C1PCH0 __at(0x893);


extern volatile __bit C1PCH1 __at(0x894);


extern volatile __bit C1PCH2 __at(0x895);


extern volatile __bit C1POL __at(0x88C);


extern volatile __bit C1SP __at(0x88A);


extern volatile __bit C1SYNC __at(0x888);


extern volatile __bit C1TSEL0 __at(0x14F8);


extern volatile __bit C1TSEL1 __at(0x14F9);


extern volatile __bit C2HYS __at(0x899);


extern volatile __bit C2IE __at(0x496);


extern volatile __bit C2IF __at(0x96);


extern volatile __bit C2INTN __at(0x8A6);


extern volatile __bit C2INTP __at(0x8A7);


extern volatile __bit C2NCH0 __at(0x8A0);


extern volatile __bit C2NCH1 __at(0x8A1);


extern volatile __bit C2NCH2 __at(0x8A2);


extern volatile __bit C2ON __at(0x89F);


extern volatile __bit C2OUT __at(0x89E);


extern volatile __bit C2PCH0 __at(0x8A3);


extern volatile __bit C2PCH1 __at(0x8A4);


extern volatile __bit C2PCH2 __at(0x8A5);


extern volatile __bit C2POL __at(0x89C);


extern volatile __bit C2SP __at(0x89A);


extern volatile __bit C2SYNC __at(0x898);


extern volatile __bit C2TSEL0 __at(0x14FA);


extern volatile __bit C2TSEL1 __at(0x14FB);


extern volatile __bit C3TSEL0 __at(0x14FC);


extern volatile __bit C3TSEL1 __at(0x14FD);


extern volatile __bit C4TSEL0 __at(0x14FE);


extern volatile __bit C4TSEL1 __at(0x14FF);


extern volatile __bit CARRY __at(0x18);


extern volatile __bit CCAP0 __at(0x18A0);


extern volatile __bit CCAP1 __at(0x18A1);


extern volatile __bit CCAP2 __at(0x18A2);


extern volatile __bit CCAP3 __at(0x18A3);


extern volatile __bit CCDEN __at(0x20FF);


extern volatile __bit CCDS0 __at(0x20F8);


extern volatile __bit CCDS1 __at(0x20F9);


extern volatile __bit CCP1CTS0 __at(0x14A0);


extern volatile __bit CCP1CTS1 __at(0x14A1);


extern volatile __bit CCP1CTS2 __at(0x14A2);


extern volatile __bit CCP1CTS3 __at(0x14A3);


extern volatile __bit CCP1EN __at(0x149F);


extern volatile __bit CCP1FMT __at(0x149C);


extern volatile __bit CCP1IE __at(0x4A0);


extern volatile __bit CCP1IF __at(0xA0);


extern volatile __bit CCP1MD __at(0x48A0);


extern volatile __bit CCP1MODE0 __at(0x1498);


extern volatile __bit CCP1MODE1 __at(0x1499);


extern volatile __bit CCP1MODE2 __at(0x149A);


extern volatile __bit CCP1MODE3 __at(0x149B);


extern volatile __bit CCP1OUT __at(0x149D);


extern volatile __bit CCP1PPS0 __at(0x70A0);


extern volatile __bit CCP1PPS1 __at(0x70A1);


extern volatile __bit CCP1PPS2 __at(0x70A2);


extern volatile __bit CCP1PPS3 __at(0x70A3);


extern volatile __bit CCP1PPS4 __at(0x70A4);


extern volatile __bit CCP2CTS0 __at(0x14C0);


extern volatile __bit CCP2CTS1 __at(0x14C1);


extern volatile __bit CCP2CTS2 __at(0x14C2);


extern volatile __bit CCP2CTS3 __at(0x14C3);


extern volatile __bit CCP2EN __at(0x14BF);


extern volatile __bit CCP2FMT __at(0x14BC);


extern volatile __bit CCP2IE __at(0x4A1);


extern volatile __bit CCP2IF __at(0xA1);


extern volatile __bit CCP2MD __at(0x48A1);


extern volatile __bit CCP2MODE0 __at(0x14B8);


extern volatile __bit CCP2MODE1 __at(0x14B9);


extern volatile __bit CCP2MODE2 __at(0x14BA);


extern volatile __bit CCP2MODE3 __at(0x14BB);


extern volatile __bit CCP2OUT __at(0x14BD);


extern volatile __bit CCP2PPS0 __at(0x70A8);


extern volatile __bit CCP2PPS1 __at(0x70A9);


extern volatile __bit CCP2PPS2 __at(0x70AA);


extern volatile __bit CCP2PPS3 __at(0x70AB);


extern volatile __bit CCP2PPS4 __at(0x70AC);


extern volatile __bit CCP3EN __at(0x189F);


extern volatile __bit CCP3FMT __at(0x189C);


extern volatile __bit CCP3IE __at(0x4A2);


extern volatile __bit CCP3IF __at(0xA2);


extern volatile __bit CCP3MD __at(0x48A2);


extern volatile __bit CCP3MODE0 __at(0x1898);


extern volatile __bit CCP3MODE1 __at(0x1899);


extern volatile __bit CCP3MODE2 __at(0x189A);


extern volatile __bit CCP3MODE3 __at(0x189B);


extern volatile __bit CCP3OUT __at(0x189D);


extern volatile __bit CCP3PPS0 __at(0x70B0);


extern volatile __bit CCP3PPS1 __at(0x70B1);


extern volatile __bit CCP3PPS2 __at(0x70B2);


extern volatile __bit CCP3PPS3 __at(0x70B3);


extern volatile __bit CCP3PPS4 __at(0x70B4);


extern volatile __bit CCP4CTS0 __at(0x18C0);


extern volatile __bit CCP4CTS1 __at(0x18C1);


extern volatile __bit CCP4CTS2 __at(0x18C2);


extern volatile __bit CCP4CTS3 __at(0x18C3);


extern volatile __bit CCP4EN __at(0x18BF);


extern volatile __bit CCP4FMT __at(0x18BC);


extern volatile __bit CCP4IE __at(0x4A3);


extern volatile __bit CCP4IF __at(0xA3);


extern volatile __bit CCP4MD __at(0x48A3);


extern volatile __bit CCP4MODE0 __at(0x18B8);


extern volatile __bit CCP4MODE1 __at(0x18B9);


extern volatile __bit CCP4MODE2 __at(0x18BA);


extern volatile __bit CCP4MODE3 __at(0x18BB);


extern volatile __bit CCP4OUT __at(0x18BD);


extern volatile __bit CCP4PPS0 __at(0x70B8);


extern volatile __bit CCP4PPS1 __at(0x70B9);


extern volatile __bit CCP4PPS2 __at(0x70BA);


extern volatile __bit CCP4PPS3 __at(0x70BB);


extern volatile __bit CCP4PPS4 __at(0x70BC);


extern volatile __bit CDAFVR0 __at(0x8BA);


extern volatile __bit CDAFVR1 __at(0x8BB);


extern volatile __bit CDIV0 __at(0x48D0);


extern volatile __bit CDIV1 __at(0x48D1);


extern volatile __bit CDIV2 __at(0x48D2);


extern volatile __bit CDIV3 __at(0x48D3);


extern volatile __bit CFGS __at(0x44AE);


extern volatile __bit CHS0 __at(0x4EA);


extern volatile __bit CHS1 __at(0x4EB);


extern volatile __bit CHS2 __at(0x4EC);


extern volatile __bit CHS3 __at(0x4ED);


extern volatile __bit CHS4 __at(0x4EE);


extern volatile __bit CHS5 __at(0x4EF);


extern volatile __bit CLC1IE __at(0x498);


extern volatile __bit CLC1IF __at(0x98);


extern volatile __bit CLC1MD __at(0x48B1);


extern volatile __bit CLC2IE __at(0x499);


extern volatile __bit CLC2IF __at(0x99);


extern volatile __bit CLC2MD __at(0x48B2);


extern volatile __bit CLC3IE __at(0x49A);


extern volatile __bit CLC3IF __at(0x9A);


extern volatile __bit CLC3MD __at(0x48B3);


extern volatile __bit CLC4IE __at(0x49B);


extern volatile __bit CLC4IF __at(0x9B);


extern volatile __bit CLC4MD __at(0x48B4);


extern volatile __bit CLCIN0PPS0 __at(0x7140);


extern volatile __bit CLCIN0PPS1 __at(0x7141);


extern volatile __bit CLCIN0PPS2 __at(0x7142);


extern volatile __bit CLCIN0PPS3 __at(0x7143);


extern volatile __bit CLCIN0PPS4 __at(0x7144);


extern volatile __bit CLCIN1PPS0 __at(0x7148);


extern volatile __bit CLCIN1PPS1 __at(0x7149);


extern volatile __bit CLCIN1PPS2 __at(0x714A);


extern volatile __bit CLCIN1PPS3 __at(0x714B);


extern volatile __bit CLCIN1PPS4 __at(0x714C);


extern volatile __bit CLCIN2PPS0 __at(0x7150);


extern volatile __bit CLCIN2PPS1 __at(0x7151);


extern volatile __bit CLCIN2PPS2 __at(0x7152);


extern volatile __bit CLCIN2PPS3 __at(0x7153);


extern volatile __bit CLCIN2PPS4 __at(0x7154);


extern volatile __bit CLCIN3PPS0 __at(0x7158);


extern volatile __bit CLCIN3PPS1 __at(0x7159);


extern volatile __bit CLCIN3PPS2 __at(0x715A);


extern volatile __bit CLCIN3PPS3 __at(0x715B);


extern volatile __bit CLCIN3PPS4 __at(0x715C);


extern volatile __bit CLKRDC0 __at(0x1CD3);


extern volatile __bit CLKRDC1 __at(0x1CD4);


extern volatile __bit CLKRDIV0 __at(0x1CD0);


extern volatile __bit CLKRDIV1 __at(0x1CD1);


extern volatile __bit CLKRDIV2 __at(0x1CD2);


extern volatile __bit CLKREN __at(0x1CD7);


extern volatile __bit CLKRMD __at(0x4889);


extern volatile __bit CMP1MD __at(0x4899);


extern volatile __bit CMP2MD __at(0x489A);


extern volatile __bit COSC0 __at(0x48D4);


extern volatile __bit COSC1 __at(0x48D5);


extern volatile __bit COSC2 __at(0x48D6);


extern volatile __bit CREN __at(0xCEC);


extern volatile __bit CSRC __at(0xCF7);


extern volatile __bit CSWHOLD __at(0x48DF);


extern volatile __bit CSWIE __at(0x49E);


extern volatile __bit CSWIF __at(0x9E);


extern volatile __bit CWG1CS __at(0x3488);


extern volatile __bit CWG1DAT0 __at(0x3490);


extern volatile __bit CWG1DAT1 __at(0x3491);


extern volatile __bit CWG1DAT2 __at(0x3492);


extern volatile __bit CWG1DAT3 __at(0x3493);


extern volatile __bit CWG1DBF0 __at(0x34A0);


extern volatile __bit CWG1DBF1 __at(0x34A1);


extern volatile __bit CWG1DBF2 __at(0x34A2);


extern volatile __bit CWG1DBF3 __at(0x34A3);


extern volatile __bit CWG1DBF4 __at(0x34A4);


extern volatile __bit CWG1DBF5 __at(0x34A5);


extern volatile __bit CWG1DBR0 __at(0x3498);


extern volatile __bit CWG1DBR1 __at(0x3499);


extern volatile __bit CWG1DBR2 __at(0x349A);


extern volatile __bit CWG1DBR3 __at(0x349B);


extern volatile __bit CWG1DBR4 __at(0x349C);


extern volatile __bit CWG1DBR5 __at(0x349D);


extern volatile __bit CWG1EN __at(0x34AF);


extern volatile __bit CWG1IE __at(0x4A6);


extern volatile __bit CWG1IF __at(0xA6);


extern volatile __bit CWG1IN __at(0x34B5);


extern volatile __bit CWG1LD __at(0x34AE);


extern volatile __bit CWG1LSAC0 __at(0x34BA);


extern volatile __bit CWG1LSAC1 __at(0x34BB);


extern volatile __bit CWG1LSBD0 __at(0x34BC);


extern volatile __bit CWG1LSBD1 __at(0x34BD);


extern volatile __bit CWG1MD __at(0x48A6);


extern volatile __bit CWG1MODE0 __at(0x34A8);


extern volatile __bit CWG1MODE1 __at(0x34A9);


extern volatile __bit CWG1MODE2 __at(0x34AA);


extern volatile __bit CWG1OVRA __at(0x34CC);


extern volatile __bit CWG1OVRB __at(0x34CD);


extern volatile __bit CWG1OVRC __at(0x34CE);


extern volatile __bit CWG1OVRD __at(0x34CF);


extern volatile __bit CWG1POLA __at(0x34B0);


extern volatile __bit CWG1POLB __at(0x34B1);


extern volatile __bit CWG1POLC __at(0x34B2);


extern volatile __bit CWG1POLD __at(0x34B3);


extern volatile __bit CWG1PPS0 __at(0x70C0);


extern volatile __bit CWG1PPS1 __at(0x70C1);


extern volatile __bit CWG1PPS2 __at(0x70C2);


extern volatile __bit CWG1PPS3 __at(0x70C3);


extern volatile __bit CWG1PPS4 __at(0x70C4);


extern volatile __bit CWG1REN __at(0x34BE);


extern volatile __bit CWG1SHUTDOWN __at(0x34BF);


extern volatile __bit CWG1STRA __at(0x34C8);


extern volatile __bit CWG1STRB __at(0x34C9);


extern volatile __bit CWG1STRC __at(0x34CA);


extern volatile __bit CWG1STRD __at(0x34CB);


extern volatile __bit CWG2CS __at(0x3888);


extern volatile __bit CWG2DAT0 __at(0x3890);


extern volatile __bit CWG2DAT1 __at(0x3891);


extern volatile __bit CWG2DAT2 __at(0x3892);


extern volatile __bit CWG2DAT3 __at(0x3893);


extern volatile __bit CWG2DBF0 __at(0x38A0);


extern volatile __bit CWG2DBF1 __at(0x38A1);


extern volatile __bit CWG2DBF2 __at(0x38A2);


extern volatile __bit CWG2DBF3 __at(0x38A3);


extern volatile __bit CWG2DBF4 __at(0x38A4);


extern volatile __bit CWG2DBF5 __at(0x38A5);


extern volatile __bit CWG2DBR0 __at(0x3898);


extern volatile __bit CWG2DBR1 __at(0x3899);


extern volatile __bit CWG2DBR2 __at(0x389A);


extern volatile __bit CWG2DBR3 __at(0x389B);


extern volatile __bit CWG2DBR4 __at(0x389C);


extern volatile __bit CWG2DBR5 __at(0x389D);


extern volatile __bit CWG2EN __at(0x38AF);


extern volatile __bit CWG2IE __at(0x4A7);


extern volatile __bit CWG2IF __at(0xA7);


extern volatile __bit CWG2IN __at(0x38B5);


extern volatile __bit CWG2LD __at(0x38AE);


extern volatile __bit CWG2LSAC0 __at(0x38BA);


extern volatile __bit CWG2LSAC1 __at(0x38BB);


extern volatile __bit CWG2LSBD0 __at(0x38BC);


extern volatile __bit CWG2LSBD1 __at(0x38BD);


extern volatile __bit CWG2MD __at(0x48A7);


extern volatile __bit CWG2MODE0 __at(0x38A8);


extern volatile __bit CWG2MODE1 __at(0x38A9);


extern volatile __bit CWG2MODE2 __at(0x38AA);


extern volatile __bit CWG2OVRA __at(0x38CC);


extern volatile __bit CWG2OVRB __at(0x38CD);


extern volatile __bit CWG2OVRC __at(0x38CE);


extern volatile __bit CWG2OVRD __at(0x38CF);


extern volatile __bit CWG2POLA __at(0x38B0);


extern volatile __bit CWG2POLB __at(0x38B1);


extern volatile __bit CWG2POLC __at(0x38B2);


extern volatile __bit CWG2POLD __at(0x38B3);


extern volatile __bit CWG2PPS0 __at(0x70C8);


extern volatile __bit CWG2PPS1 __at(0x70C9);


extern volatile __bit CWG2PPS2 __at(0x70CA);


extern volatile __bit CWG2PPS3 __at(0x70CB);


extern volatile __bit CWG2PPS4 __at(0x70CC);


extern volatile __bit CWG2REN __at(0x38BE);


extern volatile __bit CWG2SHUTDOWN __at(0x38BF);


extern volatile __bit CWG2STRA __at(0x38C8);


extern volatile __bit CWG2STRB __at(0x38C9);


extern volatile __bit CWG2STRC __at(0x38CA);


extern volatile __bit CWG2STRD __at(0x38CB);


extern volatile __bit C_SHAD __at(0x7F20);


extern volatile __bit DAC1EN __at(0x8C7);


extern volatile __bit DAC1NSS __at(0x8C0);


extern volatile __bit DAC1OE __at(0x8C5);


extern volatile __bit DAC1PSS0 __at(0x8C2);


extern volatile __bit DAC1PSS1 __at(0x8C3);


extern volatile __bit DAC1R0 __at(0x8C8);


extern volatile __bit DAC1R1 __at(0x8C9);


extern volatile __bit DAC1R2 __at(0x8CA);


extern volatile __bit DAC1R3 __at(0x8CB);


extern volatile __bit DAC1R4 __at(0x8CC);


extern volatile __bit DACMD __at(0x489E);


extern volatile __bit DC __at(0x19);


extern volatile __bit DC_SHAD __at(0x7F21);


extern volatile __bit DOE __at(0x48C4);


extern volatile __bit DOZE0 __at(0x48C0);


extern volatile __bit DOZE1 __at(0x48C1);


extern volatile __bit DOZE2 __at(0x48C2);


extern volatile __bit DOZEN __at(0x48C6);


extern volatile __bit DSMMD __at(0x48B0);


extern volatile __bit EXTOEN __at(0x48EF);


extern volatile __bit EXTOR __at(0x48E7);


extern volatile __bit FERR __at(0xCEA);


extern volatile __bit FREE __at(0x44AC);


extern volatile __bit FVREN __at(0x8BF);


extern volatile __bit FVRMD __at(0x488E);


extern volatile __bit FVRRDY __at(0x8BE);


extern volatile __bit G1EN __at(0x34AF);


extern volatile __bit G2EN __at(0x38AF);


extern volatile __bit GIE __at(0x5F);


extern volatile __bit GO __at(0x4E9);


extern volatile __bit GO_nDONE __at(0x4E9);


extern volatile __bit HFFRQ0 __at(0x48F8);


extern volatile __bit HFFRQ1 __at(0x48F9);


extern volatile __bit HFFRQ2 __at(0x48FA);


extern volatile __bit HFFRQ3 __at(0x48FB);


extern volatile __bit HFOEN __at(0x48EE);


extern volatile __bit HFOR __at(0x48E6);


extern volatile __bit HFTUN0 __at(0x48F0);


extern volatile __bit HFTUN1 __at(0x48F1);


extern volatile __bit HFTUN2 __at(0x48F2);


extern volatile __bit HFTUN3 __at(0x48F3);


extern volatile __bit HFTUN4 __at(0x48F4);


extern volatile __bit HFTUN5 __at(0x48F5);


extern volatile __bit IDLEN __at(0x48C7);


extern volatile __bit INLVLA0 __at(0x1C60);


extern volatile __bit INLVLA1 __at(0x1C61);


extern volatile __bit INLVLA2 __at(0x1C62);


extern volatile __bit INLVLA3 __at(0x1C63);


extern volatile __bit INLVLA4 __at(0x1C64);


extern volatile __bit INLVLA5 __at(0x1C65);


extern volatile __bit INLVLC0 __at(0x1C70);


extern volatile __bit INLVLC1 __at(0x1C71);


extern volatile __bit INLVLC2 __at(0x1C72);


extern volatile __bit INLVLC3 __at(0x1C73);


extern volatile __bit INLVLC4 __at(0x1C74);


extern volatile __bit INLVLC5 __at(0x1C75);


extern volatile __bit INTE __at(0x480);


extern volatile __bit INTEDG __at(0x58);


extern volatile __bit INTF __at(0x80);


extern volatile __bit INTPPS0 __at(0x7080);


extern volatile __bit INTPPS1 __at(0x7081);


extern volatile __bit INTPPS2 __at(0x7082);


extern volatile __bit INTPPS3 __at(0x7083);


extern volatile __bit INTPPS4 __at(0x7084);


extern volatile __bit IOCAF0 __at(0x1C98);


extern volatile __bit IOCAF1 __at(0x1C99);


extern volatile __bit IOCAF2 __at(0x1C9A);


extern volatile __bit IOCAF3 __at(0x1C9B);


extern volatile __bit IOCAF4 __at(0x1C9C);


extern volatile __bit IOCAF5 __at(0x1C9D);


extern volatile __bit IOCAN0 __at(0x1C90);


extern volatile __bit IOCAN1 __at(0x1C91);


extern volatile __bit IOCAN2 __at(0x1C92);


extern volatile __bit IOCAN3 __at(0x1C93);


extern volatile __bit IOCAN4 __at(0x1C94);


extern volatile __bit IOCAN5 __at(0x1C95);


extern volatile __bit IOCAP0 __at(0x1C88);


extern volatile __bit IOCAP1 __at(0x1C89);


extern volatile __bit IOCAP2 __at(0x1C8A);


extern volatile __bit IOCAP3 __at(0x1C8B);


extern volatile __bit IOCAP4 __at(0x1C8C);


extern volatile __bit IOCAP5 __at(0x1C8D);


extern volatile __bit IOCCF0 __at(0x1CC8);


extern volatile __bit IOCCF1 __at(0x1CC9);


extern volatile __bit IOCCF2 __at(0x1CCA);


extern volatile __bit IOCCF3 __at(0x1CCB);


extern volatile __bit IOCCF4 __at(0x1CCC);


extern volatile __bit IOCCF5 __at(0x1CCD);


extern volatile __bit IOCCN0 __at(0x1CC0);


extern volatile __bit IOCCN1 __at(0x1CC1);


extern volatile __bit IOCCN2 __at(0x1CC2);


extern volatile __bit IOCCN3 __at(0x1CC3);


extern volatile __bit IOCCN4 __at(0x1CC4);


extern volatile __bit IOCCN5 __at(0x1CC5);


extern volatile __bit IOCCP0 __at(0x1CB8);


extern volatile __bit IOCCP1 __at(0x1CB9);


extern volatile __bit IOCCP2 __at(0x1CBA);


extern volatile __bit IOCCP3 __at(0x1CBB);


extern volatile __bit IOCCP4 __at(0x1CBC);


extern volatile __bit IOCCP5 __at(0x1CBD);


extern volatile __bit IOCIE __at(0x484);


extern volatile __bit IOCIF __at(0x84);


extern volatile __bit IOCMD __at(0x4888);


extern volatile __bit LATA0 __at(0x860);


extern volatile __bit LATA1 __at(0x861);


extern volatile __bit LATA2 __at(0x862);


extern volatile __bit LATA4 __at(0x864);


extern volatile __bit LATA5 __at(0x865);


extern volatile __bit LATC0 __at(0x870);


extern volatile __bit LATC1 __at(0x871);


extern volatile __bit LATC2 __at(0x872);


extern volatile __bit LATC3 __at(0x873);


extern volatile __bit LATC4 __at(0x874);


extern volatile __bit LATC5 __at(0x875);


extern volatile __bit LC1D1S0 __at(0x7890);


extern volatile __bit LC1D1S1 __at(0x7891);


extern volatile __bit LC1D1S2 __at(0x7892);


extern volatile __bit LC1D1S3 __at(0x7893);


extern volatile __bit LC1D1S4 __at(0x7894);


extern volatile __bit LC1D1S5 __at(0x7895);


extern volatile __bit LC1D2S0 __at(0x7898);


extern volatile __bit LC1D2S1 __at(0x7899);


extern volatile __bit LC1D2S2 __at(0x789A);


extern volatile __bit LC1D2S3 __at(0x789B);


extern volatile __bit LC1D2S4 __at(0x789C);


extern volatile __bit LC1D2S5 __at(0x789D);


extern volatile __bit LC1D3S0 __at(0x78A0);


extern volatile __bit LC1D3S1 __at(0x78A1);


extern volatile __bit LC1D3S2 __at(0x78A2);


extern volatile __bit LC1D3S3 __at(0x78A3);


extern volatile __bit LC1D3S4 __at(0x78A4);


extern volatile __bit LC1D3S5 __at(0x78A5);


extern volatile __bit LC1D4S0 __at(0x78A8);


extern volatile __bit LC1D4S1 __at(0x78A9);


extern volatile __bit LC1D4S2 __at(0x78AA);


extern volatile __bit LC1D4S3 __at(0x78AB);


extern volatile __bit LC1D4S4 __at(0x78AC);


extern volatile __bit LC1D4S5 __at(0x78AD);


extern volatile __bit LC1EN __at(0x7887);


extern volatile __bit LC1G1D1N __at(0x78B0);


extern volatile __bit LC1G1D1T __at(0x78B1);


extern volatile __bit LC1G1D2N __at(0x78B2);


extern volatile __bit LC1G1D2T __at(0x78B3);


extern volatile __bit LC1G1D3N __at(0x78B4);


extern volatile __bit LC1G1D3T __at(0x78B5);


extern volatile __bit LC1G1D4N __at(0x78B6);


extern volatile __bit LC1G1D4T __at(0x78B7);


extern volatile __bit LC1G1POL __at(0x7888);


extern volatile __bit LC1G2D1N __at(0x78B8);


extern volatile __bit LC1G2D1T __at(0x78B9);


extern volatile __bit LC1G2D2N __at(0x78BA);


extern volatile __bit LC1G2D2T __at(0x78BB);


extern volatile __bit LC1G2D3N __at(0x78BC);


extern volatile __bit LC1G2D3T __at(0x78BD);


extern volatile __bit LC1G2D4N __at(0x78BE);


extern volatile __bit LC1G2D4T __at(0x78BF);


extern volatile __bit LC1G2POL __at(0x7889);


extern volatile __bit LC1G3D1N __at(0x78C0);


extern volatile __bit LC1G3D1T __at(0x78C1);


extern volatile __bit LC1G3D2N __at(0x78C2);


extern volatile __bit LC1G3D2T __at(0x78C3);


extern volatile __bit LC1G3D3N __at(0x78C4);


extern volatile __bit LC1G3D3T __at(0x78C5);


extern volatile __bit LC1G3D4N __at(0x78C6);


extern volatile __bit LC1G3D4T __at(0x78C7);


extern volatile __bit LC1G3POL __at(0x788A);


extern volatile __bit LC1G4D1N __at(0x78C8);


extern volatile __bit LC1G4D1T __at(0x78C9);


extern volatile __bit LC1G4D2N __at(0x78CA);


extern volatile __bit LC1G4D2T __at(0x78CB);


extern volatile __bit LC1G4D3N __at(0x78CC);


extern volatile __bit LC1G4D3T __at(0x78CD);


extern volatile __bit LC1G4D4N __at(0x78CE);


extern volatile __bit LC1G4D4T __at(0x78CF);


extern volatile __bit LC1G4POL __at(0x788B);


extern volatile __bit LC1INTN __at(0x7883);


extern volatile __bit LC1INTP __at(0x7884);


extern volatile __bit LC1MODE0 __at(0x7880);


extern volatile __bit LC1MODE1 __at(0x7881);


extern volatile __bit LC1MODE2 __at(0x7882);


extern volatile __bit LC1OUT __at(0x7885);


extern volatile __bit LC1POL __at(0x788F);


extern volatile __bit LC2D1S0 __at(0x78E0);


extern volatile __bit LC2D1S1 __at(0x78E1);


extern volatile __bit LC2D1S2 __at(0x78E2);


extern volatile __bit LC2D1S3 __at(0x78E3);


extern volatile __bit LC2D1S4 __at(0x78E4);


extern volatile __bit LC2D1S5 __at(0x78E5);


extern volatile __bit LC2D2S0 __at(0x78E8);


extern volatile __bit LC2D2S1 __at(0x78E9);


extern volatile __bit LC2D2S2 __at(0x78EA);


extern volatile __bit LC2D2S3 __at(0x78EB);


extern volatile __bit LC2D2S4 __at(0x78EC);


extern volatile __bit LC2D2S5 __at(0x78ED);


extern volatile __bit LC2D3S0 __at(0x78F0);


extern volatile __bit LC2D3S1 __at(0x78F1);


extern volatile __bit LC2D3S2 __at(0x78F2);


extern volatile __bit LC2D3S3 __at(0x78F3);


extern volatile __bit LC2D3S4 __at(0x78F4);


extern volatile __bit LC2D3S5 __at(0x78F5);


extern volatile __bit LC2D4S0 __at(0x78F8);


extern volatile __bit LC2D4S1 __at(0x78F9);


extern volatile __bit LC2D4S2 __at(0x78FA);


extern volatile __bit LC2D4S3 __at(0x78FB);


extern volatile __bit LC2D4S4 __at(0x78FC);


extern volatile __bit LC2D4S5 __at(0x78FD);


extern volatile __bit LC2EN __at(0x78D7);


extern volatile __bit LC2G1D1N __at(0x7900);


extern volatile __bit LC2G1D1T __at(0x7901);


extern volatile __bit LC2G1D2N __at(0x7902);


extern volatile __bit LC2G1D2T __at(0x7903);


extern volatile __bit LC2G1D3N __at(0x7904);


extern volatile __bit LC2G1D3T __at(0x7905);


extern volatile __bit LC2G1D4N __at(0x7906);


extern volatile __bit LC2G1D4T __at(0x7907);


extern volatile __bit LC2G1POL __at(0x78D8);


extern volatile __bit LC2G2D1N __at(0x7908);


extern volatile __bit LC2G2D1T __at(0x7909);


extern volatile __bit LC2G2D2N __at(0x790A);


extern volatile __bit LC2G2D2T __at(0x790B);


extern volatile __bit LC2G2D3N __at(0x790C);


extern volatile __bit LC2G2D3T __at(0x790D);


extern volatile __bit LC2G2D4N __at(0x790E);


extern volatile __bit LC2G2D4T __at(0x790F);


extern volatile __bit LC2G2POL __at(0x78D9);


extern volatile __bit LC2G3D1N __at(0x7910);


extern volatile __bit LC2G3D1T __at(0x7911);


extern volatile __bit LC2G3D2N __at(0x7912);


extern volatile __bit LC2G3D2T __at(0x7913);


extern volatile __bit LC2G3D3N __at(0x7914);


extern volatile __bit LC2G3D3T __at(0x7915);


extern volatile __bit LC2G3D4N __at(0x7916);


extern volatile __bit LC2G3D4T __at(0x7917);


extern volatile __bit LC2G3POL __at(0x78DA);


extern volatile __bit LC2G4D1N __at(0x7918);


extern volatile __bit LC2G4D1T __at(0x7919);


extern volatile __bit LC2G4D2N __at(0x791A);


extern volatile __bit LC2G4D2T __at(0x791B);


extern volatile __bit LC2G4D3N __at(0x791C);


extern volatile __bit LC2G4D3T __at(0x791D);


extern volatile __bit LC2G4D4N __at(0x791E);


extern volatile __bit LC2G4D4T __at(0x791F);


extern volatile __bit LC2G4POL __at(0x78DB);


extern volatile __bit LC2INTN __at(0x78D3);


extern volatile __bit LC2INTP __at(0x78D4);


extern volatile __bit LC2MODE0 __at(0x78D0);


extern volatile __bit LC2MODE1 __at(0x78D1);


extern volatile __bit LC2MODE2 __at(0x78D2);


extern volatile __bit LC2OUT __at(0x78D5);


extern volatile __bit LC2POL __at(0x78DF);


extern volatile __bit LC3D1S0 __at(0x7930);


extern volatile __bit LC3D1S1 __at(0x7931);


extern volatile __bit LC3D1S2 __at(0x7932);


extern volatile __bit LC3D1S3 __at(0x7933);


extern volatile __bit LC3D1S4 __at(0x7934);


extern volatile __bit LC3D1S5 __at(0x7935);


extern volatile __bit LC3D2S0 __at(0x7938);


extern volatile __bit LC3D2S1 __at(0x7939);


extern volatile __bit LC3D2S2 __at(0x793A);


extern volatile __bit LC3D2S3 __at(0x793B);


extern volatile __bit LC3D2S4 __at(0x793C);


extern volatile __bit LC3D2S5 __at(0x793D);


extern volatile __bit LC3D3S0 __at(0x7940);


extern volatile __bit LC3D3S1 __at(0x7941);


extern volatile __bit LC3D3S2 __at(0x7942);


extern volatile __bit LC3D3S3 __at(0x7943);


extern volatile __bit LC3D3S4 __at(0x7944);


extern volatile __bit LC3D3S5 __at(0x7945);


extern volatile __bit LC3D4S0 __at(0x7948);


extern volatile __bit LC3D4S1 __at(0x7949);


extern volatile __bit LC3D4S2 __at(0x794A);


extern volatile __bit LC3D4S3 __at(0x794B);


extern volatile __bit LC3D4S4 __at(0x794C);


extern volatile __bit LC3D4S5 __at(0x794D);


extern volatile __bit LC3EN __at(0x7927);


extern volatile __bit LC3G1D1N __at(0x7950);


extern volatile __bit LC3G1D1T __at(0x7951);


extern volatile __bit LC3G1D2N __at(0x7952);


extern volatile __bit LC3G1D2T __at(0x7953);


extern volatile __bit LC3G1D3N __at(0x7954);


extern volatile __bit LC3G1D3T __at(0x7955);


extern volatile __bit LC3G1D4N __at(0x7956);


extern volatile __bit LC3G1D4T __at(0x7957);


extern volatile __bit LC3G1POL __at(0x7928);


extern volatile __bit LC3G2D1N __at(0x7958);


extern volatile __bit LC3G2D1T __at(0x7959);


extern volatile __bit LC3G2D2N __at(0x795A);


extern volatile __bit LC3G2D2T __at(0x795B);


extern volatile __bit LC3G2D3N __at(0x795C);


extern volatile __bit LC3G2D3T __at(0x795D);


extern volatile __bit LC3G2D4N __at(0x795E);


extern volatile __bit LC3G2D4T __at(0x795F);


extern volatile __bit LC3G2POL __at(0x7929);


extern volatile __bit LC3G3D1N __at(0x7960);


extern volatile __bit LC3G3D1T __at(0x7961);


extern volatile __bit LC3G3D2N __at(0x7962);


extern volatile __bit LC3G3D2T __at(0x7963);


extern volatile __bit LC3G3D3N __at(0x7964);


extern volatile __bit LC3G3D3T __at(0x7965);


extern volatile __bit LC3G3D4N __at(0x7966);


extern volatile __bit LC3G3D4T __at(0x7967);


extern volatile __bit LC3G3POL __at(0x792A);


extern volatile __bit LC3G4D1N __at(0x7968);


extern volatile __bit LC3G4D1T __at(0x7969);


extern volatile __bit LC3G4D2N __at(0x796A);


extern volatile __bit LC3G4D2T __at(0x796B);


extern volatile __bit LC3G4D3N __at(0x796C);


extern volatile __bit LC3G4D3T __at(0x796D);


extern volatile __bit LC3G4D4N __at(0x796E);


extern volatile __bit LC3G4D4T __at(0x796F);


extern volatile __bit LC3G4POL __at(0x792B);


extern volatile __bit LC3INTN __at(0x7923);


extern volatile __bit LC3INTP __at(0x7924);


extern volatile __bit LC3MODE0 __at(0x7920);


extern volatile __bit LC3MODE1 __at(0x7921);


extern volatile __bit LC3MODE2 __at(0x7922);


extern volatile __bit LC3OUT __at(0x7925);


extern volatile __bit LC3POL __at(0x792F);


extern volatile __bit LC4D1S0 __at(0x7980);


extern volatile __bit LC4D1S1 __at(0x7981);


extern volatile __bit LC4D1S2 __at(0x7982);


extern volatile __bit LC4D1S3 __at(0x7983);


extern volatile __bit LC4D1S4 __at(0x7984);


extern volatile __bit LC4D1S5 __at(0x7985);


extern volatile __bit LC4D2S0 __at(0x7988);


extern volatile __bit LC4D2S1 __at(0x7989);


extern volatile __bit LC4D2S2 __at(0x798A);


extern volatile __bit LC4D2S3 __at(0x798B);


extern volatile __bit LC4D2S4 __at(0x798C);


extern volatile __bit LC4D2S5 __at(0x798D);


extern volatile __bit LC4D3S0 __at(0x7990);


extern volatile __bit LC4D3S1 __at(0x7991);


extern volatile __bit LC4D3S2 __at(0x7992);


extern volatile __bit LC4D3S3 __at(0x7993);


extern volatile __bit LC4D3S4 __at(0x7994);


extern volatile __bit LC4D3S5 __at(0x7995);


extern volatile __bit LC4D4S0 __at(0x7998);


extern volatile __bit LC4D4S1 __at(0x7999);


extern volatile __bit LC4D4S2 __at(0x799A);


extern volatile __bit LC4D4S3 __at(0x799B);


extern volatile __bit LC4D4S4 __at(0x799C);


extern volatile __bit LC4D4S5 __at(0x799D);


extern volatile __bit LC4EN __at(0x7977);


extern volatile __bit LC4G1D1N __at(0x79A0);


extern volatile __bit LC4G1D1T __at(0x79A1);


extern volatile __bit LC4G1D2N __at(0x79A2);


extern volatile __bit LC4G1D2T __at(0x79A3);


extern volatile __bit LC4G1D3N __at(0x79A4);


extern volatile __bit LC4G1D3T __at(0x79A5);


extern volatile __bit LC4G1D4N __at(0x79A6);


extern volatile __bit LC4G1D4T __at(0x79A7);


extern volatile __bit LC4G1POL __at(0x7978);


extern volatile __bit LC4G2D1N __at(0x79A8);


extern volatile __bit LC4G2D1T __at(0x79A9);


extern volatile __bit LC4G2D2N __at(0x79AA);


extern volatile __bit LC4G2D2T __at(0x79AB);


extern volatile __bit LC4G2D3N __at(0x79AC);


extern volatile __bit LC4G2D3T __at(0x79AD);


extern volatile __bit LC4G2D4N __at(0x79AE);


extern volatile __bit LC4G2D4T __at(0x79AF);


extern volatile __bit LC4G2POL __at(0x7979);


extern volatile __bit LC4G3D1N __at(0x79B0);


extern volatile __bit LC4G3D1T __at(0x79B1);


extern volatile __bit LC4G3D2N __at(0x79B2);


extern volatile __bit LC4G3D2T __at(0x79B3);


extern volatile __bit LC4G3D3N __at(0x79B4);


extern volatile __bit LC4G3D3T __at(0x79B5);


extern volatile __bit LC4G3D4N __at(0x79B6);


extern volatile __bit LC4G3D4T __at(0x79B7);


extern volatile __bit LC4G3POL __at(0x797A);


extern volatile __bit LC4G4D1N __at(0x79B8);


extern volatile __bit LC4G4D1T __at(0x79B9);


extern volatile __bit LC4G4D2N __at(0x79BA);


extern volatile __bit LC4G4D2T __at(0x79BB);


extern volatile __bit LC4G4D3N __at(0x79BC);


extern volatile __bit LC4G4D3T __at(0x79BD);


extern volatile __bit LC4G4D4N __at(0x79BE);


extern volatile __bit LC4G4D4T __at(0x79BF);


extern volatile __bit LC4G4POL __at(0x797B);


extern volatile __bit LC4INTN __at(0x7973);


extern volatile __bit LC4INTP __at(0x7974);


extern volatile __bit LC4MODE0 __at(0x7970);


extern volatile __bit LC4MODE1 __at(0x7971);


extern volatile __bit LC4MODE2 __at(0x7972);


extern volatile __bit LC4OUT __at(0x7975);


extern volatile __bit LC4POL __at(0x797F);


extern volatile __bit LFOEN __at(0x48EC);


extern volatile __bit LFOR __at(0x48E4);


extern volatile __bit LWLO __at(0x44AD);


extern volatile __bit MC1OUT __at(0x8A8);


extern volatile __bit MC2OUT __at(0x8A9);


extern volatile __bit MDBIT __at(0x1CE0);


extern volatile __bit MDCH0 __at(0x1CF0);


extern volatile __bit MDCH1 __at(0x1CF1);


extern volatile __bit MDCH2 __at(0x1CF2);


extern volatile __bit MDCH3 __at(0x1CF3);


extern volatile __bit MDCHPOL __at(0x1CF6);


extern volatile __bit MDCHSYNC __at(0x1CF5);


extern volatile __bit MDCIN1PPS0 __at(0x70D0);


extern volatile __bit MDCIN1PPS1 __at(0x70D1);


extern volatile __bit MDCIN1PPS2 __at(0x70D2);


extern volatile __bit MDCIN1PPS3 __at(0x70D3);


extern volatile __bit MDCIN1PPS4 __at(0x70D4);


extern volatile __bit MDCIN2PPS0 __at(0x70D8);


extern volatile __bit MDCIN2PPS1 __at(0x70D9);


extern volatile __bit MDCIN2PPS2 __at(0x70DA);


extern volatile __bit MDCIN2PPS3 __at(0x70DB);


extern volatile __bit MDCIN2PPS4 __at(0x70DC);


extern volatile __bit MDCL0 __at(0x1CF8);


extern volatile __bit MDCL1 __at(0x1CF9);


extern volatile __bit MDCL2 __at(0x1CFA);


extern volatile __bit MDCL3 __at(0x1CFB);


extern volatile __bit MDCLPOL __at(0x1CFE);


extern volatile __bit MDCLSYNC __at(0x1CFD);


extern volatile __bit MDEN __at(0x1CE7);


extern volatile __bit MDMINPPS0 __at(0x70E0);


extern volatile __bit MDMINPPS1 __at(0x70E1);


extern volatile __bit MDMINPPS2 __at(0x70E2);


extern volatile __bit MDMINPPS3 __at(0x70E3);


extern volatile __bit MDMINPPS4 __at(0x70E4);


extern volatile __bit MDMS0 __at(0x1CE8);


extern volatile __bit MDMS1 __at(0x1CE9);


extern volatile __bit MDMS2 __at(0x1CEA);


extern volatile __bit MDMS3 __at(0x1CEB);


extern volatile __bit MDOPOL __at(0x1CE4);


extern volatile __bit MDOUT __at(0x1CE3);


extern volatile __bit MLC1OUT __at(0x7878);


extern volatile __bit MLC2OUT __at(0x7879);


extern volatile __bit MLC3OUT __at(0x787A);


extern volatile __bit MLC4OUT __at(0x787B);


extern volatile __bit MSSP1MD __at(0x48A9);


extern volatile __bit MSSP2MD __at(0x48AA);


extern volatile __bit N1EN __at(0x24F7);


extern volatile __bit N1OUT __at(0x24F5);


extern volatile __bit N1PFM __at(0x24F0);


extern volatile __bit N1POL __at(0x24F4);


extern volatile __bit NCO1IE __at(0x490);


extern volatile __bit NCO1IF __at(0x90);


extern volatile __bit NCOMD __at(0x4897);


extern volatile __bit NDIV0 __at(0x48C8);


extern volatile __bit NDIV1 __at(0x48C9);


extern volatile __bit NDIV2 __at(0x48CA);


extern volatile __bit NDIV3 __at(0x48CB);


extern volatile __bit NOSC0 __at(0x48CC);


extern volatile __bit NOSC1 __at(0x48CD);


extern volatile __bit NOSC2 __at(0x48CE);


extern volatile __bit NOSCR __at(0x48DB);


extern volatile __bit NVMADR0 __at(0x4488);


extern volatile __bit NVMADR1 __at(0x4489);


extern volatile __bit NVMADR10 __at(0x4492);


extern volatile __bit NVMADR11 __at(0x4493);


extern volatile __bit NVMADR12 __at(0x4494);


extern volatile __bit NVMADR13 __at(0x4495);


extern volatile __bit NVMADR14 __at(0x4496);


extern volatile __bit NVMADR2 __at(0x448A);


extern volatile __bit NVMADR3 __at(0x448B);


extern volatile __bit NVMADR4 __at(0x448C);


extern volatile __bit NVMADR5 __at(0x448D);


extern volatile __bit NVMADR6 __at(0x448E);


extern volatile __bit NVMADR7 __at(0x448F);


extern volatile __bit NVMADR8 __at(0x4490);


extern volatile __bit NVMADR9 __at(0x4491);


extern volatile __bit NVMDAT0 __at(0x4498);


extern volatile __bit NVMDAT1 __at(0x4499);


extern volatile __bit NVMDAT10 __at(0x44A2);


extern volatile __bit NVMDAT11 __at(0x44A3);


extern volatile __bit NVMDAT12 __at(0x44A4);


extern volatile __bit NVMDAT13 __at(0x44A5);


extern volatile __bit NVMDAT2 __at(0x449A);


extern volatile __bit NVMDAT3 __at(0x449B);


extern volatile __bit NVMDAT4 __at(0x449C);


extern volatile __bit NVMDAT5 __at(0x449D);


extern volatile __bit NVMDAT6 __at(0x449E);


extern volatile __bit NVMDAT7 __at(0x449F);


extern volatile __bit NVMDAT8 __at(0x44A0);


extern volatile __bit NVMDAT9 __at(0x44A1);


extern volatile __bit NVMIE __at(0x494);


extern volatile __bit NVMIF __at(0x94);


extern volatile __bit NVMMD __at(0x488A);


extern volatile __bit NVMREGS __at(0x44AE);


extern volatile __bit ODCA0 __at(0x1460);


extern volatile __bit ODCA1 __at(0x1461);


extern volatile __bit ODCA2 __at(0x1462);


extern volatile __bit ODCA4 __at(0x1464);


extern volatile __bit ODCA5 __at(0x1465);


extern volatile __bit ODCC0 __at(0x1470);


extern volatile __bit ODCC1 __at(0x1471);


extern volatile __bit ODCC2 __at(0x1472);


extern volatile __bit ODCC3 __at(0x1473);


extern volatile __bit ODCC4 __at(0x1474);


extern volatile __bit ODCC5 __at(0x1475);


extern volatile __bit OERR __at(0xCE9);


extern volatile __bit ORDY __at(0x48DC);


extern volatile __bit OSFIE __at(0x49F);


extern volatile __bit OSFIF __at(0x9F);


extern volatile __bit P5TSEL0 __at(0x30F8);


extern volatile __bit P5TSEL1 __at(0x30F9);


extern volatile __bit P6TSEL0 __at(0x30FA);


extern volatile __bit P6TSEL1 __at(0x30FB);


extern volatile __bit PEIE __at(0x5E);


extern volatile __bit PLLR __at(0x48E0);


extern volatile __bit PPSLOCKED __at(0x7078);


extern volatile __bit PWM5DCH0 __at(0x30C0);


extern volatile __bit PWM5DCH1 __at(0x30C1);


extern volatile __bit PWM5DCH2 __at(0x30C2);


extern volatile __bit PWM5DCH3 __at(0x30C3);


extern volatile __bit PWM5DCH4 __at(0x30C4);


extern volatile __bit PWM5DCH5 __at(0x30C5);


extern volatile __bit PWM5DCH6 __at(0x30C6);


extern volatile __bit PWM5DCH7 __at(0x30C7);


extern volatile __bit PWM5DCL0 __at(0x30BE);


extern volatile __bit PWM5DCL1 __at(0x30BF);


extern volatile __bit PWM5EN __at(0x30CF);


extern volatile __bit PWM5MD __at(0x48A4);


extern volatile __bit PWM5OUT __at(0x30CD);


extern volatile __bit PWM5POL __at(0x30CC);


extern volatile __bit PWM6DCH0 __at(0x30D8);


extern volatile __bit PWM6DCH1 __at(0x30D9);


extern volatile __bit PWM6DCH2 __at(0x30DA);


extern volatile __bit PWM6DCH3 __at(0x30DB);


extern volatile __bit PWM6DCH4 __at(0x30DC);


extern volatile __bit PWM6DCH5 __at(0x30DD);


extern volatile __bit PWM6DCH6 __at(0x30DE);


extern volatile __bit PWM6DCH7 __at(0x30DF);


extern volatile __bit PWM6DCL0 __at(0x30D6);


extern volatile __bit PWM6DCL1 __at(0x30D7);


extern volatile __bit PWM6EN __at(0x30E7);


extern volatile __bit PWM6MD __at(0x48A5);


extern volatile __bit PWM6OUT __at(0x30E5);


extern volatile __bit PWM6POL __at(0x30E4);


extern volatile __bit RA0 __at(0x60);


extern volatile __bit RA0PPS0 __at(0x7480);


extern volatile __bit RA0PPS1 __at(0x7481);


extern volatile __bit RA0PPS2 __at(0x7482);


extern volatile __bit RA0PPS3 __at(0x7483);


extern volatile __bit RA0PPS4 __at(0x7484);


extern volatile __bit RA1 __at(0x61);


extern volatile __bit RA1PPS0 __at(0x7488);


extern volatile __bit RA1PPS1 __at(0x7489);


extern volatile __bit RA1PPS2 __at(0x748A);


extern volatile __bit RA1PPS3 __at(0x748B);


extern volatile __bit RA1PPS4 __at(0x748C);


extern volatile __bit RA2 __at(0x62);


extern volatile __bit RA2PPS0 __at(0x7490);


extern volatile __bit RA2PPS1 __at(0x7491);


extern volatile __bit RA2PPS2 __at(0x7492);


extern volatile __bit RA2PPS3 __at(0x7493);


extern volatile __bit RA2PPS4 __at(0x7494);


extern volatile __bit RA3 __at(0x63);


extern volatile __bit RA4 __at(0x64);


extern volatile __bit RA4PPS0 __at(0x74A0);


extern volatile __bit RA4PPS1 __at(0x74A1);


extern volatile __bit RA4PPS2 __at(0x74A2);


extern volatile __bit RA4PPS3 __at(0x74A3);


extern volatile __bit RA4PPS4 __at(0x74A4);


extern volatile __bit RA5 __at(0x65);


extern volatile __bit RA5PPS0 __at(0x74A8);


extern volatile __bit RA5PPS1 __at(0x74A9);


extern volatile __bit RA5PPS2 __at(0x74AA);


extern volatile __bit RA5PPS3 __at(0x74AB);


extern volatile __bit RA5PPS4 __at(0x74AC);


extern volatile __bit RC0 __at(0x70);


extern volatile __bit RC0PPS0 __at(0x7500);


extern volatile __bit RC0PPS1 __at(0x7501);


extern volatile __bit RC0PPS2 __at(0x7502);


extern volatile __bit RC0PPS3 __at(0x7503);


extern volatile __bit RC0PPS4 __at(0x7504);


extern volatile __bit RC1 __at(0x71);


extern volatile __bit RC1PPS0 __at(0x7508);


extern volatile __bit RC1PPS1 __at(0x7509);


extern volatile __bit RC1PPS2 __at(0x750A);


extern volatile __bit RC1PPS3 __at(0x750B);


extern volatile __bit RC1PPS4 __at(0x750C);


extern volatile __bit RC2 __at(0x72);


extern volatile __bit RC2PPS0 __at(0x7510);


extern volatile __bit RC2PPS1 __at(0x7511);


extern volatile __bit RC2PPS2 __at(0x7512);


extern volatile __bit RC2PPS3 __at(0x7513);


extern volatile __bit RC2PPS4 __at(0x7514);


extern volatile __bit RC3 __at(0x73);


extern volatile __bit RC3PPS0 __at(0x7518);


extern volatile __bit RC3PPS1 __at(0x7519);


extern volatile __bit RC3PPS2 __at(0x751A);


extern volatile __bit RC3PPS3 __at(0x751B);


extern volatile __bit RC3PPS4 __at(0x751C);


extern volatile __bit RC4 __at(0x74);


extern volatile __bit RC4PPS0 __at(0x7520);


extern volatile __bit RC4PPS1 __at(0x7521);


extern volatile __bit RC4PPS2 __at(0x7522);


extern volatile __bit RC4PPS3 __at(0x7523);


extern volatile __bit RC4PPS4 __at(0x7524);


extern volatile __bit RC5 __at(0x75);


extern volatile __bit RC5PPS0 __at(0x7528);


extern volatile __bit RC5PPS1 __at(0x7529);


extern volatile __bit RC5PPS2 __at(0x752A);


extern volatile __bit RC5PPS3 __at(0x752B);


extern volatile __bit RC5PPS4 __at(0x752C);


extern volatile __bit RCIDL __at(0xCFE);


extern volatile __bit RCIE __at(0x48D);


extern volatile __bit RCIF __at(0x8D);


extern volatile __bit RD __at(0x44A8);


extern volatile __bit ROI __at(0x48C5);


extern volatile __bit RX9 __at(0xCEE);


extern volatile __bit RX9D __at(0xCE8);


extern volatile __bit RXDTPPS0 __at(0x7120);


extern volatile __bit RXDTPPS1 __at(0x7121);


extern volatile __bit RXDTPPS2 __at(0x7122);


extern volatile __bit RXDTPPS3 __at(0x7123);


extern volatile __bit RXDTPPS4 __at(0x7124);


extern volatile __bit SBOREN __at(0x8B7);


extern volatile __bit SCKP __at(0xCFC);


extern volatile __bit SENDB __at(0xCF3);


extern volatile __bit SLRA0 __at(0x1860);


extern volatile __bit SLRA1 __at(0x1861);


extern volatile __bit SLRA2 __at(0x1862);


extern volatile __bit SLRA4 __at(0x1864);


extern volatile __bit SLRA5 __at(0x1865);


extern volatile __bit SLRC0 __at(0x1870);


extern volatile __bit SLRC1 __at(0x1871);


extern volatile __bit SLRC2 __at(0x1872);


extern volatile __bit SLRC3 __at(0x1873);


extern volatile __bit SLRC4 __at(0x1874);


extern volatile __bit SLRC5 __at(0x1875);


extern volatile __bit SOR __at(0x48E3);


extern volatile __bit SOSCBE __at(0x48DD);


extern volatile __bit SOSCEN __at(0x48EB);


extern volatile __bit SOSCPWR __at(0x48DE);


extern volatile __bit SPEN __at(0xCEF);


extern volatile __bit SREN __at(0xCED);


extern volatile __bit SSP1ADD0 __at(0x1090);


extern volatile __bit SSP1ADD1 __at(0x1091);


extern volatile __bit SSP1ADD2 __at(0x1092);


extern volatile __bit SSP1ADD3 __at(0x1093);


extern volatile __bit SSP1ADD4 __at(0x1094);


extern volatile __bit SSP1ADD5 __at(0x1095);


extern volatile __bit SSP1ADD6 __at(0x1096);


extern volatile __bit SSP1ADD7 __at(0x1097);


extern volatile __bit SSP1BUF0 __at(0x1088);


extern volatile __bit SSP1BUF1 __at(0x1089);


extern volatile __bit SSP1BUF2 __at(0x108A);


extern volatile __bit SSP1BUF3 __at(0x108B);


extern volatile __bit SSP1BUF4 __at(0x108C);


extern volatile __bit SSP1BUF5 __at(0x108D);


extern volatile __bit SSP1BUF6 __at(0x108E);


extern volatile __bit SSP1BUF7 __at(0x108F);


extern volatile __bit SSP1CLKPPS0 __at(0x7100);


extern volatile __bit SSP1CLKPPS1 __at(0x7101);


extern volatile __bit SSP1CLKPPS2 __at(0x7102);


extern volatile __bit SSP1CLKPPS3 __at(0x7103);


extern volatile __bit SSP1CLKPPS4 __at(0x7104);


extern volatile __bit SSP1DATPPS0 __at(0x7108);


extern volatile __bit SSP1DATPPS1 __at(0x7109);


extern volatile __bit SSP1DATPPS2 __at(0x710A);


extern volatile __bit SSP1DATPPS3 __at(0x710B);


extern volatile __bit SSP1DATPPS4 __at(0x710C);


extern volatile __bit SSP1IE __at(0x48B);


extern volatile __bit SSP1IF __at(0x8B);


extern volatile __bit SSP1MSK0 __at(0x1098);


extern volatile __bit SSP1MSK1 __at(0x1099);


extern volatile __bit SSP1MSK2 __at(0x109A);


extern volatile __bit SSP1MSK3 __at(0x109B);


extern volatile __bit SSP1MSK4 __at(0x109C);


extern volatile __bit SSP1MSK5 __at(0x109D);


extern volatile __bit SSP1MSK6 __at(0x109E);


extern volatile __bit SSP1MSK7 __at(0x109F);


extern volatile __bit SSP1SSPPS0 __at(0x7110);


extern volatile __bit SSP1SSPPS1 __at(0x7111);


extern volatile __bit SSP1SSPPS2 __at(0x7112);


extern volatile __bit SSP1SSPPS3 __at(0x7113);


extern volatile __bit SSP1SSPPS4 __at(0x7114);


extern volatile __bit SSP2ADD0 __at(0x10D0);


extern volatile __bit SSP2ADD1 __at(0x10D1);


extern volatile __bit SSP2ADD2 __at(0x10D2);


extern volatile __bit SSP2ADD3 __at(0x10D3);


extern volatile __bit SSP2ADD4 __at(0x10D4);


extern volatile __bit SSP2ADD5 __at(0x10D5);


extern volatile __bit SSP2ADD6 __at(0x10D6);


extern volatile __bit SSP2ADD7 __at(0x10D7);


extern volatile __bit SSP2BUF0 __at(0x10C8);


extern volatile __bit SSP2BUF1 __at(0x10C9);


extern volatile __bit SSP2BUF2 __at(0x10CA);


extern volatile __bit SSP2BUF3 __at(0x10CB);


extern volatile __bit SSP2BUF4 __at(0x10CC);


extern volatile __bit SSP2BUF5 __at(0x10CD);


extern volatile __bit SSP2BUF6 __at(0x10CE);


extern volatile __bit SSP2BUF7 __at(0x10CF);


extern volatile __bit SSP2CLKPPS0 __at(0x70E8);


extern volatile __bit SSP2CLKPPS1 __at(0x70E9);


extern volatile __bit SSP2CLKPPS2 __at(0x70EA);


extern volatile __bit SSP2CLKPPS3 __at(0x70EB);


extern volatile __bit SSP2CLKPPS4 __at(0x70EC);


extern volatile __bit SSP2DATPPS0 __at(0x70F0);


extern volatile __bit SSP2DATPPS1 __at(0x70F1);


extern volatile __bit SSP2DATPPS2 __at(0x70F2);


extern volatile __bit SSP2DATPPS3 __at(0x70F3);


extern volatile __bit SSP2DATPPS4 __at(0x70F4);


extern volatile __bit SSP2IE __at(0x493);


extern volatile __bit SSP2IF __at(0x93);


extern volatile __bit SSP2MSK0 __at(0x10D8);


extern volatile __bit SSP2MSK1 __at(0x10D9);


extern volatile __bit SSP2MSK2 __at(0x10DA);


extern volatile __bit SSP2MSK3 __at(0x10DB);


extern volatile __bit SSP2MSK4 __at(0x10DC);


extern volatile __bit SSP2MSK5 __at(0x10DD);


extern volatile __bit SSP2MSK6 __at(0x10DE);


extern volatile __bit SSP2MSK7 __at(0x10DF);


extern volatile __bit SSP2SSPPS0 __at(0x70F8);


extern volatile __bit SSP2SSPPS1 __at(0x70F9);


extern volatile __bit SSP2SSPPS2 __at(0x70FA);


extern volatile __bit SSP2SSPPS3 __at(0x70FB);


extern volatile __bit SSP2SSPPS4 __at(0x70FC);


extern volatile __bit STKOVF __at(0x44DF);


extern volatile __bit STKUNF __at(0x44DE);


extern volatile __bit SWDTEN __at(0x4B8);


extern volatile __bit SYNC __at(0xCF4);


extern volatile __bit SYSCMD __at(0x488F);


extern volatile __bit T016BIT __at(0xBC);


extern volatile __bit T0ASYNC __at(0xC4);


extern volatile __bit T0CKIPPS0 __at(0x7088);


extern volatile __bit T0CKIPPS1 __at(0x7089);


extern volatile __bit T0CKIPPS2 __at(0x708A);


extern volatile __bit T0CKIPPS3 __at(0x708B);


extern volatile __bit T0CKIPPS4 __at(0x708C);


extern volatile __bit T0CKPS0 __at(0xC0);


extern volatile __bit T0CKPS1 __at(0xC1);


extern volatile __bit T0CKPS2 __at(0xC2);


extern volatile __bit T0CKPS3 __at(0xC3);


extern volatile __bit T0CS0 __at(0xC5);


extern volatile __bit T0CS1 __at(0xC6);


extern volatile __bit T0CS2 __at(0xC7);


extern volatile __bit T0EN __at(0xBF);


extern volatile __bit T0OUT __at(0xBD);


extern volatile __bit T0OUTPS0 __at(0xB8);


extern volatile __bit T0OUTPS1 __at(0xB9);


extern volatile __bit T0OUTPS2 __at(0xBA);


extern volatile __bit T0OUTPS3 __at(0xBB);


extern volatile __bit T1CKIPPS0 __at(0x7090);


extern volatile __bit T1CKIPPS1 __at(0x7091);


extern volatile __bit T1CKIPPS2 __at(0x7092);


extern volatile __bit T1CKIPPS3 __at(0x7093);


extern volatile __bit T1CKIPPS4 __at(0x7094);


extern volatile __bit T1CKPS0 __at(0xDC);


extern volatile __bit T1CKPS1 __at(0xDD);


extern volatile __bit T1GGO_nDONE __at(0xE3);


extern volatile __bit T1GPOL __at(0xE6);


extern volatile __bit T1GPPS0 __at(0x7098);


extern volatile __bit T1GPPS1 __at(0x7099);


extern volatile __bit T1GPPS2 __at(0x709A);


extern volatile __bit T1GPPS3 __at(0x709B);


extern volatile __bit T1GPPS4 __at(0x709C);


extern volatile __bit T1GSPM __at(0xE4);


extern volatile __bit T1GSS0 __at(0xE0);


extern volatile __bit T1GSS1 __at(0xE1);


extern volatile __bit T1GTM __at(0xE5);


extern volatile __bit T1GVAL __at(0xE2);


extern volatile __bit T1SOSC __at(0xDB);


extern volatile __bit T1SYNC __at(0xDA);


extern volatile __bit T2CKPS0 __at(0xF8);


extern volatile __bit T2CKPS1 __at(0xF9);


extern volatile __bit T2OUTPS0 __at(0xFB);


extern volatile __bit T2OUTPS1 __at(0xFC);


extern volatile __bit T2OUTPS2 __at(0xFD);


extern volatile __bit T2OUTPS3 __at(0xFE);


extern volatile __bit T3CKPS0 __at(0x209C);


extern volatile __bit T3CKPS1 __at(0x209D);


extern volatile __bit T3GGO_nDONE __at(0x20A3);


extern volatile __bit T3GPOL __at(0x20A6);


extern volatile __bit T3GSPM __at(0x20A4);


extern volatile __bit T3GSS0 __at(0x20A0);


extern volatile __bit T3GSS1 __at(0x20A1);


extern volatile __bit T3GTM __at(0x20A5);


extern volatile __bit T3GVAL __at(0x20A2);


extern volatile __bit T3SOSC __at(0x209B);


extern volatile __bit T3SYNC __at(0x209A);


extern volatile __bit T4CKPS0 __at(0x20B8);


extern volatile __bit T4CKPS1 __at(0x20B9);


extern volatile __bit T4OUTPS0 __at(0x20BB);


extern volatile __bit T4OUTPS1 __at(0x20BC);


extern volatile __bit T4OUTPS2 __at(0x20BD);


extern volatile __bit T4OUTPS3 __at(0x20BE);


extern volatile __bit T5CKPS0 __at(0x20D4);


extern volatile __bit T5CKPS1 __at(0x20D5);


extern volatile __bit T5GGO_nDONE __at(0x20DB);


extern volatile __bit T5GPOL __at(0x20DE);


extern volatile __bit T5GSPM __at(0x20DC);


extern volatile __bit T5GSS0 __at(0x20D8);


extern volatile __bit T5GSS1 __at(0x20D9);


extern volatile __bit T5GTM __at(0x20DD);


extern volatile __bit T5GVAL __at(0x20DA);


extern volatile __bit T5SOSC __at(0x20D3);


extern volatile __bit T5SYNC __at(0x20D2);


extern volatile __bit T6CKPS0 __at(0x20F0);


extern volatile __bit T6CKPS1 __at(0x20F1);


extern volatile __bit T6OUTPS0 __at(0x20F3);


extern volatile __bit T6OUTPS1 __at(0x20F4);


extern volatile __bit T6OUTPS2 __at(0x20F5);


extern volatile __bit T6OUTPS3 __at(0x20F6);


extern volatile __bit TMR00 __at(0xA8);


extern volatile __bit TMR01 __at(0xA9);


extern volatile __bit TMR010 __at(0xB2);


extern volatile __bit TMR011 __at(0xB3);


extern volatile __bit TMR012 __at(0xB4);


extern volatile __bit TMR013 __at(0xB5);


extern volatile __bit TMR014 __at(0xB6);


extern volatile __bit TMR015 __at(0xB7);


extern volatile __bit TMR02 __at(0xAA);


extern volatile __bit TMR03 __at(0xAB);


extern volatile __bit TMR04 __at(0xAC);


extern volatile __bit TMR05 __at(0xAD);


extern volatile __bit TMR06 __at(0xAE);


extern volatile __bit TMR07 __at(0xAF);


extern volatile __bit TMR08 __at(0xB0);


extern volatile __bit TMR09 __at(0xB1);


extern volatile __bit TMR0IE __at(0x485);


extern volatile __bit TMR0IF __at(0x85);


extern volatile __bit TMR0MD __at(0x4890);


extern volatile __bit TMR1CS0 __at(0xDE);


extern volatile __bit TMR1CS1 __at(0xDF);


extern volatile __bit TMR1GE __at(0xE7);


extern volatile __bit TMR1GIE __at(0x48F);


extern volatile __bit TMR1GIF __at(0x8F);


extern volatile __bit TMR1IE __at(0x488);


extern volatile __bit TMR1IF __at(0x88);


extern volatile __bit TMR1MD __at(0x4891);


extern volatile __bit TMR1ON __at(0xD8);


extern volatile __bit TMR2IE __at(0x489);


extern volatile __bit TMR2IF __at(0x89);


extern volatile __bit TMR2MD __at(0x4892);


extern volatile __bit TMR2ON __at(0xFA);


extern volatile __bit TMR3CS0 __at(0x209E);


extern volatile __bit TMR3CS1 __at(0x209F);


extern volatile __bit TMR3GE __at(0x20A7);


extern volatile __bit TMR3GIE __at(0x49D);


extern volatile __bit TMR3GIF __at(0x9D);


extern volatile __bit TMR3IE __at(0x49C);


extern volatile __bit TMR3IF __at(0x9C);


extern volatile __bit TMR3MD __at(0x4893);


extern volatile __bit TMR3ON __at(0x2098);


extern volatile __bit TMR4IE __at(0x491);


extern volatile __bit TMR4IF __at(0x91);


extern volatile __bit TMR4MD __at(0x4894);


extern volatile __bit TMR4ON __at(0x20BA);


extern volatile __bit TMR5CS0 __at(0x20D6);


extern volatile __bit TMR5CS1 __at(0x20D7);


extern volatile __bit TMR5GE __at(0x20DF);


extern volatile __bit TMR5GIE __at(0x4A5);


extern volatile __bit TMR5GIF __at(0xA5);


extern volatile __bit TMR5IE __at(0x4A4);


extern volatile __bit TMR5IF __at(0xA4);


extern volatile __bit TMR5MD __at(0x4895);


extern volatile __bit TMR5ON __at(0x20D0);


extern volatile __bit TMR6IE __at(0x497);


extern volatile __bit TMR6IF __at(0x97);


extern volatile __bit TMR6MD __at(0x4896);


extern volatile __bit TMR6ON __at(0x20F2);


extern volatile __bit TRISA0 __at(0x460);


extern volatile __bit TRISA1 __at(0x461);


extern volatile __bit TRISA2 __at(0x462);


extern volatile __bit TRISA4 __at(0x464);


extern volatile __bit TRISA5 __at(0x465);


extern volatile __bit TRISC0 __at(0x470);


extern volatile __bit TRISC1 __at(0x471);


extern volatile __bit TRISC2 __at(0x472);


extern volatile __bit TRISC3 __at(0x473);


extern volatile __bit TRISC4 __at(0x474);


extern volatile __bit TRISC5 __at(0x475);


extern volatile __bit TRMT __at(0xCF1);


extern volatile __bit TSEN __at(0x8BD);


extern volatile __bit TSRNG __at(0x8BC);


extern volatile __bit TX9 __at(0xCF6);


extern volatile __bit TX9D __at(0xCF0);


extern volatile __bit TXCKPPS0 __at(0x7128);


extern volatile __bit TXCKPPS1 __at(0x7129);


extern volatile __bit TXCKPPS2 __at(0x712A);


extern volatile __bit TXCKPPS3 __at(0x712B);


extern volatile __bit TXCKPPS4 __at(0x712C);


extern volatile __bit TXEN __at(0xCF5);


extern volatile __bit TXIE __at(0x48C);


extern volatile __bit TXIF __at(0x8C);


extern volatile __bit UART1MD __at(0x48AD);


extern volatile __bit WDTPS0 __at(0x4B9);


extern volatile __bit WDTPS1 __at(0x4BA);


extern volatile __bit WDTPS2 __at(0x4BB);


extern volatile __bit WDTPS3 __at(0x4BC);


extern volatile __bit WDTPS4 __at(0x4BD);


extern volatile __bit WPUA0 __at(0x1060);


extern volatile __bit WPUA1 __at(0x1061);


extern volatile __bit WPUA2 __at(0x1062);


extern volatile __bit WPUA3 __at(0x1063);


extern volatile __bit WPUA4 __at(0x1064);


extern volatile __bit WPUA5 __at(0x1065);


extern volatile __bit WPUC0 __at(0x1070);


extern volatile __bit WPUC1 __at(0x1071);


extern volatile __bit WPUC2 __at(0x1072);


extern volatile __bit WPUC3 __at(0x1073);


extern volatile __bit WPUC4 __at(0x1074);


extern volatile __bit WPUC5 __at(0x1075);


extern volatile __bit WR __at(0x44A9);


extern volatile __bit WREN __at(0x44AA);


extern volatile __bit WRERR __at(0x44AB);


extern volatile __bit WUE __at(0xCF9);


extern volatile __bit ZERO __at(0x1A);


extern volatile __bit Z_SHAD __at(0x7F22);


extern volatile __bit nBOR __at(0x44D8);


extern volatile __bit nPD __at(0x1B);


extern volatile __bit nPOR __at(0x44D9);


extern volatile __bit nRI __at(0x44DA);


extern volatile __bit nRMCLR __at(0x44DB);


extern volatile __bit nRWDT __at(0x44DC);


extern volatile __bit nTO __at(0x1C);


# 30 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\pic.h"
#pragma intrinsic(__nop)
extern void __nop(void);

# 78
__attribute__((__unsupported__("The " "FLASH_READ" " macro function is no longer supported. Please use the MPLAB X MCC."))) unsigned char __flash_read(unsigned short addr);

__attribute__((__unsupported__("The " "FLASH_WRITE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_write(unsigned short addr, unsigned short data);

__attribute__((__unsupported__("The " "FLASH_ERASE" " macro function is no longer supported. Please use the MPLAB X MCC."))) void __flash_erase(unsigned short addr);

# 114 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\eeprom_routines.h"
extern void eeprom_write(unsigned char addr, unsigned char value);
extern unsigned char eeprom_read(unsigned char addr);


# 91 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\pic.h"
#pragma intrinsic(_delay)
extern __nonreentrant void _delay(unsigned long);
#pragma intrinsic(_delaywdt)
extern __nonreentrant void _delaywdt(unsigned long);

#pragma intrinsic(_delay3)
extern __nonreentrant void _delay3(unsigned char);

# 137
extern __bank0 unsigned char __resetbits;
extern __bank0 __bit __powerdown;
extern __bank0 __bit __timeout;

# 4 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\__size_t.h"
typedef unsigned size_t;

# 14 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\string.h"
extern void * memcpy(void *, const void *, size_t);
extern void * memmove(void *, const void *, size_t);
extern void * memset(void *, int, size_t);

# 36
extern char * strcat(char *, const char *);
extern char * strcpy(char *, const char *);
extern char * strncat(char *, const char *, size_t);
extern char * strncpy(char *, const char *, size_t);
extern char * strdup(const char *);
extern char * strtok(char *, const char *);


extern int memcmp(const void *, const void *, size_t);
extern int strcmp(const char *, const char *);
extern int stricmp(const char *, const char *);
extern int strncmp(const char *, const char *, size_t);
extern int strnicmp(const char *, const char *, size_t);
extern void * memchr(const void *, int, size_t);
extern size_t strcspn(const char *, const char *);
extern char * strpbrk(const char *, const char *);
extern size_t strspn(const char *, const char *);
extern char * strstr(const char *, const char *);
extern char * stristr(const char *, const char *);
extern char * strerror(int);
extern size_t strlen(const char *);
extern char * strchr(const char *, int);
extern char * strichr(const char *, int);
extern char * strrchr(const char *, int);
extern char * strrichr(const char *, int);

# 7 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\stdlib.h"
typedef unsigned short wchar_t;

# 15
typedef struct {
int rem;
int quot;
} div_t;
typedef struct {
unsigned rem;
unsigned quot;
} udiv_t;
typedef struct {
long quot;
long rem;
} ldiv_t;
typedef struct {
unsigned long quot;
unsigned long rem;
} uldiv_t;

# 65
extern double atof(const char *);
extern double strtod(const char *, const char **);
extern int atoi(const char *);
extern unsigned xtoi(const char *);
extern long atol(const char *);

# 73
extern long strtol(const char *, char **, int);

extern int rand(void);
extern void srand(unsigned int);
extern void * calloc(size_t, size_t);
extern div_t div(int numer, int denom);
extern udiv_t udiv(unsigned numer, unsigned denom);
extern ldiv_t ldiv(long numer, long denom);
extern uldiv_t uldiv(unsigned long numer,unsigned long denom);

# 85
extern unsigned long _lrotl(unsigned long value, unsigned int shift);
extern unsigned long _lrotr(unsigned long value, unsigned int shift);
extern unsigned int _rotl(unsigned int value, unsigned int shift);
extern unsigned int _rotr(unsigned int value, unsigned int shift);




extern void * malloc(size_t);
extern void free(void *);
extern void * realloc(void *, size_t);

# 104
extern int atexit(void (*)(void));
extern char * getenv(const char *);
extern char ** environ;
extern int system(char *);
extern void qsort(void *, size_t, size_t, int (*)(const void *, const void *));
extern void * bsearch(const void *, void *, size_t, size_t, int(*)(const void *, const void *));
extern int abs(int);
extern long labs(long);

extern char * itoa(char * buf, int val, int base);
extern char * utoa(char * buf, unsigned val, int base);




extern char * ltoa(char * buf, long val, int base);
extern char * ultoa(char * buf, unsigned long val, int base);

extern char * ftoa(float f, int * status);

# 7 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\stdarg.h"
typedef void * va_list[1];

#pragma intrinsic(__va_start)
extern void * __va_start(void);

#pragma intrinsic(__va_arg)
extern void * __va_arg(void *, ...);

# 43 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\stdio.h"
struct __prbuf
{
char * ptr;
void (* func)(char);
};

# 29 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\errno.h"
extern int errno;

# 12 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\conio.h"
extern void init_uart(void);

extern char getch(void);
extern char getche(void);
extern void putch(char);
extern void ungetch(char);

extern __bit kbhit(void);

# 23
extern char * cgets(char *);
extern void cputs(const char *);

# 88 "C:\Program Files (x86)\Microchip\xc8\v2.00\pic\include\c90\stdio.h"
extern int cprintf(char *, ...);
#pragma printf_check(cprintf)



extern int _doprnt(struct __prbuf *, const register char *, register va_list);


# 180
#pragma printf_check(vprintf) const
#pragma printf_check(vsprintf) const

extern char * gets(char *);
extern int puts(const char *);
extern int scanf(const char *, ...) __attribute__((unsupported("scanf() is not supported by this compiler")));
extern int sscanf(const char *, const char *, ...) __attribute__((unsupported("sscanf() is not supported by this compiler")));
extern int vprintf(const char *, va_list) __attribute__((unsupported("vprintf() is not supported by this compiler")));
extern int vsprintf(char *, const char *, va_list) __attribute__((unsupported("vsprintf() is not supported by this compiler")));
extern int vscanf(const char *, va_list ap) __attribute__((unsupported("vscanf() is not supported by this compiler")));
extern int vsscanf(const char *, const char *, va_list) __attribute__((unsupported("vsscanf() is not supported by this compiler")));

#pragma printf_check(printf) const
#pragma printf_check(sprintf) const
extern int sprintf(char *, const char *, ...);
extern int printf(const char *, ...);

# 6 "eeprom.h"
void EEPROMWrite(unsigned int address, unsigned char data);
unsigned char EEPROMRead(unsigned int address);

# 12 "interface.h"
typedef struct{
unsigned char check;
char name[16];
unsigned int bootMode;
float tempCalVf;
float tempCalTc;
float tempCalOffset;
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

# 56
void nrf24l01InterfaceInit(void);
unsigned char nrf24l01SPISend(unsigned char data);
void nrf24l01SPIStart(void);
void nrf24l01SPIEnd(void);

void exception(unsigned char exception);

void resetWDT(void);
void sleepMs(unsigned int milliseconds);

# 42 "nRF24L01_Types.h"
typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned PRIM_RX : 1;
unsigned PWR_UP : 1;
unsigned CRCO : 1;
unsigned EN_CRC : 1;
unsigned MASK_MAX_RT: 1;
unsigned MASK_TX_DS : 1;
unsigned MASK_RX_DR : 1;
unsigned Reserved : 1;

};
} n_CONFIG_t;


typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned ENAA_P0 : 1;
unsigned ENAA_P1 : 1;
unsigned ENAA_P2 : 1;
unsigned ENAA_P3 : 1;
unsigned ENAA_P4 : 1;
unsigned ENAA_P5 : 1;
unsigned Reserved : 2;

};
} n_EN_AA_t;


typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned ERX_P0 : 1;
unsigned ERX_P1 : 1;
unsigned ERX_P2 : 1;
unsigned ERX_P3 : 1;
unsigned ERX_P4 : 1;
unsigned ERX_P5 : 1;
unsigned Reserved : 2;

};
} n_EN_RXADDR_t;


typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned AW : 2;
unsigned Reserved : 6;
};
} n_SETUP_AW_t;



typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned ARC : 4;
unsigned ARD : 4;

};
} n_SETUP_RETR_t;


typedef union {
struct {
unsigned byte : 8;
};
struct {
unsigned RF_CH : 7;
unsigned Reserved : 1;
};
} n_RF_CH_t;


typedef union {
struct {
unsigned byte : 8;
};
struct {
unsigned Obsolete : 1;
unsigned RF_PWR : 2;
unsigned RF_DR_HIGH : 1;
unsigned PLL_LOCK : 1;
unsigned RF_DR_LOW : 1;
unsigned Reserved : 1;
unsigned CONT_WAVE : 1;
};
} n_RF_SETUP_t;



typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned TX_FULL : 1;
unsigned RX_P_NO : 3;
unsigned MAX_RT : 1;
unsigned TX_DS : 1;
unsigned RX_DR : 1;
unsigned Reserved : 1;

};
} n_STATUS_t;


typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned RPD : 1;

};
} n_RPD_t;

# 187
typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned RX_PW : 6;
unsigned Reserved : 2;

};
} n_RX_PW_t;

# 207
typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned DPL_P0 : 1;
unsigned DPL_P1 : 1;
unsigned DPL_P2 : 1;
unsigned DPL_P3 : 1;
unsigned DPL_P4 : 1;
unsigned DPL_P5 : 1;
unsigned Reserved : 2;

};
} n_DYNPD_t;



typedef union{
struct {
unsigned byte : 8;
};
struct {
unsigned EN_DYN_ACK : 1;
unsigned EN_ACK_PAY : 1;
unsigned EN_DPL : 1;
unsigned Reserved : 5;
};
} n_FEATURE_t;

# 8 "nrf24l01.h"
extern const unsigned char n_ADDRESS_P0[];
extern const unsigned char n_ADDRESS_MUL;


typedef struct{
unsigned char TX;
unsigned char RX;
n_STATUS_t statusRegister;
n_CONFIG_t configRegister;
unsigned char retryCount;
} nrf24l01State_t;

volatile nrf24l01State_t status;

# 35
typedef union{
struct{
unsigned int byte :8;
};
struct{
unsigned RPD : 1;
unsigned ACKRPD : 1;
unsigned ACKRequest : 1;
unsigned IsACK : 1;
unsigned Pipe : 3;
};
} packetData_t;

typedef struct{
packetData_t packetData;
char Message[32];
} nrf24l01Packet_t;

# 57
unsigned char nrf24l01Send(unsigned char command,unsigned char data);
void nrf24l01SetRXPipe(unsigned char pipe);
void nrf24l01SetRXMode(unsigned char rxMode);

void nrf24l01ISR(void);
void nrf24l01Init(void);
void nrf24l01Service(void);
void nrf24l01SetTXPipe(unsigned char pipe);
void nrf24l01SendPacket(nrf24l01Packet_t * txPacket);

# 4 "HC-SR04.h"
void hcsr04Init(void);
void hcsr04ISR(void);
void hcsr04Trigger(void);
float hcsr04GetAerage(void);

unsigned long counter = 0;

# 13 "main.c"
void interrupt ISR(void){

if (IOCAFbits.IOCAF3){
hcsr04ISR();
IOCAFbits.IOCAF3 = 0;
}

if (PIR0bits.INTF){
nrf24l01ISR();
PIR0bits.INTF = 0;
}

if (PIR1bits.ADIF){
PIR1bits.ADIF = 0;
}

}

float getADCValue(unsigned char channel){


float adcSum = 0;
unsigned int adcLoop = 1000;

ADCON0bits.CHS = channel;
FVRCONbits.FVREN = 1;
ADCON0bits.ADON = 1;

sleepMs(1);

while (adcLoop--){

ADCON0bits.ADGO = 1;

while (ADCON0bits.ADGO){
sleepMs(1);
}

adcSum+= (ADRESL | (ADRESH << 8));

}

FVRCONbits.FVREN = 0;
ADCON0bits.ADON = 0;


adcSum/= 1000;


if (ADCON1bits.ADPREF == 0b11){
switch (FVRCONbits.ADFVR){
case 0b10:
adcSum/= 500;
break;
}
}


return adcSum;
}

void sleepListren(unsigned int seconds){


while(seconds--){

nrf24l01SetRXMode(0);
sleepMs(200);

nrf24l01SetRXMode(0);
sleepMs(200);

}
}
void sendMessage(nrf24l01Packet_t * packet, const char * topic, float value){

int ftoaStatus;

memset(packet->Message, 0, sizeof(packet->Message));
strcpy(packet->Message, romData->name);
strcat(packet->Message, "/");
strcat(packet->Message, topic);
strcat(packet->Message, "/");
strcat(packet->Message, ftoa(value, &ftoaStatus));

packet->packetData.byte = 0;
packet->packetData.ACKRequest = 0;

nrf24l01SendPacket(packet);

sleepListren(1);
}


void loop(){

nrf24l01Packet_t packet;

sendMessage(&packet, "DIST", hcsr04GetAerage());

hcsr04Trigger();

sendMessage(&packet, "COUNT", counter);

# 122
sendMessage(&packet, "VBAT", getADCValue(0b000100) * 3.106382978723404);

# 134
FVRCONbits.TSEN = 1;
float vt = (2.048 - getADCValue(0b111101)) / 2;
FVRCONbits.TSEN = 0;




float ta = (vt / -0.00132) - (0.6063 / -0.00132) - 40;

sendMessage(&packet, "TEMP", ta);

# 153
}

unsigned char nrf24l01GetPipe(char * name){
unsigned char pipe = 0;
unsigned char i = 0;


for (i = 0; i < strlen(name); i++){
pipe+= name[i];
}

return (unsigned) pipe % 6;
}

void main(void) {



ANSELA = 0x00;
ANSELC = 0x00;

ODCONA = 0x00;
ODCONC = 0x00;




INLVLA = 0x00;
INLVLC = 0x00;

WPUA = 0x00;
WPUC = 0x00;

TRISCbits.TRISC5 = 0;
TRISCbits.TRISC4 = 0;

PORTCbits.RC4 = 0;

# 196
INTCONbits.PEIE = 0;
INTCONbits.GIE = 0;

OSCCON1bits.NOSC = 0b000;
OSCCON1bits.NDIV = 0b000;

_delay((unsigned long)((1000)*(32000000/4000000.0)));



strcpy(romData->name, "UWT");

nrf24l01Init();

unsigned char pipe = nrf24l01GetPipe(romData->name);
nrf24l01SetTXPipe(pipe);
nrf24l01SetRXPipe(pipe);



ADCON0bits.ADON = 0;


PORTAbits.RA4 = 0;
TRISAbits.TRISA4 = 1;
WPUAbits.WPUA4 = 0;
ODCONAbits.ODCA4 = 1;
ANSELAbits.ANSA4 = 1;


ANSELCbits.ANSC3 = 1;
TRISCbits.TRISC3 = 1;


FVRCONbits.TSEN = 1;
FVRCONbits.TSRNG = 1;


FVRCONbits.FVREN = 0;
FVRCONbits.ADFVR = 0b10;

ADCON1bits.ADCS = 0b111;
ADCON1bits.ADFM = 1;
ADCON1bits.ADPREF = 0b11;
ADCON1bits.ADNREF = 0b00;
PIE1bits.ADIE = 1;


ADCON0bits.CHS = 3;




TRISAbits.TRISA2 = 1;
PIE0bits.INTE = 1;
INTCONbits.INTEDG = 0;


TRISAbits.TRISA5 = 0;
PORTAbits.RA5 = 0;

hcsr04Init();


INTCONbits.PEIE = 1;
INTCONbits.GIE = 1;

nrf24l01Packet_t packet;

sendMessage(&packet, "BOOT0", 123);
sendMessage(&packet, "BOOT1", 456);

# 273
while(1){
loop();
}

return;
}
