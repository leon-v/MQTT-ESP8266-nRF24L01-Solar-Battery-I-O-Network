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


### Packet format will be fixed length
|MQTT Topic	| Command	| Value	|
|:---------:|:---------:|:-----:|
|19 Bytes	| 5 Bytes	| 8 Bytes|



### Output Commands:
|Control Name		| Description			| Limits			|
|-------------------|-----------------------|------------------:|
|ADC0_				| ADC Input				| (0- 1023)			|
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


Encryption will be used to prevent noise from any other sensors. 
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

All configuration (apart from the WiFi User / Pass and MQTT details) will be retained in the MQTT broker.
MQTT topics:

#List of all the radio node names:
/radio/configuration/nodes

#The encryption keys for the node:
/radio/encryption/[NODE_TOPIC]/[INDEX]/[ASCII_KEY]
[NODE_TOPIC] Is the node MQTT topic
[INDEX] Is the key index, when changing key, the new key will be the next available index (0 to n), and the old / active key is 0.
When the router gets a packet that was successfully decrypted with a key that is not 0, it will place that key in index 0 and clear all the others.

#The real time log of raw unencrypted packet data
/radio/stream/encrypted Strings if raw packet data


I think ill make the MQTT sever handle all the decryption and re-publishing 

### PIC16LF1505 Pin Functions
|Pin	|Direction	|Secondary Function	|Primary Function		|
|-------|-----------|-------------------|-----------------------|
|1.		| 			|					| 3.3V Input			|
|2.		| Output	|					| Battery Charge Control|
|3.		| Input		|					| Battery Voltage ADC	|
|4.		| Input		|ICSP MCLR			| IOC					|
|5.		| Output	|					| PWM					|
|6.		| Output	|					| Digital Output		|
|7.		| Input		|					| ADC					|
|8.		| Output	|					| Radio SPI MOSI		|
|9.		| Input		|					| Radio SPI MISO		|
|10.	| Output	|					| Radio SPI CLK			|
|11.	| Input		|					| Radio SPI Interrupt	|
|12.	| Both		|ICSP CLK			| Radio Chip Select		|
|13.	| Both		|ICSP DAT			| Radio Chip Enable		|
|14.	|			|					| GND					|