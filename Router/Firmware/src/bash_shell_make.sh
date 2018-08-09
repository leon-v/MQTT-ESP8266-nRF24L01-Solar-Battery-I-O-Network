#/bin/sh

export IDF_PATH=$PWD/../ESP8266_RTOS_SDK
export PATH=$PWD/../toolchain/xtensa-lx106-elf-linux64-1.22.0-88-gde0bdc1-4.8.5/xtensa-lx106-elf/bin/:$PATH
if [ "$1" = 2 ];
	then
	make clean
fi

make all