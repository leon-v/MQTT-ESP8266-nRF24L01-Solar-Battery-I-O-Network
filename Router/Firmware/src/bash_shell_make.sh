#/bin/sh


export IDF_PATH=$PWD/../esp-idf
export PATH=$PWD/../toolchain/xtensa-esp32-elf/bin/:$PATH
if [ "$1" = 2 ];
	then
	make clean
fi

make -j4 all