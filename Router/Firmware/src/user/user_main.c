/* main.c -- MQTT client example
*
* Copyright (c) 2014-2015, Tuan PM <tuanpm at live dot com>
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* * Redistributions of source code must retain the above copyright notice,
* this list of conditions and the following disclaimer.
* * Redistributions in binary form must reproduce the above copyright
* notice, this list of conditions and the following disclaimer in the
* documentation and/or other materials provided with the distribution.
* * Neither the name of Redis nor the names of its contributors may be used
* to endorse or promote products derived from this software without
* specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
* LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
* CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
* SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
* INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
* CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*/
#include "ets_sys.h"
#include "driver/uart.h"
#include "osapi.h"
#include "mqtt.h"
#include "wifi.h"
#include "config.h"
#include "debug.h"
#include "gpio.h"
#include "user_interface.h"
#include "mem.h"
#include "radio_app.h"


MQTT_Client mqttClient;
typedef unsigned long u32_t;
static ETSTimer sntp_timer;

void sntpfn(){
    u32_t ts = 0;
    ts = sntp_get_current_timestamp();
    os_printf("current time : %s\n", sntp_get_real_time(ts));
    if (ts == 0) {
        //os_printf("did not get a valid time from sntp server\n");
    } else {
            os_timer_disarm(&sntp_timer);
            MQTT_Connect(&mqttClient);
    }
}

void wifiConnectCb(uint8_t status) {
    if(status == STATION_GOT_IP){
        sntp_setservername(0, "pool.ntp.org");        // set sntp server after got ip address
        sntp_init();
        os_timer_disarm(&sntp_timer);
        os_timer_setfn(&sntp_timer, (os_timer_func_t *)sntpfn, NULL);
        os_timer_arm(&sntp_timer, 1000, 1);//1s
    } else {
          MQTT_Disconnect(&mqttClient);
          radioEnable(0);
    }
}

void ICACHE_FLASH_ATTR mqttConnectedCb(uint32_t *args){

	MQTT_Client* client = (MQTT_Client*)args;

	
	INFO("MQTT: Connected\r\n");
	// nrf24l01Unpause();
	// MQTT_Publish(client, "/sensor/test/online", "1", 1, 1, 1);
	// MQTT_InitLWT(client, "/sensor/test/online", "0", 1, 1);
	
	// MQTT_Publish(client, "/sensor/test/max", "4500", 4, 1, 1);
	// MQTT_Publish(client, "/sensor/test/min", "2500", 4, 1, 1);

	// MQTT_Subscribe(client, "/mqtt/topic/0", 0);
	// MQTT_Subscribe(client, "/mqtt/topic/1", 1);
	// MQTT_Subscribe(client, "/mqtt/topic/2", 2);
	// MQTT_Subscribe(client, "/sensor/test/0", 0);

	// MQTT_Publish(client, "/mqtt/topic/0", "hello0", 6, 0, 0);
	// MQTT_Publish(client, "/mqtt/topic/1", "hello1", 6, 1, 0);
	// MQTT_Publish(client, "/mqtt/topic/2", "hello2", 6, 2, 0);

	//sleepSetEnable();
	radioInit(&mqttClient);
	radioEnable(1);
}

void ICACHE_FLASH_ATTR mqttDisconnectedCb(uint32_t *args){
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Disconnected\r\n");
	radioEnable(0);
}

void ICACHE_FLASH_ATTR mqttPublishedCb(uint32_t *args){
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Published\r\n");

	//sleepSetEnable();
}


void mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len) {
    char *topicBuf = (char*)os_zalloc(topic_len+1), *dataBuf = (char*)os_zalloc(data_len+1);

    MQTT_Client* client = (MQTT_Client*)args;

    os_memcpy(topicBuf, topic, topic_len);
    topicBuf[topic_len] = 0;

    os_memcpy(dataBuf, data, data_len);
    dataBuf[data_len] = 0;

    INFO("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);
    os_free(topicBuf);
    os_free(dataBuf);
}



/******************************************************************************
 * FunctionName : user_rf_cal_sector_set
 * Description  : SDK just reversed 4 sectors, used for rf init data and paramters.
 *                We add this function to force users to set rf cal sector, since
 *                we don't know which sector is free in user's application.
 *                sector map for last several sectors : ABCCC
 *                A : rf cal
 *                B : rf init data
 *                C : sdk parameters
 * Parameters   : none
 * Returns      : rf cal sector
 *******************************************************************************/
uint32 ICACHE_FLASH_ATTR
user_rf_cal_sector_set(void)
{
    enum flash_size_map size_map = system_get_flash_size_map();
    uint32 rf_cal_sec = 0;

    switch (size_map) {
        case FLASH_SIZE_4M_MAP_256_256:
            rf_cal_sec = 128 - 5;
            break;

        case FLASH_SIZE_8M_MAP_512_512:
            rf_cal_sec = 256 - 5;
            break;

        case FLASH_SIZE_16M_MAP_512_512:
        case FLASH_SIZE_16M_MAP_1024_1024:
            rf_cal_sec = 512 - 5;
            break;

        case FLASH_SIZE_32M_MAP_512_512:
        case FLASH_SIZE_32M_MAP_1024_1024:
            rf_cal_sec = 1024 - 5;
            break;

        case FLASH_SIZE_64M_MAP_1024_1024:
            rf_cal_sec = 2048 - 5;
            break;
        case FLASH_SIZE_128M_MAP_1024_1024:
            rf_cal_sec = 4096 - 5;
            break;
        default:
            rf_cal_sec = 0;
            break;
    }

    return rf_cal_sec;
}

void ICACHE_FLASH_ATTR user_init(void){

	INFO("\r\nBOOT\r\n");
	
	// system_set_os_print(0);
	// INFO("\r\nDEBUG DISABLE\r\n");

	
	//uart_init(BIT_RATE_115200, BIT_RATE_115200);
	os_delay_us(65535);

	struct rst_info* resetInfo;
	resetInfo = system_get_rst_info();

	os_printf("RR: %d\r\n", resetInfo->reason);

	CFG_Load();

	gpio_init();

	gpio_output_set(BIT2,0, BIT2, 0); // LED OFF (Some ESPs use pin 1)

	// PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U, FUNC_GPIO4);
	// GPIO_DIS_OUTPUT(4);
	PIN_PULLUP_EN(PERIPHS_IO_MUX_GPIO4_U);

	// (high, low, out, in)
	gpio_output_set(BIT4, 0, BIT4, 0);
	gpio_output_set(BIT4, 0, BIT4, 0);
	os_delay_us(65535);
	os_delay_us(65535);
	gpio_output_set(0, BIT4, 0, BIT4);// Bit 4 input


	// if (resetInfo->reason != 4){
	if (!GPIO_INPUT_GET(4)){
	 // if (1){
			INFO("\r\nStarting HTTP Config ....\r\n");
		HTTPConfig_Init();
	}

	else{

		INFO("\r\nStarting MQTT ....\r\n");

		MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, 0);//sysCfg.security

		INFO("MQTT: Init: device_id %s\r\n", sysCfg.device_id);
		INFO("MQTT: Init: mqtt_user %s\r\n", sysCfg.mqtt_user);
		INFO("MQTT: Init: mqtt_keepalive %u\r\n", sysCfg.mqtt_keepalive);

		MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);

		MQTT_OnConnected(&mqttClient, mqttConnectedCb);
		MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
		MQTT_OnPublished(&mqttClient, mqttPublishedCb);
		MQTT_OnData(&mqttClient, mqttDataCb);

		WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);

		INFO("\r\nSystem started ...\r\n");	
	}
}


// 638 = 3.3

// 638 / 1024 = 0.623046875
// 2048 / 3300 = 0.6206060606060606

// 321 / 1024 / 0.3134765625
// 1024 / 3300 = 0.3103030303030303

// * 1028
// 

// 81855 / 255 * 10.3
// 3413