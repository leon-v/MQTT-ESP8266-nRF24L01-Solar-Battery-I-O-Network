
#include "spi_interface.h"
#include "ets_sys.h"
#include "osapi.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "mqtt.h"
#include "nRF24L01+.h"
#include "spi.h"

LOCAL MQTT_Client* mqttClient;

static os_timer_t spiTestTimer;
unsigned int spiCounter = 0x00;
void spiTestTimerFunction(){

	// os_printf("Write Data\r\n");
	spi_mast_byte_write(HSPI, spiCounter);
	spiCounter++;
	// if (spiCounter == 255){
	// 	spiCounter = 0;
	// }

}

void ICACHE_FLASH_ATTR nrf24l01Init(MQTT_Client* p_mqttClient){



	mqttClient = p_mqttClient;

	SpiAttr hSpiAttr;
	hSpiAttr.bitOrder = SpiBitOrder_MSBFirst;
	hSpiAttr.speed = SpiSpeed_0_5MHz;
	hSpiAttr.mode = SpiMode_Master;
	hSpiAttr.subMode = SpiSubMode_0;

	gpio_output_set(0, BIT13, BIT13, 0); 			// Set GPIO15 low output

    // Init HSPI GPIO
	WRITE_PERI_REG(PERIPHS_IO_MUX, 0x105);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, 2);//configure io to spi mode
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, 2);//configure io to spi mode
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, 2);//configure io to spi mode
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, 2);//configure io to spi mode

	 SPIInit(SpiNum_HSPI, &hSpiAttr);

	
	os_timer_disarm(&spiTestTimer);
	os_timer_setfn(&spiTestTimer, (os_timer_func_t *)spiTestTimerFunction, NULL);

	os_timer_arm(&spiTestTimer, 100, 1);
}
// void spi_mast_byte_write(uint8 spi_no,uint8 reg, uint8 value)
// void hspi_master_readwrite_repeat(void)