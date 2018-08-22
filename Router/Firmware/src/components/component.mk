#
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += httpd_custom\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/include/lwip/apps

COMPONENT_SRCDIRS += httpd_custom\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd\

ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd/fs.o: CFLAGS += -DHTTPD_USE_CUSTOM_FSDATA=1
ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd/httpd.o: CFLAGS += -DLWIP_HTTPD_SSI=1 -DLWIP_HTTPD_DYNAMIC_HEADERS=1

