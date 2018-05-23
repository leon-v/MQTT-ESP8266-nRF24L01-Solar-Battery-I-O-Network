

#include "osapi.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "nRF24L01+.h"
#include "nRF24L01+_types.h"
#include "mem.h"
#include "pin_mux_register.h"

const uint8 n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const uint8 n_ADDRESS_MUL = 33;



#define MISOPIN	BIT12
#define MISOBIT	12
#define MOSIPIN	BIT13
#define CLKPIN	BIT14


#define INTBIT 5

#define CEPIN		BIT4
#define CELOW()		gpio_output_set(0, CEPIN, CEPIN, 0); // (high, low, out, in)
#define CEHIGH()	gpio_output_set(CEPIN, 0, CEPIN, 0); // (high, low, out, in)

#define CSPIN		BIT15
#define CSLOW()		gpio_output_set(0, CSPIN, CSPIN, 0); // (high, low, out, in)
#define CSHIGH()	gpio_output_set(CSPIN, 0, CSPIN, 0); // (high, low, out, in)



LOCAL MQTT_Client* mqttClient;

uint8 paused = 1;
void ICACHE_FLASH_ATTR nrf24l01Pause(void){
	paused = 1;
}
void ICACHE_FLASH_ATTR nrf24l01Unpause(void){
	paused = 0;
}

void nrf24l01SPIInit(void){

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); // MISO
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); // MOSI
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); // CLK
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15); // CS

	// MISO as input
	gpio_output_set(MISOPIN, 0, 0, MISOPIN);// (high, low, out, in)
	GPIO_DIS_OUTPUT(MISOBIT);

	// MISO as output and low
	gpio_output_set(0, MOSIPIN, MOSIPIN, 0);// (high, low, out, in)

	// CLK as output and low
	gpio_output_set(0, CLKPIN, CLKPIN, 0);// (high, low, out, in)

	// Enable the chip
	gpio_output_set(0, CEPIN, CEPIN, 0);// (high, low, out, in)
	os_delay_us(1000);

	// Set CS inactive
	// (high, low, out, in)
	gpio_output_set(CSPIN, 0, CSPIN, 0);
	
	os_delay_us(65535);
}

void nrf24l01SPIStart(void){
    ets_intr_lock();		 //close	interrupt

    CSLOW();

	os_delay_us(100);
}

uint8 nrf24l01SPISend(uint8 data) {

	// CS is low
	uint8 result = 0x00;
	uint8 bit = 8;
	while (bit > 0){

		// Read MISO
		result|= (GPIO_INPUT_GET(MISOBIT) << (bit - 1));

		// Set MOSI
		if ( (data >> (bit - 1)) & 1) {
			// High
			gpio_output_set(MOSIPIN, 0, MOSIPIN, 0);// (high, low, out, in)
		}else{
			// Low
			gpio_output_set(0, MOSIPIN, MOSIPIN, 0);// (high, low, out, in)
		}

		// Clock Up
		os_delay_us(10);
		gpio_output_set(CLKPIN, 0, CLKPIN, 0);// (high, low, out, in)

		// Clock Down
		os_delay_us(10);
		gpio_output_set(0, CLKPIN, CLKPIN, 0);// (high, low, out, in)

		bit--;
	}

	return result;
}

void nrf24l01SPIEnd(void){
	os_delay_us(100);
    CSHIGH();
	ets_intr_unlock();	 	 //open	interrupt
}

n_STATUS_t status;
void rf24l01UpdateStatus(){
	nrf24l01SPIStart();
	status.byte = nrf24l01SPISend(0);
	nrf24l01SPIEnd();
}



uint8 nrf24l01Send(uint8 command,uint8 data) {
    uint8 result;

    nrf24l01SPIStart();
    
    status.byte = nrf24l01SPISend(command);
    result = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    return result;
}


void nrf24l01SetTransmitMode(void){
    n_CONFIG_t config;
    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
    if (config.PRIM_RX == 1){
        config.PRIM_RX = 0;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        os_delay_us(130);
    }
}

void nrf24l01SetRecieveMode(void){

    n_CONFIG_t config;

    config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);

    if (config.PRIM_RX == 0){
        config.PRIM_RX = 1;
        nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
        os_delay_us(130);
    }
}



void nrf24l01SendStart(void){
    
    CELOW();
    
    nrf24l01SetTransmitMode();
    
    nrf24l01SPIStart();
    
    nrf24l01SPISend(n_W_TX_PAYLOAD);
}

void nrf24l01SendByte(uint8 payloadByte){
    nrf24l01SPISend(payloadByte);
}

void nrf24l01SendEnd(void){
    
    nrf24l01SPIEnd();

    CEHIGH();
}



void nrf24l01InitRegisters(void){
    
    n_SETUP_AW_t setupAW;
    setupAW.byte = 0x00;
    setupAW.AW = 3;
    nrf24l01Send(n_W_REGISTER | n_SETUP_AW, setupAW.byte);
    
    
    n_SETUP_RETR_t setupRetries;
    setupRetries.ARD = 15; //4000us
    setupRetries.ARC = 15; //15  retries
    nrf24l01Send(n_W_REGISTER | n_SETUP_RETR, setupRetries.byte);
    
    // Set Frequency
    // n_RF_CH_t channel;
    // channel.RF_CH = RADIO_FREQUENCY;
    // nrf24l01Send(n_W_REGISTER | n_RF_CH, channel.byte);
    
    // Set radio to 2 Mbps and high power.  Leave LNA_HCURR at its default.
    n_RF_SETUP_t rfSetup;
    rfSetup.RF_DR_LOW = 0;
    rfSetup.RF_DR_HIGH = 1;
    rfSetup.RF_PWR = 3;
    nrf24l01Send(n_W_REGISTER | n_RF_SETUP, rfSetup.byte);
    
    // Enable 2-byte CRC and power up in receive mode.
    n_CONFIG_t config;
	config.PRIM_RX = 1;
	config.EN_CRC = 1;
    config.CRCO = 1;
	config.PWR_UP = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);
    
    // Enable all data pipes
	n_EN_RXADDR_t enRXAddr;
	enRXAddr.ERX_P0 = 1;
	enRXAddr.ERX_P1 = 1;
	enRXAddr.ERX_P2 = 1;
	enRXAddr.ERX_P3 = 1;
	enRXAddr.ERX_P4 = 1;
	enRXAddr.ERX_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_EN_RXADDR, enRXAddr.byte);

	// Disable Auto ACK MCU needs to do this
	n_EN_AA_t enAA;
	enAA.byte = nrf24l01Send(n_R_REGISTER | n_EN_AA, 0);
	enAA.ENAA_P0 = 0;
	enAA.ENAA_P1 = 0;
	enAA.ENAA_P2 = 0;
	enAA.ENAA_P3 = 0;
	enAA.ENAA_P4 = 0;
	enAA.ENAA_P5 = 0;
	nrf24l01Send(n_W_REGISTER | n_EN_AA, enAA.byte);
    
    
    // Set dynamic payload length
	n_FEATURE_t feature;
	feature.byte = nrf24l01Send(n_R_REGISTER | n_FEATURE, 0);
	feature.EN_DPL = 1;
	nrf24l01Send(n_W_REGISTER | n_FEATURE, feature.byte);
    
    n_DYNPD_t DynPD;
	DynPD.byte = nrf24l01Send(n_R_REGISTER | n_DYNPD, 0);
	DynPD.DPL_P0 = 1;
	DynPD.DPL_P1 = 1;
	DynPD.DPL_P2 = 1;
	DynPD.DPL_P3 = 1;
	DynPD.DPL_P4 = 1;
	DynPD.DPL_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_DYNPD, DynPD.byte); 
    
    // clear the interrupt flags in case the radio's still asserting an old unhandled interrupt
    status.byte = 0x00;
    status.RX_DR = 1;
    status.TX_DS = 1;
    status.MAX_RT = 1;
    nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte);
    
    // flush the FIFOs in case there are old data in them.
    nrf24l01Send(n_FLUSH_TX, 0);
    nrf24l01Send(n_FLUSH_RX, 0);
}



void nrf24l01CheckRecieve(void){

	rf24l01UpdateStatus();

	// os_printf("nrf24l01CheckRecieve %02X \r\n", status.byte);

	if (status.RX_DR){

		// (high, low, out, in)
		gpio_output_set(0, CEPIN, CEPIN, 0);

		

		// Get data
		uint8 width = nrf24l01Send(n_R_RX_PL_WID, 0); //1

		char *buffer = NULL;
		buffer = (char *) os_malloc((width + 16) * sizeof(char));
		buffer[0] = '\0';
		strcat(buffer, "/radio/raw/");
		char *buffer1 = buffer + strlen(buffer);
		nrf24l01SPIStart();

		nrf24l01SPISend(n_R_RX_PAYLOAD);
		
		int i = 0;
		while (i < width){
			buffer1[i] = nrf24l01SPISend(0);
			i++;
		}
		nrf24l01SPIEnd();
		buffer1[i] = '\0';

		// os_printf("Got %s\r\n", buffer1);

		int offset = strlen(buffer) - 1;
		char* suffix = buffer + offset;
		while ( (offset > 0) && (buffer[offset] != '/') && (buffer[offset] != '\0')) {
			suffix = buffer + offset;
			offset--;
		}
		buffer[offset] = '\0';

		if (!paused){
			MQTT_Publish(mqttClient, buffer, suffix, strlen(suffix), 1, 1);
		}
		

		os_free(buffer);
		

		//Clear 
		nrf24l01Send(n_W_REGISTER | n_STATUS, status.byte); //2

		// (high, low, out, in)
		gpio_output_set(CEPIN, 0, CEPIN, 0);
	}
}

static os_timer_t spiTestTimer;
void ICACHE_FLASH_ATTR spiTestTimerFunction(void *arg){
	nrf24l01CheckRecieve();
}


void nrf24l01Interrupt(int * arg){

	uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);

	// os_printf("nrf24l01Interrupt\r\n");

	nrf24l01CheckRecieve();

	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status);
}


void ICACHE_FLASH_ATTR nrf24l01Init(MQTT_Client* p_mqttClient){

	mqttClient = p_mqttClient;

	nrf24l01SPIInit();

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); // CE


	GPIO_DIS_OUTPUT(GPIO_ID_PIN(5));
	GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, BIT(5));

	gpio_output_set(0, GPIO_ID_PIN(5), 0, GPIO_ID_PIN(5));
	gpio_pin_intr_state_set(GPIO_ID_PIN(5), GPIO_PIN_INTR_LOLEVEL);
	ets_isr_attach(ETS_GPIO_INUM, (ets_isr_t) nrf24l01Interrupt, NULL);
	ETS_GPIO_INTR_ENABLE();// Enable interrupts

	
	os_timer_disarm(&spiTestTimer);
	os_timer_setfn(&spiTestTimer, (os_timer_func_t *)spiTestTimerFunction, NULL);

	os_timer_arm(&spiTestTimer, 2000, 1);


	CELOW();
    
    os_delay_us(11000);
    
    nrf24l01InitRegisters();
    
    os_delay_us(2000);

    nrf24l01SetRecieveMode();

    os_delay_us(2000);
    
    CEHIGH();

}
// void spi_mast_byte_write(uint8 spi_no,uint8 reg, uint8 value)
// void hspi_master_readwrite_repeat(void)