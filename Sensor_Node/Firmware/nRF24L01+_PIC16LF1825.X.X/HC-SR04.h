#ifndef HCSR04_H
#define	HCSR04_H

void hcsr04Init(void);
void hcsr04ISR(void);
void hcsr04Trigger(void);
float hcsr04GetAerage(void);

unsigned long counter = 0;

#endif