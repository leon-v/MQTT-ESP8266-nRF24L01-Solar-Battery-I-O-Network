
#include "spi_interface.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "nRF24L01+.h"
#include "nRF24L01+_types.h"

#include "spi.h"
#include "pin_mux_register.h"

const uint8 n_ADDRESS_P0[] = {0xAD, 0x87, 0x66, 0xBC, 0xBB};
const uint8 n_ADDRESS_P1[] = {0x9D, 0xBF, 0x97, 0x4D, 0xFB};
const uint8 n_ADDRESS_MUL = 33;

#define CSPIN BIT15
#define CEPIN BIT4

LOCAL MQTT_Client* mqttClient;

void nrf24l01SPIStart(void){
    ets_intr_lock();		 //close	interrupt
	gpio_output_set(0, CSPIN, CSPIN, 0); // (high, low, out, in)
}

uint8 nrf24l01SPISend(uint8 data){

	uint32 regvalue;

	while(READ_PERI_REG(SPI_CMD(HSPI))&SPI_USR);
	CLEAR_PERI_REG_MASK(SPI_USER(HSPI), SPI_USR_MOSI|SPI_USR_MISO);

	//SPI_FLASH_USER2 bit28-31 is cmd length,cmd bit length is value(0-15)+1,
	// bit15-0 is cmd value.
	WRITE_PERI_REG(SPI_USER2(HSPI), ((7 & SPI_USR_COMMAND_BITLEN)<<SPI_USR_COMMAND_BITLEN_S)|((uint32)data));
	SET_PERI_REG_MASK(SPI_CMD(HSPI), SPI_USR);
	while(READ_PERI_REG(SPI_CMD(HSPI)) & SPI_USR);
	return (uint8) (READ_PERI_REG(SPI_W0(HSPI)) & 0xff);
}

void nrf24l01SPIEnd(void){
    gpio_output_set(CSPIN, 0, CSPIN, 0); // (high, low, out, in)
	ets_intr_unlock();	 	 //open	interrupt
}

n_STATUS_t status;
uint8 nrf24l01Send(uint8 command,uint8 data) {
    
    nrf24l01SPIStart();
    
    status.byte = nrf24l01SPISend(command);
    data        = nrf24l01SPISend(data);
    
    nrf24l01SPIEnd();
    
    return data;
}



static os_timer_t spiTestTimer;
void spiTestTimerFunction(){
	

	// Set config bit
    n_CONFIG_t config;
	config.byte = nrf24l01Send(n_R_REGISTER | n_CONFIG, 0); //1
	config.PRIM_RX = 1;
	nrf24l01Send(n_W_REGISTER | n_CONFIG, config.byte); //2

	// Enable all data pipes
	n_EN_RXADDR_t enRXAddr;
	enRXAddr.byte = nrf24l01Send(n_R_REGISTER | n_EN_RXADDR, 0); //3
	enRXAddr.ERX_P0 = 1;
	enRXAddr.ERX_P1 = 1;
	enRXAddr.ERX_P2 = 1;
	enRXAddr.ERX_P3 = 1;
	enRXAddr.ERX_P4 = 1;
	enRXAddr.ERX_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_EN_RXADDR, enRXAddr.byte); //4

	// Enable auto-ack for all pipes
	n_EN_AA_t enAA;
	enAA.byte = nrf24l01Send(n_R_REGISTER | n_EN_AA, 0); //5
	enAA.ENAA_P0 = 1;
	enAA.ENAA_P1 = 1;
	enAA.ENAA_P2 = 1;
	enAA.ENAA_P3 = 1;
	enAA.ENAA_P4 = 1;
	enAA.ENAA_P5 = 1;
	nrf24l01Send(n_W_REGISTER | n_EN_AA, enAA.byte); //6

	// Set pipes payload lengths to 32
	n_RX_PW_t rxPW;
	rxPW.RX_PW = 32;
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P0, rxPW.byte); // 7
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P1, rxPW.byte); // 8
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P2, rxPW.byte); // 9
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P3, rxPW.byte); // 10
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P4, rxPW.byte); // 11
	nrf24l01Send(n_W_REGISTER | n_RX_PW_P5, rxPW.byte); // 12

	// Setup addresses as a PRX

	// Receive pipe addres 0
	nrf24l01SPIStart();	
	status.byte = nrf24l01SPISend(n_W_REGISTER | n_RX_ADDR_P0);  //13
	nrf24l01SPISend(n_ADDRESS_P0[0]);
	nrf24l01SPISend(n_ADDRESS_P0[1]);
	nrf24l01SPISend(n_ADDRESS_P0[2]);
	nrf24l01SPISend(n_ADDRESS_P0[3]);
	nrf24l01SPISend(n_ADDRESS_P0[4] + (0 * n_ADDRESS_MUL));
	nrf24l01SPIEnd();

	// Receive pipe addres 1
	nrf24l01SPIStart();
	status.byte = nrf24l01SPISend(n_W_REGISTER | n_RX_ADDR_P1); // 14
	nrf24l01SPISend(n_ADDRESS_P1[0]);
	nrf24l01SPISend(n_ADDRESS_P1[1]);
	nrf24l01SPISend(n_ADDRESS_P1[2]);
	nrf24l01SPISend(n_ADDRESS_P1[3]);
	nrf24l01SPISend(n_ADDRESS_P1[4] + (1 * n_ADDRESS_MUL));
	nrf24l01SPIEnd();

	// Receive pipe addres 2
	nrf24l01Send(n_W_REGISTER | n_RX_ADDR_P2, n_ADDRESS_P1[4] + (2 * n_ADDRESS_MUL)); // 15

	// Receive pipe addres 3
	nrf24l01Send(n_W_REGISTER | n_RX_ADDR_P3, n_ADDRESS_P1[4] + (3 * n_ADDRESS_MUL)); // 16

	// Receive pipe addres 4
	nrf24l01Send(n_W_REGISTER | n_RX_ADDR_P4, n_ADDRESS_P1[4] + (4 * n_ADDRESS_MUL)); // 17

	// Receive pipe addres 5
	nrf24l01Send(n_W_REGISTER | n_RX_ADDR_P5, n_ADDRESS_P1[4] + (5 * n_ADDRESS_MUL)); // 18

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

	os_timer_arm(&spiTestTimer, 100, 1);
}
// void spi_mast_byte_write(uint8 spi_no,uint8 reg, uint8 value)
// void hspi_master_readwrite_repeat(void)