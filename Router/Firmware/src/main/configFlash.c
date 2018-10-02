#include <string.h>

#include "spi_flash.h"


#include "configFlash.h"

configFlashSaveFlag_t saveFlag;

/*Please Keep the following configuration if you have no very deep understanding of ESP*/
// https://github.com/esp8266/esp8266-wiki/wiki/Memory-Map
#define CFG_LOCATION 0x79    /* Please don't change or if you know what you doing */

#define currentVersion 0x00000002    /* Change this value to reset */

void configFlashSave(void) {

	spi_flash_read((CFG_LOCATION + 3) * SPI_FLASH_SEC_SIZE, (unsigned int *) &saveFlag, sizeof(configFlashSaveFlag_t));

	if (saveFlag.flag == 0) {
		spi_flash_erase_sector(CFG_LOCATION + 1);
		spi_flash_write((CFG_LOCATION + 1) * SPI_FLASH_SEC_SIZE, (unsigned int *) &configFlash, sizeof(configFlash_t));

		saveFlag.flag = 1;

		spi_flash_erase_sector(CFG_LOCATION + 3);
		spi_flash_write((CFG_LOCATION + 3) * SPI_FLASH_SEC_SIZE, (unsigned int *) &saveFlag, sizeof(configFlashSaveFlag_t));
	}

	else {
		spi_flash_erase_sector(CFG_LOCATION + 0);
		spi_flash_write((CFG_LOCATION + 0) * SPI_FLASH_SEC_SIZE, (unsigned int *) &configFlash, sizeof(configFlash_t));
		saveFlag.flag = 0;
		spi_flash_erase_sector(CFG_LOCATION + 3);
		spi_flash_write((CFG_LOCATION + 3) * SPI_FLASH_SEC_SIZE, (unsigned int *) &saveFlag, sizeof(configFlashSaveFlag_t));
	}
}

void configFlashLoad(void) {

	spi_flash_read((CFG_LOCATION + 3) * SPI_FLASH_SEC_SIZE, (unsigned int *) &saveFlag, sizeof(configFlashSaveFlag_t));

	if (saveFlag.flag == 0) {
		spi_flash_read((CFG_LOCATION + 0) * SPI_FLASH_SEC_SIZE, (unsigned int *) &configFlash, sizeof(configFlash_t));
	}

	else {
		spi_flash_read((CFG_LOCATION + 1) * SPI_FLASH_SEC_SIZE, (unsigned int *) &configFlash, sizeof(configFlash_t));
	}

	if(configFlash.version != currentVersion){

		memset(&configFlash, 0x00, sizeof(configFlash));

		configFlash.version = currentVersion;

		configFlashSave();
	}

}

void configFlashInit(void) {
	configFlashLoad();
}