#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "configFlash.h"


typedef struct{
	char * key;
	char * value;
} token_t;

typedef struct{
	token_t tokens[8];
	unsigned int length;
} tokens_t;

tokens_t * httpServerPageParsePost(char * payload){
	
	tokens_t post;
	post.length = 0;

	printf("Data: %s\n", payload);

	char * token = strtok(payload, "&");

	while (token != NULL){
		post.tokens[post.length++].key = token;
		token = strtok(NULL, "&");
	}

	unsigned int index;
	for (index = 0; index < post.length; index++){
		post.tokens[index].key = strtok(post.tokens[index].key, "=");
		post.tokens[index].value = strtok(NULL, "=");

		if (post.tokens[index].value == NULL){
			post.tokens[index].value = post.tokens[index].key + strlen(post.tokens[index].key);
		}
		printf("Key: %s, Value: %s\n", post.tokens[index].key, post.tokens[index].value);
	}
}
void httpServerPagePostIndex(char * payload){

	tokens_t post;
	post.length = 0;

	printf("Data: %s\n", payload);

	char * token = strtok(payload, "&");

	while (token != NULL){
		post.tokens[post.length++].key = token;
		token = strtok(NULL, "&");
	}

	unsigned int index;
	for (index = 0; index < post.length; index++){
		post.tokens[index].key = strtok(post.tokens[index].key, "=");
		post.tokens[index].value = strtok(NULL, "=");

		if (post.tokens[index].value == NULL){
			post.tokens[index].value = post.tokens[index].key + strlen(post.tokens[index].key);
		}
		printf("Key: %s, Value: %s\n", post.tokens[index].key, post.tokens[index].value);
	}
	
}
char * httpServerPageGetIndex(void){

	static const char PageIndex[] = "\
		<!DOCTYPE html>\
		<html>\
		<head>\
			<title>ESP8266 Configuration</title>\
		</head>\
		<body>\
			<h3>ESP8266 Configuration</h3>\
			<form method=\"post\">\
				<table>\
					<tbody>\
						<tr>\
							<th colspan='2' >WiFi Configuration</th>\
						</tr>\
						<tr>\
							<th>WiFi SSID</th>\
							<td><input type='text' name=\"wifiSSID\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<th>WiFi Password</th>\
							<td><input type='password' name=\"wifiPassword\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<td colspan=\"2\" ><hr></td>\
						</tr>\
						<tr>\
							<th colspan='2' >MQTT Configuration</th>\
						</tr>\
						<tr>\
							<th>MQTT Host</th>\
							<td><input type='text' name=\"mqttHost\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<th>MQTT Port</th>\
							<td><input type='text' name=\"mqttPort\" value=\"%i\" ></td>\
						</tr>\
						<tr>\
							<th>MQTT Keepalive (sec)</th>\
							<td><input type='text' name=\"mqttKeepalive\" value=\"%i\" ></td>\
						</tr>\
						<tr>\
							<th>MQTT Username</th>\
							<td><input type='text' name=\"mqttUsername\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<th>MQTT Password</th>\
							<td><input type='password' name=\"mqttPassword\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<td colspan\"2\" ><button>Save</button></td>\
						</tr>\
					</tbody>\
				</table>\
			</form>\
		</body>\
	";
	#define PageIndexParams configFlash.wifiSSID, configFlash.wifiPassword, configFlash.mqttHost, configFlash.mqttPort,\
		configFlash.mqttKeepalive, configFlash.mqttUsername, configFlash.mqttPassword

	size_t needed = snprintf(NULL, 0, PageIndex, PageIndexParams) + 1;
	char  *html = malloc(needed);
	snprintf(html, needed, PageIndex, PageIndexParams);
    return html;
}


char * httpServerPageGet(char * method, char * uri, char * payload){

	if (strcmp(uri, "/") == 0){

		if (strcmp(method, "POST") == 0){
			httpServerPagePostIndex(payload);
		}
		return httpServerPageGetIndex();
	}

	return NULL;
}
