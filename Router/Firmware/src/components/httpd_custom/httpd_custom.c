
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


#include "httpd.h"
#include "lwip/stats.h"
#include "httpd_opts.h"

#include "configFlash.h"
#include "radio.h"
#include "mqtt_connection.h"

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
#define HTML_TEXTAREA "<textarea rows=\"%d\" name=\"%s\" >%s</textarea>"
#define HTML_ULONG "%lu"
#define HTML_UINT "%u"
/* Server-Side Include (SSI) handler .......................................*/

int ssi_handler(const char* ssi_tag_name, char *pcInsert, int iInsertLen) {

	radioStatus_t radioStatus = radioGetStatus();
	mqttStatus_t mqttStatus = mqtt_connection_get_status();

	if (strcmp(ssi_tag_name, "wifiSSID") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "text", "wifiSSID", configFlash.wifiSSID);
	}
	else if (strcmp(ssi_tag_name, "wifiPassword") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "password", "wifiPassword", configFlash.wifiPassword);
	}
	else if (strcmp(ssi_tag_name, "mqttHost") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "text", "mqttHost", configFlash.mqttHost);
	}
	else if (strcmp(ssi_tag_name, "mqttPort") == 0) {
		sprintf(pcInsert, HTML_INPUT_INT, "number", "mqttPort", configFlash.mqttPort);
	}
	else if (strcmp(ssi_tag_name, "mqttKeepalive") == 0) {
		sprintf(pcInsert, HTML_INPUT_INT, "number", "mqttKeepalive", configFlash.mqttKeepalive);
	}
	else if (strcmp(ssi_tag_name, "mqttUsername") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "text", "mqttUsername", configFlash.mqttUsername);
	}
	else if (strcmp(ssi_tag_name, "mqttPassword") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "password", "mqttPassword", configFlash.mqttPassword);
	}
	else if (strcmp(ssi_tag_name, "mqttConnected") == 0) {
		if (mqttStatus.connected){
			sprintf(pcInsert, "Yes");
		} else{
			sprintf(pcInsert, "No");
		}
	}
	else if (strcmp(ssi_tag_name, "mqttConnectionSuccess") == 0) {
		sprintf(pcInsert, HTML_ULONG, mqttStatus.connectionSuccess);
	}
	else if (strcmp(ssi_tag_name, "mqttConnectionFail") == 0) {
		sprintf(pcInsert, HTML_ULONG, mqttStatus.connectionFail);
	}
	else if (strcmp(ssi_tag_name, "mqttPublish") == 0) {
		sprintf(pcInsert, HTML_ULONG, mqttStatus.Publish);
	}
	else if (strcmp(ssi_tag_name, "mqttDump") == 0) {
		sprintf(pcInsert, HTML_ULONG, mqttStatus.Dump);
	}
	else if (strcmp(ssi_tag_name, "radioNrf24l01In") == 0) {
		sprintf(pcInsert, HTML_ULONG, radioStatus.nrf24l01In);
	}
	else if (strcmp(ssi_tag_name, "elasticHost") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "text", "elasticHost", configFlash.elasticHost);
	}
	else if (strcmp(ssi_tag_name, "elasticUser") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "text", "elasticUser", configFlash.elasticUser);
	}
	else if (strcmp(ssi_tag_name, "elasticPassword") == 0) {
		sprintf(pcInsert, HTML_INPUT_STRING, "password", "elasticPassword", configFlash.elasticPassword);
	}
	else{
		sprintf(pcInsert, "NULL");
	}

	iInsertLen = strlen(pcInsert);

	return iInsertLen;
}

void httpd_custom_init(void){
	httpd_init();
	http_set_ssi_handler( (tSSIHandler) &ssi_handler, NULL, NULL);
}


void urlDecode(char * input, int length) {
    
    char * output = input;
    char hex[3] = "\0\0\0";

    while (input[0] != '\0') {

    	if (!length--){
    		break;
    	}


    	if (input[0] == '+') {
    		input[0] = ' ';
    		input+= 1;
    	}

    	else if (input[0] == '%') {

    		// printf("1: %d\n", input[1]);
    		// printf("2: %d\n", input[2]);

    		hex[0] = input[1];
    		hex[1] = input[2];
    		output[0] = strtol(hex, NULL, 16);
    		// printf("O: %d\n", input[2]);
    		input+= 3;
    	}

    	else{
    		output[0] = input[0];
    		input+= 1;
    	}

    	output+= 1;
    }

    output[0] = '\0';
}


const char * request_uri = NULL;

char postBuffer[2048];

err_t httpd_post_begin(void *connection, const char *uri, const char *http_request, u16_t http_request_len, int content_len, char *response_uri, u16_t response_uri_len, u8_t *post_auto_wnd){

	request_uri = uri;

	postBuffer[0] = '\0';
	
	return ERR_OK;
}

err_t httpd_post_receive_data(void * hs, struct pbuf *p){

	printf("httpd_post_receive_data\n");

	unsigned int total = strlen(postBuffer) + p->len;
	
	if (total > sizeof(postBuffer)) {
		printf("httpd_post_receive_data postBuffer too small %d\n", total);
	}

	char * payload = (char *) p->payload;

	strncat(postBuffer, payload, p->len);

	return ERR_OK;

}

void httpd_post_finished(void *connection, char *response_uri, u16_t response_uri_len){

	printf("httpd_post_finished\n");

	tokens_t post;
	
	// printf("post: %s\n", (char *) postBuffer);
	printf("post postBuffer length: %d\n", strlen(postBuffer));
	printf("postrequest_uri  %s\n", request_uri);

	// return ERR_OK;
	httpServerParseValues(&post, (char *) postBuffer, "&", "=", "");

	char * value;

	if (strcmp(request_uri, "/config.shtml?a=save") == 0){

		value = httpServerGetTokenValue(&post, "wifiSSID");
		if (value){
			urlDecode(value, sizeof(configFlash.wifiSSID));
			strncpy(configFlash.wifiSSID, value, sizeof(configFlash.wifiSSID));
		}

		value = httpServerGetTokenValue(&post, "wifiPassword");
		if (value){
			urlDecode(value, sizeof(configFlash.wifiPassword));
			strncpy(configFlash.wifiPassword, value, sizeof(configFlash.wifiPassword));
		}

		value = httpServerGetTokenValue(&post, "mqttHost");
		if (value){
			urlDecode(value, sizeof(configFlash.mqttHost));
			strncpy(configFlash.mqttHost, value, sizeof(configFlash.mqttHost));
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
			urlDecode(value, sizeof(configFlash.mqttUsername));
			strncpy(configFlash.mqttUsername, value, sizeof(configFlash.mqttUsername));
		}

		value = httpServerGetTokenValue(&post, "mqttPassword");
		printf("mqttPassword: '%s'\n", value);
		if (value){
			urlDecode(value, sizeof(configFlash.mqttPassword));
			strncpy(configFlash.mqttPassword, value, sizeof(configFlash.mqttPassword));
		}

		value = httpServerGetTokenValue(&post, "mqttVersion");
		if (value){
			configFlash.mqttVersion = atoi(value);
		}

		value = httpServerGetTokenValue(&post, "debugLevel");
		if (value){
			configFlash.debugLevel = atoi(value);
		}

		value = httpServerGetTokenValue(&post, "elasticHost");
		urlDecode(value, sizeof(configFlash.elasticHost));
		if (value){
			urlDecode(value, sizeof(configFlash.elasticHost));
			strncpy(configFlash.elasticHost, value, sizeof(configFlash.elasticHost));
		}

		value = httpServerGetTokenValue(&post, "elasticUser");
		if (value){
			urlDecode(value, sizeof(configFlash.elasticUser));
			strncpy(configFlash.elasticUser, value, sizeof(configFlash.elasticUser));
		}

		value = httpServerGetTokenValue(&post, "elasticPassword");
		if (value){
			urlDecode(value, sizeof(configFlash.elasticPassword));
			strncpy(configFlash.elasticPassword, value, sizeof(configFlash.elasticPassword));
		}

		configFlashSave();

	}

	strcpy(response_uri, request_uri);

	response_uri_len = strlen(response_uri);

	request_uri = NULL;
}