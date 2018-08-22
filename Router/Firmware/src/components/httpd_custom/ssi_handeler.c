
#include "httpd.h"
#include "lwip/stats.h"
#include "httpd_opts.h"
#include "../../main/configFlash.h"

/* Server-Side Include (SSI) demo ..........................................*/
static char const * const ssi_tags[] = {
    "wssid",
    "wpass"
};


/* Server-Side Include (SSI) handler .......................................*/
static int ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {

    switch (iIndex) {
        case 0:
			return snprintf(pcInsert, LWIP_HTTPD_MAX_TAG_INSERT_LEN, "%s", configFlash.wifiSSID);
            break;
        case 1:
            return snprintf(pcInsert, LWIP_HTTPD_MAX_TAG_INSERT_LEN, "%s", configFlash.mqttPassword);
            break;
    }
}

void ssi_init(void){
	http_set_ssi_handler(&ssi_handler, ssi_tags, 2);
}