

#include <string.h>
#include <stdlib.h>


#include "httpd.h"
#include "lwip/stats.h"
#include "httpd_opts.h"

#include "configFlash.h"
#include "radio.h"
#include "mqtt_connection.h"

/* Server-Side Include (SSI) demo ..........................................*/
static const char * ssi_tags[] = {
    "wifiSSID",					//0
    "wifiPassword",				//1
    "mqttHost",					//2
    "mqttPort",					//3
    "mqttKeepalive",			//4
    "mqttUsername",				//5
    "mqttPassword",				//6

    "mqttConnectionSuccess",	//7
    "mqttConnectionFail",		//8
    "mqttPublish",				//9
    "mqttDump",					//10

    "radioNrf24l01In",			//11
};

typedef struct{
	char * key;
	char * value;
} token_t;

typedef struct{
	token_t tokens[32];
	unsigned int length;
} tokens_t;

char * httpServerParseValues(tokens_t * tokens, char * buffer, const char * rowDelimiter, const char * valueDelimiter, const char * endMatch){

	tokens->length = 0;

	// Start parsing the values by creating a new string from the payload 
	char * token = strtok(buffer, rowDelimiter);

	char * end = buffer + strlen(buffer);

	// break apart the string getting all the parts delimited by &
	while (token != NULL) {

		if (strlen(endMatch) > 0){
			end = token + strlen(token) + 1;

			if (strncmp(end, endMatch, strlen(endMatch)) == 0) {
				end+= strlen(endMatch);
				break;
			}
		}

		tokens->tokens[tokens->length++].key = token;

		token = strtok(NULL, rowDelimiter);
	}

	// Re-parse the strigns and break them apart into key / value pairs
	for (unsigned int index = 0; index < tokens->length; index++){

		tokens->tokens[index].key = strtok(tokens->tokens[index].key, valueDelimiter);

		tokens->tokens[index].value = strtok(NULL, valueDelimiter);

		// If the value is NULL, make it point to an empty string.
		if (tokens->tokens[index].value == NULL){
			tokens->tokens[index].value = tokens->tokens[index].key + strlen(tokens->tokens[index].key);
		}
	}

	return end;
}

char * httpServerGetTokenValue(tokens_t * tokens, const char * key){

	for (unsigned int index = 0; index < tokens->length; index++){

		if (strcmp(tokens->tokens[index].key, key) == 0){
			return tokens->tokens[index].value;
		}
	}

	return NULL;
}

#define HTML_INPUT_STRING "<input type=\"%s\" name=\"%s\" value=\"%s\" />"
#define HTML_INPUT_INT "<input type=\"%s\" name=\"%s\" value=\"%u\" />"
#define HTML_ULONG "%lu"
#define HTML_UINT "%u"
/* Server-Side Include (SSI) handler .......................................*/
int ssi_handler(int iIndex, char *pcInsert, int iInsertLen) {

	radioStatus_t radioStatus = radioGetStatus();
	mqttStatus_t mqttStatus = mqtt_connection_get_status();

	strcpy(pcInsert, "");
	switch (iIndex){
		case 0:
			sprintf(pcInsert, HTML_INPUT_STRING, "text", "wifiSSID", configFlash.wifiSSID);
			break;

		case 1:
			sprintf(pcInsert, HTML_INPUT_STRING, "password", "wifiPassword", configFlash.wifiPassword);
			break;

		case 2:
			sprintf(pcInsert, HTML_INPUT_STRING, "text", "mqttHost", configFlash.mqttHost);
			break;

		case 3:
			sprintf(pcInsert, HTML_INPUT_INT, "number", "mqttPort", configFlash.mqttPort);
			break;

		case 4:
			sprintf(pcInsert, HTML_INPUT_INT, "number", "mqttKeepalive", configFlash.mqttKeepalive);
			break;

		case 5:
			sprintf(pcInsert, HTML_INPUT_STRING, "text", "mqttUsername", configFlash.mqttUsername);
			break;

		case 6:
			sprintf(pcInsert, HTML_INPUT_STRING, "password", "mqttPassword", configFlash.mqttPassword);
			break;

		case 7:
			sprintf(pcInsert, HTML_ULONG, mqttStatus.connectionSuccess);
			break;

		case 8:
			sprintf(pcInsert, HTML_ULONG, mqttStatus.connectionFail);
			break;

		case 9:
			sprintf(pcInsert, HTML_ULONG, mqttStatus.Publish);
			break;

		case 10:
			sprintf(pcInsert, HTML_ULONG, mqttStatus.Dump);
			break;

		case 11:
			sprintf(pcInsert, HTML_ULONG, radioStatus.nrf24l01In);
			break;

		default:
			sprintf(pcInsert, "NULL");
			break;
	}

	return strlen(pcInsert);
}

void httpd_custom_init(void){
	http_set_ssi_handler( (tSSIHandler) &ssi_handler, ssi_tags, sizeof(ssi_tags));
}


const char * request_uri = NULL;
err_t httpd_post_begin(void *connection, const char *uri, const char *http_request, u16_t http_request_len, int content_len, char *response_uri, u16_t response_uri_len, u8_t *post_auto_wnd){

	request_uri = uri;
	
	printf("%s\n", uri);
	// printf("%s\n", http_request);
	return ERR_OK;
}

err_t httpd_post_receive_data(void *connection, struct pbuf *p){
	printf("httpd_post_receive_data\n");

	tokens_t post;

	char * payload = (char *) p->payload;
	payload[p->len] = '\0';
	
	printf("post: %s\n", (char *) payload);
	printf("post Len: %d\n", p->len);
	httpServerParseValues(&post, (char *) payload, "&", "=", "");

	char * value;

	if (strcmp(request_uri, "/config.shtml?a=save") == 0){

		value = httpServerGetTokenValue(&post, "wifiSSID");
		if (value){
			strcpy(configFlash.wifiSSID, value);
		}

		value = httpServerGetTokenValue(&post, "wifiPassword");
		if (value){
			strcpy(configFlash.wifiPassword, value);
		}

		value = httpServerGetTokenValue(&post, "mqttHost");
		if (value){
			strcpy(configFlash.mqttHost, value);
		}

		value = httpServerGetTokenValue(&post, "mqttPort");
		if (value){
			configFlash.mqttPort = atoi(value);
		}

		value = httpServerGetTokenValue(&post, "mqttKeepalive");
		if (value){
			configFlash.mqttKeepalive = atoi(value);
		}

		value = httpServerGetTokenValue(&post, "mqttUsername");
		if (value){
			strcpy(configFlash.mqttUsername, value);
		}

		value = httpServerGetTokenValue(&post, "mqttPassword");
		printf("mqttPassword: '%s'\n", value);
		if (value){
			strcpy(configFlash.mqttPassword, value);
		}

		value = httpServerGetTokenValue(&post, "mqttVersion");
		if (value){
			configFlash.mqttVersion = atoi(value);
		}

		value = httpServerGetTokenValue(&post, "debugLevel");
		if (value){
			configFlash.debugLevel = atoi(value);
		}

		configFlashSave();

	}

	return ERR_OK;
}

void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len){

	printf("httpd_post_finished\n");

	strcpy(response_uri, request_uri);
	response_uri_len = strlen(response_uri);

	printf("%s", response_uri);

	request_uri = NULL;
}