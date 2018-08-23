#
# This is a project Makefile. It is assumed the directory this Makefile resides in is a
# project subdirectory.
#

PROJECT_NAME := MQTTRouter

CFLAGS += -DHTTPD_USE_CUSTOM_FSDATA=1
CFLAGS += -DLWIP_HTTPD_SSI=1
CFLAGS += -DLWIP_HTTPD_DYNAMIC_HEADERS=1
CFLAGS += -DLWIP_HTTPD_MAX_TAG_NAME_LEN=16
CFLAGS += -DLWIP_HTTPD_SUPPORT_POST=1

include $(IDF_PATH)/make/project.mk

