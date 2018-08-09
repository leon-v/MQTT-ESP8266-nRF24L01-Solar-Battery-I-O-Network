deps_config := \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/aws_iot/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/esp8266/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/freertos/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/log/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/lwip/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/newlib/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/ssl/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/tcpip_adapter/Kconfig \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/bootloader/Kconfig.projbuild \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/esptool_py/Kconfig.projbuild \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/components/partition_table/Kconfig.projbuild \
	/mnt/c/Users/Leon/Documents/GitHub/MQTT-ESP8266-nRF24L01-Solar-Battery-I-O-Network/Router/Firmware/ESP8266_RTOS_SDK/Kconfig

include/config/auto.conf: \
	$(deps_config)


$(deps_config): ;
