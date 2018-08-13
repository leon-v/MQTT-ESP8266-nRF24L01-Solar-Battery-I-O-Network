#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "configFlash.h"
#include "httpServer.h"

void httpServerPagePostIndex(char * payload){

	tokens_t post;

	httpServerParseValues(&post, payload, "&", "=", "");

	char * value;

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
	if (value){
		strcpy(configFlash.mqttPassword, value);
	}


	configFlashSave();
}
char * httpServerPageGetIndex(void){

	configFlashLoad();

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
