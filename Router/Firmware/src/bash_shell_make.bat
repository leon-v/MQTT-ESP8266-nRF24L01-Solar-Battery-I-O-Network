@ECHO OFF &SETLOCAL

ECHO Killing previous PIDs......
tasklist /v /fo csv | findstr /i "Build-Upload" > pid.csv
FOR /F "tokens=1,2* delims=,? " %%a in (pid.csv) do (
	Taskkill /PID %%b /F
)
del pid.csv

title=Build-Upload

ECHO Building source......
set LinuxPath=%~dp0
set LinuxPath=%LinuxPath:C:=/mnt/c%
set LinuxPath=%LinuxPath:\=/%
set LinuxPath=%LinuxPath%
bash -ilc "cd %LinuxPath%; dos2unix  ./bash_shell_make.sh; ./bash_shell_make.sh %1"

if %errorlevel% neq 0 exit /b %errorlevel%

echo Build Success, Uploading....

set comport=COM5

esptool.py --chip esp32 --port %comport% --baud 115200 --before default_reset --after hard_reset write_flash -z --flash_mode dio --flash_freq 40m --flash_size detect 0x1000  "build\bootloader\bootloader.bin" 0x10000 "build\BeelineRouter.bin"	0x8000  "build\partitions_singleapp.bin"

IF NOT "%errorlevel%" == "0" (
	echo Upload Failed & exit /b
)

miniterm.py %comport% 115200

REM #..\esp-idf\tools\idf_monitor.py --port %comport% --baud 115200 ./build/BeelineRouter.elf