#
# Component Makefile
#
COMPONENT_ADD_INCLUDEDIRS += httpd_custom mqtt_connection\
	../main\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/include/lwip/apps

COMPONENT_SRCDIRS += httpd_custom mqtt_connection\
	../../ESP8266_RTOS_SDK/components/lwip/lwip/src/apps/httpd

