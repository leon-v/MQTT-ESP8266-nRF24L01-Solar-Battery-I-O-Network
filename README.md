# MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network

#### The primary intention of the network is to be solar powered and real time so i can sense someone walking down my driveway and get a message on my phone
#### And secondarily it will be low cost. The parts i select will be cheap.


This project will consist of:

1. An ESP8266 with one nRF24L01+ module which will act as an MQTT router for nRF24L01+.

2. Multiple nRF24L01+ nodes with a PIC16LF18325 to translate the radio to usable signals including PWM, ADC, DAC, I/O and Interrupt for real time detection.
These will be battery powered from an 18650 and solar panels. The PIC will use responsible for battery management.

All user configuration will be done via MQTT.

Each node will have a short name which will be part of the 32 bytes payload.

### Packet format
Packet format will be dynamic width, up to 32 characters.
With limits for each segment of 16 characters.



### Output Commands (for me to sandbox):
|Control Name		| Description			| Limits			|
|-------------------|-----------------------|------------------:|
|ADC0_				|ADC Input				| (0- 1023)			|
|INT__				|Interrupt Input		| (0 - 1)			|

### Inputs Commands:
|Control Name		| Description			| Limits			|
|-------------------|-----------------------|------------------:|
|PWM0D				| PWM 0 Duty Output		| (0 - 1023)		|
|PWMPT				| PWM Period Timer		| (0 - 255)			|
|PWMPP				| PWM Period Prescaler	| (0 - 3)			|

|DAC0S				| DAC 0 Set				| (0 - 31)			|
|RDORT				| Radio RX time			| (0 - 65535)		|
|RDOST				| Radio Sleep time		| (0 - 65535)		|
|RDOSK				| Radio Set Key			| (0 - 4294967295)	|


Encryption May be used to prevent noise from any other sensors. 
Encryption used is possibly TEA
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

All configuration (apart from the WiFi User / Pass and MQTT details) will be retained in the MQTT broker.
MQTT topics:


### PIC16LF18325 Pin Functions
|Pin	|IO	|Direction	|Secondary Function	|Primary Function		|
|-------|---|-----------|-------------------|-----------------------|
|1.		|Vdd| 			|					| 3.3V Input			|
|2.		|RA5| Output	|					| Battery Charge Control|
|3.		|RA4| Input		|					| Battery Voltage ADC	|
|4.		|RA3| Input		|ICSP MCLR			| IOC					|
|5.		|RC5| Output	|					| PWM					|
|6.		|RC4| Output	|					| Digital Output		|
|7.		|RC3| Input		|					| ADC					|
|8.		|RC2| Output	|					| Radio SPI MOSI		|
|9.		|RC1| Input		|					| Radio SPI MISO		|
|10.	|RC0| Output	|					| Radio SPI CLK			|
|11.	|RA2| Input		|					| Radio SPI Interrupt	|
|12.	|RA1| Both		|ICSP CLK			| Radio Chip Select		|
|13.	|RA0| Both		|ICSP DAT			| Radio Chip Enable		|
|14.	|Vss|			|					| GND					|


## Licence is Beerware:
Licenced under the Beerware Vwesion 42
https://en.wikipedia.org/wiki/Beerware

