
#include <string.h>

#include "httpd.h"
#include "lwip/stats.h"
#include "httpd_opts.h"
#include "../../main/configFlash.h"
/* Server-Side Include (SSI) demo ..........................................*/
static const char * ssi_tags[] = {
    "wifiSSID",
    "wifiPassword",
    "mqttHost",
    "mqttPort",
    "mqttKeepalive",
    "mqttUsername",
    "mqttPassword"
};

#define INPUT_STRING "<input type=\"%s\" name=\"%s\" value=\"%s\" />"
#define INPUT_INT "<input type=\"%s\" name=\"%s\" value=\"%u\" />"
/* Server-Side Include (SSI) handler .......................................*/
int ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {

	strcpy(pcInsert, "");
	switch (iIndex){
		case 0:
			sprintf(pcInsert, INPUT_STRING, "text", "wifiSSID", configFlash.wifiSSID);
			break;

		case 1:
			sprintf(pcInsert, INPUT_STRING, "password", "wifiPassword", configFlash.wifiPassword);
			break;

		case 2:
			sprintf(pcInsert, INPUT_STRING, "text", "mqttHost", configFlash.mqttHost);
			break;

		case 3:
			sprintf(pcInsert, INPUT_INT, "number", "mqttPort", configFlash.mqttPort);
			break;

		case 4:
			sprintf(pcInsert, INPUT_INT, "number", "mqttKeepalive", configFlash.mqttKeepalive);
			break;

		case 5:
			sprintf(pcInsert, INPUT_STRING, "text", "mqttUsername", configFlash.mqttUsername);
			break;

		case 6:
			sprintf(pcInsert, INPUT_STRING, "password", "mqttPassword", configFlash.mqttPassword);
			break;
	}

	return strlen(pcInsert);
}

void ssi_init(void){
	http_set_ssi_handler( (tSSIHandler) &ssi_handler, ssi_tags, sizeof(ssi_tags));
}
