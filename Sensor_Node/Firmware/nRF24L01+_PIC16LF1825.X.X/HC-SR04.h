#ifndef HCSR04_H
#define	HCSR04_H

void hcsr04Init(void);
void hcsr04ISR(void);
void hcsr04Trigger(void);
float hcsr04GetAerage(void);

unsigned int rloop = 0;
unsigned int rlimit = 0;
unsigned int rcount = 0;

unsigned long counter = 0;

#endif