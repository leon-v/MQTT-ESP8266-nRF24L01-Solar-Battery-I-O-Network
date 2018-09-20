# MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network

#### The primary intention of the network is to be solar powered and real time so i can sense someone walking down my driveway and get a message on my phone
#### And secondarily it will be low cost. The parts i select will be cheap.


This project consists of:

1. An ESP8266 with one nRF24L01+ module which will act as an MQTT router for nRF24L01+.

2. Multiple nRF24L01+ nodes with a PIC to translate the radio to usable signals including PWM, ADC, DAC, I/O and Interrupt for real time detection.
These will be battery powered from an 18650 and solar panels. The PIC will use responsible for battery management.
Configuration will be done via MQTT.

Each node will have a short name which will be part of the 32 bytes payload.

### Packet format
Packet format will be dynamic width, up to 32 characters.
With limits for each segment of 16 characters.
E.g. name/sensor/vlaue
tank1/level/1234.5678


All configuration (apart from the WiFi User / Pass and MQTT details) will be retained in the MQTT broker.
MQTT topics:

## Licence is Beerware:
Licenced under the Beerware Vwesion 42
https://en.wikipedia.org/wiki/Beerware

### Enviroment
Notes on setting up bash shell

Install Ubuntu 18 from the Misrosoft store.

In a command prompt:
```
>bash
>$sudo apt install dos2unix make python

```
eading package lists... Done
Building dependency tree
Reading state information... Done
Suggested packages:
  make-doc
The following NEW packages will be installed:
  dos2unix make
0 upgraded, 2 newly installed, 0 to remove and 0 not upgraded.
Need to get 220 kB of archives.
After this operation, 671 kB of additional disk space will be used.
Get:1 http://archive.ubuntu.com/ubuntu xenial/main amd64 make amd64 4.1-6 [151 kB]
Get:2 http://archive.ubuntu.com/ubuntu xenial/universe amd64 dos2unix amd64 6.0.4-1 [68.7 kB]
Fetched 220 kB in 2s (85.0 kB/s)
Selecting previously unselected package make.
(Reading database ... 25474 files and directories currently installed.)
Preparing to unpack .../archives/make_4.1-6_amd64.deb ...
Unpacking make (4.1-6) ...
Selecting previously unselected package dos2unix.
Preparing to unpack .../dos2unix_6.0.4-1_amd64.deb ...
Unpacking dos2unix (6.0.4-1) ...
Processing triggers for man-db (2.7.5-1) ...
Setting up make (4.1-6) ...
Setting up dos2unix (6.0.4-1) ...
```
>$sudo ln -sv /usr/bin/python3 /usr/bin/python





Encryption may be used to prevent noise from any other sensors. 
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
