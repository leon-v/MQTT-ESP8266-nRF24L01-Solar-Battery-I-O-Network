#
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += httpd_custom\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/include/lwip/apps

COMPONENT_SRCDIRS += httpd_custom\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd\

# ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd/fs.o: CFLAGS += 
# ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd/httpd.o: CFLAGS += 
# ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd/httpd.o: CFLAGS += 

