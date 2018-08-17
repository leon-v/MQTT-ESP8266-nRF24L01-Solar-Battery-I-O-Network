#include <xc.h>
#include "HC-SR04.h"
#include "interface.h"

volatile unsigned char waiting = 0;
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
    
    
    float average = 0;
    
    rloop = 300;
    rcount = 0;
    
    while (rloop--){
        
        // Reset Timer
        TMR1L = 0x00;
        TMR1H = 0x00;
        
        // Get module ready to trigger
        PORTCbits.RC4 = 1;
        
        // Give the module time to get ready
        __delay_us(10);
        
        // Start time we and flag state as waiting for echo
        T1CONbits.TMR1ON = 1;
        waiting = 1;
        
        // Lower trigger to start the transmit
        PORTCbits.RC4 = 0;
        
        // Sleep for 1ms or interrupt
        //0.343 meters per millisecond
        sleepMs(10);
        
        if (!waiting){
            average+= TMR1L + (unsigned) (TMR1H << 8);
            rcount++;
        }
        
        if (rcount >= 100){
            break;
        }
    }
    
    if (rcount > 10){
        // Get the average by dividing the total by the count
        average/= rcount;
    }
    
    // If the loop ran out, WE must have got no res
    else{
        average = 0;
    }
    
    return average;
}

void hcsr04ISR(void){
    waiting = 0;
    T1CONbits.TMR1ON = 0;
}

