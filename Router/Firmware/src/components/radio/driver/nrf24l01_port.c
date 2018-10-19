#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "driver/spi_master.h"

#include "nrf24l01_port.h"
#include "nrf24l01.h"
#include "radio.h"


static void gpio_isr_handler(void *arg){

	uint32_t gp_io = (uint32_t) arg;
    xQueueSendFromISR(radioGetInterruptQueue(), &gp_io, NULL);
}

void lcd_spi_pre_transfer_callback(spi_transaction_t *t){

}

spi_device_handle_t spi;
void nrf24l01InterfaceInit(void){

	printf("nrf24l01InterfaceInit\n");

	esp_err_t ret;




	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO12); // MISO
	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_GPIO13); // MOSI
	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_GPIO14); // CLK
	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U, FUNC_GPIO15); // CS
	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5); // INT

	// Configure Inputs
	gpio_config_t inputs;
	inputs.pin_bit_mask	= (1ULL << PIN_NUM_MISO);
	inputs.mode			= GPIO_MODE_INPUT;
	inputs.pull_up_en	= GPIO_PULLUP_DISABLE;
	inputs.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	inputs.intr_type	= GPIO_INTR_DISABLE;
	gpio_config(&inputs);


	// // Configure outputs
	gpio_config_t output;
	output.pin_bit_mask	= (1ULL << PIN_NUM_CE) | (1ULL << PIN_NUM_CS) | (1ULL << PIN_NUM_MOSI) | (1ULL << PIN_NUM_CLK);
	output.mode			= GPIO_MODE_OUTPUT;
	output.pull_up_en	= GPIO_PULLUP_DISABLE;
	output.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	output.intr_type	= GPIO_INTR_DISABLE;
	gpio_config(&output);

	// // Configure Interrupts
	gpio_config_t interrupt;
	interrupt.pin_bit_mask	= (1ULL << PIN_NUM_INT);
	interrupt.mode			= GPIO_MODE_INPUT;
	interrupt.pull_up_en	= GPIO_PULLUP_DISABLE;
	interrupt.pull_down_en	= GPIO_PULLDOWN_DISABLE;
	interrupt.intr_type		= GPIO_INTR_NEGEDGE;
	gpio_config(&interrupt);

	// Setup interrupt pin
    gpio_install_isr_service(0);
    //hook isr handler for specific gpio pin
    gpio_isr_handler_add(PIN_NUM_INT, gpio_isr_handler, (void *) PIN_NUM_INT);

    	printf("buscfg\n");
	spi_bus_config_t buscfg = {
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1
    };

    //Initialize the SPI bus
    ret = spi_bus_initialize(HSPI_HOST, &buscfg, 1);
    ESP_ERROR_CHECK(ret);

    printf("devcfg\n");

    spi_device_interface_config_t devcfg = {
        .clock_speed_hz=10000000,           //Clock out at 10 MHz
        .mode=0,                                //SPI mode 0
        .spics_io_num=-1,               //CS pin
        .queue_size=1,                          //We want to be able to queue 1 transactions at a time
        .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
    };

    
    ret=spi_bus_add_device(HSPI_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

	// // Enable the chip
	gpio_set_level(PIN_NUM_CE, 0);

	delayUs(1000);

	gpio_set_level(PIN_NUM_CS, 1);
	
	delayUs(65535);

	printf("nrf24l01InterfaceInit Done\n");
}


unsigned char nrf24l01SPISend(unsigned char data){

	// printf("nrf24l01SPISend -> %04x\n", data);
	esp_err_t ret;

    spi_transaction_t t;
    memset(&t, 0, sizeof(t));

    t.length = 8;
    t.tx_buffer = &data;
    t.flags = SPI_TRANS_USE_RXDATA;

    ret=spi_device_polling_transmit(spi, &t);  //Transmit!

    assert(ret==ESP_OK);            //Should have had no issues.

    // printf("nrf24l01SPISend <- %04x\n", *(unsigned char*)t.rx_data);

    return *(unsigned char*)t.rx_data;

}


void nrf24l01SPIStart(void){
	enableInterrupts(0);
    nrf24l01CSLow();
    delayUs(0);
}

void nrf24l01SPIEnd(void){
	enableInterrupts(1);
    delayUs(0);
    nrf24l01CSHigh();
}

void enableInterrupts(unsigned char enable){
    if (enable){
    	//open interrupts
    	// ets_intr_unlock();
    }
    else{
    	//close interrupts
    	// ets_intr_lock();
    }
}

void exception(unsigned char number){
	printf("EXCEPTION: %u\r\n", number);
	// system_restart();
}