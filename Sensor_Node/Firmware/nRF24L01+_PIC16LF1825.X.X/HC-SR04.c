#include <xc.h>
#include "HC-SR04.h"
#include "interface.h"

unsigned int distance = 0;

void hcsr04Init(void){
    
    // Init Echo pin
    IOCAPbits.IOCAP3 = 1;
    PIE0bits.IOCIE = 1;
    
    // Init Trigger pin
    TRISCbits.TRISC4 = 0;
    PORTCbits.RC4 = 0;
    WPUAbits.WPUA3 = 0;
    
    
    T1CONbits.TMR1ON = 0;
    T1CONbits.TMR1CS = 0b01;
    T1CONbits.T1CKPS = 0b00;
    T1CONbits.T1SYNC = 1;
    T1GCONbits.TMR1GE = 0;
    
}

// uS / 58 = centimeters 
//100us = 3206
// 32.06 per us
void hcsr04Trigger(void){
    
    counter++;
    
    // Cycle trigger pin
    
    
}

float hcsr04GetAerage(void){
    
    unsigned char loop = 10;
    unsigned char limit = 0;
    unsigned char count = 0;
    float average = 0;
    
    while (--loop){
        
        // Reset Timer
        TMR1L = 0x00;
        TMR1H = 0x00;
        
        // Trigger Module
        PORTCbits.RC4 = 1;
        __delay_us(10);
        PORTCbits.RC4 = 0;
        
        // Start timer
        T1CONbits.TMR1ON = 1;
        
        // Set time limit
        limit = 10;
        
        // Wait for timer to end
        while (T1CONbits.TMR1ON){
            
            // Break if the limit reached
            if (!(--limit)) {
                break;
            }
            
            // Sleep for 1ms or interrupt
            sleepMs(1);
        }
        
        // If the limit was not reached, sum the value
        if (limit > 0){
            average+= TMR1L + (unsigned) (TMR1H << 8);
            count++;
        }
    }
    
    // Get the average by dividing the total by the count
    average/= count;
    
    return average;
}

void hcsr04ISR(void){
    T1CONbits.TMR1ON = 0;
}

