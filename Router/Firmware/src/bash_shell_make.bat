REM @ECHO OFF &SETLOCAL

set LinuxPath=%~dp0
set LinuxPath=%LinuxPath:C:=/mnt/c%
set LinuxPath=%LinuxPath:\=/%
set LinuxPath=%LinuxPath%
bash -c "cd %LinuxPath%; dos2unix  ./bash_shell_make.sh; ./bash_shell_make.sh %1"
echo "Result: %ERRORLEVEL%"

if %errorlevel% neq 0 exit /b %errorlevel%

set comport=COM3

esptool.py --chip esp8266 --port %comport% --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode qio --flash_freq 40m --flash_size 2MB 0x0000 ../build/bootloader/bootloader.bin 0x10000 ../build/MQTTRouter.bin 0x8000 ../build/partitions_singleapp.bin

if NOT "%errorlevel%" == "0" echo Upload Failed & exit /b

miniterm.py %comport% 74880