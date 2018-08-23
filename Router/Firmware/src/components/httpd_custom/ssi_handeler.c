
#include <string.h>

#include "httpd.h"
#include "lwip/stats.h"
#include "httpd_opts.h"
#include "../../main/configFlash.h"

/* Server-Side Include (SSI) demo ..........................................*/
static const char * ssi_tags[] = {
    "wifiSSID",
    "wifiPassword"
};

/* Server-Side Include (SSI) handler .......................................*/
int ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {

	strcpy(pcInsert, "");
	printf("ssi_handler\n");
	switch (iIndex){
		case 0:
			strcpy(pcInsert, configFlash.wifiSSID);
		break;

		case 1:
			strcpy(pcInsert, configFlash.wifiPassword);
		break;
	}

	return strlen(pcInsert);
}

void ssi_init(void){
	http_set_ssi_handler( (tSSIHandler) &ssi_handler, ssi_tags, 2);
}
