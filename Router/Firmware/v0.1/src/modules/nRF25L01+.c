
#include "spi_interface.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "nRF24L01+.h"
#include "nRF24L01+_types.h"

#include "spi.h"
#include "pin_mux_register.h"

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
uint8 nrf24l01Send(uint8 command,uint8 data){

	ets_intr_lock();		 //close	interrupt

    n_CONFIG_t config;

    gpio_output_set(0, BIT15, BIT15, 0); // (high, low, out, in)
    status.byte = spi_mast_byte_read_write(HSPI, n_R_REGISTER | n_CONFIG);
    config.byte = spi_mast_byte_read_write(HSPI, 0);
    gpio_output_set(BIT15, 0, BIT15, 0); // (high, low, out, in)

    config.PRIM_RX = 1;

    gpio_output_set(0, BIT15, BIT15, 0); // (high, low, out, in)
    status.byte = spi_mast_byte_read_write(HSPI, n_W_REGISTER | n_CONFIG);
    spi_mast_byte_read_write(HSPI, config.byte);
    pio_output_set(BIT15, 0, BIT15, 0); // (high, low, out, in)

    ets_intr_unlock();	 	 //open	interrupt
}

static os_timer_t spiTestTimer;
unsigned int spiCounter = 0x00;
void spiTestTimerFunction(){

	// os_printf("Write Data\r\n");

	// (high, low, out, in)
	ets_intr_lock();		 //close	interrupt

    gpio_output_set(0, BIT15, BIT15, 0); 			// Set low output


    spi_mast_byte_write(HSPI, spiCounter >> 16);
	spi_mast_byte_write(HSPI, spiCounter >> 8);
	spi_mast_byte_write(HSPI, spiCounter >> 0);

	// (high, low, out, in)
    gpio_output_set(BIT15, 0, BIT15, 0); 			// Set low output

    ets_intr_unlock();	 	 //open	interrupt
	spiCounter++;
	// if (spiCounter == 255){
	// 	spiCounter = 0;
	// }

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
    gpio_output_set(BIT15, 0, BIT15, 0); 			// Set low output

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