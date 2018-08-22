#
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += httpd_custom

COMPONENT_SRCDIRS += httpd_custom\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd\

CFLAGS += -Wno-address #lots of LWIP source files evaluate macros that check address of stack variables

ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd/fs.o: CFLAGS += -DHTTPD_USE_CUSTOM_FSDATA=1
