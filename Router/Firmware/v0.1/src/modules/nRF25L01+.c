
#include "spi_interface.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "nRF24L01+.h"
#include "spi.h"
#include "pin_mux_register.h"

LOCAL MQTT_Client* mqttClient;

static os_timer_t spiTestTimer;
unsigned int spiCounter = 0x00;
void spiTestTimerFunction(){

	// os_printf("Write Data\r\n");
	spi_mast_byte_write(HSPI, spiCounter >> 8);
	spi_mast_byte_write(HSPI, spiCounter >> 0);
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
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_HSPI_CS0);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_HSPID_MOSI);
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_HSPI_CLK);

    // (high, low, out, in)
    // gpio_output_set(BIT13, BIT13, BIT13, 0); 			// Set low output

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