
#include "spi_interface.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "nRF24L01+.h"
#include "nRF24L01+_types.h"

#include "spi.h"
#include "pin_mux_register.h"

#define CSPIN BIT15
#define CEPIN BIT4

LOCAL MQTT_Client* mqttClient;


uint8 ICACHE_FLASH_ATTR spi_mast_byte_read_write(uint8 spi_no,uint8 data) {
	uint32 regvalue;

	if(spi_no>1) 		return; //handle invalid input number

	while(READ_PERI_REG(SPI_CMD(spi_no))&SPI_USR);
	CLEAR_PERI_REG_MASK(SPI_USER(spi_no), SPI_USR_MOSI|SPI_USR_MISO);

	//SPI_FLASH_USER2 bit28-31 is cmd length,cmd bit length is value(0-15)+1,
	// bit15-0 is cmd value.
	WRITE_PERI_REG(SPI_USER2(spi_no), ((7 & SPI_USR_COMMAND_BITLEN)<<SPI_USR_COMMAND_BITLEN_S)|((uint32)data));
	SET_PERI_REG_MASK(SPI_CMD(spi_no), SPI_USR);
	while(READ_PERI_REG(SPI_CMD(spi_no)) & SPI_USR);
	return (uint8) (READ_PERI_REG(SPI_W0(spi_no)) & 0xff);
 } 

n_STATUS_t status;

uint8 nrf24l01Send(uint8 command,uint8 data) {
	ets_intr_lock();		 //close	interrupt

	gpio_output_set(0, CSPIN, CSPIN, 0); // (high, low, out, in)
	status.byte = spi_mast_byte_read_write(HSPI, command);
	uint8 result;
	result = spi_mast_byte_read_write(HSPI, data);
	gpio_output_set(CSPIN, 0, CSPIN, 0); // (high, low, out, in)

	ets_intr_unlock();	 	 //open	interrupt
	return result;
}


static os_timer_t spiTestTimer;
void spiTestTimerFunction(){
	
	n_CONFIG_t config;
	config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0);
	config.PRIM_RX = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte);


	n_EN_RXADDR_t enRXAddr;
	enRXAddr.byte = nrf24l01Send(n_R_REGISTER | n_EN_RXADDR, 0);
	enRXAddr.ERX_P0 = 1;
	enRXAddr.ERX_P1 = 1;
	enRXAddr.ERX_P2 = 1;
	enRXAddr.ERX_P3 = 1;
	enRXAddr.ERX_P4 = 1;
	enRXAddr.ERX_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_EN_RXADDR, enRXAddr.byte);

	n_EN_AA_t enAA;
	enAA.byte = nrf24l01Send(n_R_REGISTER | n_EN_AA, 0);
	enAA.ENAA_P0 = 1;
	enAA.ENAA_P1 = 1;
	enAA.ENAA_P2 = 1;
	enAA.ENAA_P3 = 1;
	enAA.ENAA_P4 = 1;
	enAA.ENAA_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_EN_AA, enAA.byte);

	n_RX_PW_t rxPW;
	rxPW.RX_PW = 32;
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P0, rxPW.byte);
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P1, rxPW.byte);
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P2, rxPW.byte);
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P3, rxPW.byte);
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P4, rxPW.byte);
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P5, rxPW.byte);


	// (high, low, out, in)
	gpio_output_set(CEPIN, 0, CEPIN, 0);

	// Reciever listening
}

void ICACHE_FLASH_ATTR nrf24l01Init(MQTT_Client* p_mqttClient){

	mqttClient = p_mqttClient;


	 //Initialze Pins on ESP8266
	WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_HSPIQ_MISO);
	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_HSPI_CS0);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_HSPID_MOSI);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_HSPI_CLK);

	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15);

	// (high, low, out, in)
	gpio_output_set(CSPIN, 0, CSPIN, 0); 			// Set low output

	// (high, low, out, in)
	gpio_output_set(0, CEPIN, CEPIN, 0);
	

	SpiAttr pAttr;   //Set as Master/Sub mode 0 and speed 10MHz
	pAttr.mode = SpiMode_Master;
	pAttr.subMode = SpiSubMode_0;
	pAttr.speed = SpiSpeed_10MHz; // 0.5, 1, 2, 5, 8, 10
	pAttr.bitOrder = SpiBitOrder_MSBFirst;
	SPIInit(SpiNum_HSPI, &pAttr);
	
	os_timer_disarm(&spiTestTimer);
	os_timer_setfn(&spiTestTimer, (os_timer_func_t *)spiTestTimerFunction, NULL);

	os_timer_arm(&spiTestTimer, 1, 1);
}
// void spi_mast_byte_write(uint8 spi_no,uint8 reg, uint8 value)
// void hspi_master_readwrite_repeat(void)