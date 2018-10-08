#/bin/sh

cd components/httpd_custom
rm fsdata_custom.c
./makefsdata/makefsdata
sed -i '1s/^/#include "fsdata_custom.h"\n/' fsdata_custom.c
cd ../..


export IDF_PATH=$PWD/../esp-idf
export PATH=$PWD/../toolchain/xtensa-lx106-elf-linux64-1.22.0-88-gde0bdc1-4.8.5/xtensa-lx106-elf/bin/:$PATH
if [ "$1" = 2 ];
	then
	make clean
fi

make all