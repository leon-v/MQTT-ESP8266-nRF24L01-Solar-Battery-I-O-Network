# MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network

#### The primary intention of the network is to be solar powered and real time so i can sense someone walking down my driveway and get a message on my phone
#### And secondarily it will be low cost. The parts i select will be cheap.


This project will consist of:

1. An ESP8266 with one or two nRF24L01+ modules which will act as an MQTT router for nRF24L01+.

2. Multiple nRF24L01+ nodes with a PIC16LF1503 to translate the radio to usable signals including PWM, ADC, DAC, I/O and Interrupt for real time detection.
These will be battery powered from an 18650 and solar panels. The PIC will use responsible for not overcharging the 18650, it letting it trickle charge.

All configuration will be done via MQTT.
The two main parameters that need to be set before use are the short encryption key and the node name

Each node will have a short name which will be part of the 32 bytes payload.

Packet format will be fixed length:
******************************************************
|Sensor Name| Sensor / Control Location | Binary Data|
******************************************************
 19 bytes           5 bytes               8 bytes


Sensor / Controller names

### Outputs:
ADC0_:	ADC Input			(0- 1023)
INT__:	Interrupt Input		(0 - 1)

### Inputs:
PWM0D:	PWM 0 Duty Output	(0 - 1023)
PWMPT:	PWM Period Timer	(0 - 255)
PWMPP:	PWM Period Prescaler(0 - 3)

DAC0S:	DAC 0 Set			(0 - 31)

RDORT:	Radio RX time		(0 - 65535)
RDOST:	Radio Sleep time	(0 - 65535)
RDOSK:	Radio Set Key		(0 - 4294967295)


Encryption used is TEA
```
void encrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0, i;           /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i < 32; i++) {                       /* basic cycle start */
        sum += delta;
        v0 += ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        v1 += ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}

void decrypt (uint32_t* v, uint32_t* k) {
    uint32_t v0=v[0], v1=v[1], sum=0xC6EF3720, i;  /* set up */
    uint32_t delta=0x9e3779b9;                     /* a key schedule constant */
    uint32_t k0=k[0], k1=k[1], k2=k[2], k3=k[3];   /* cache key */
    for (i=0; i<32; i++) {                         /* basic cycle start */
        v1 -= ((v0<<4) + k2) ^ (v0 + sum) ^ ((v0>>5) + k3);
        v0 -= ((v1<<4) + k0) ^ (v1 + sum) ^ ((v1>>5) + k1);
        sum -= delta;
    }                                              /* end cycle */
    v[0]=v0; v[1]=v1;
}
```