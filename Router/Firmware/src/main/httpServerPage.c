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

	value = httpServerGetTokenValue(&post, "mqttVersion");
	if (value){
		configFlash.mqttVersion = atoi(value);
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
		<style type='text/css'>\
			*{\
				box-sizing: border-box;\
			}\
			body{\
				font-family: Arial;\
				color: #ede5ff;\
				background-color:#262626;\
			}\
			td{\
				width:200px;\
			}\
			th{\
				text-align: left;\
				width:125px;\
				font-size: 14px;\
			}\
			input, select, button{\
				background-color:#262626;\
				color: #ede5ff;\
				border:1px solid #ffffff;\
				padding:3px;\
				margin:0px;\
				margin-bottom:-4px;\
				font-size: 14px;\
				width:100%%;\
			}\
			button{\
				margin-top:5px;\
				\
			}\
			.roundTop{\
				border-top-right-radius: 5px;\
				border-top-left-radius: 5px;\
			}\
			.roundBotton{\
				border-bottom-right-radius: 5px;\
				border-bottom-left-radius: 5px;\
			}\
		</style>\
	</head>\
	<body>\
		<h2>ESP8266 Configuration</h2>\
		<form method='post'>\
			<table>\
				<tbody>\
					<tr>\
						<th colspan='2'><h3>WiFi Configuration</h3></th>\
					</tr>\
					<tr>\
						<th>WiFi SSID</th>\
						<td><input type='text' name='wifiSSID' value='%s' class='roundTop'></td>\
					</tr>\
					<tr>\
						<th>WiFi Password</th>\
						<td><input type='password' name='wifiPassword' value='%s' class='roundBotton'></td>\
					</tr>\
					<tr>\
						<td colspan='2'><hr></td>\
					</tr>\
					<tr>\
						<th colspan='2'><h3>MQTT Configuration</h3></th>\
					</tr>\
					<tr>\
						<th>Host</th>\
						<td><input type='text' name='mqttHost' value='%s' class='roundTop'></td>\
					</tr>\
					<tr>\
						<th>Port</th>\
						<td><input type='text' name='mqttPort' value='%d'></td>\
					</tr>\
					<tr>\
						<th>Keepalive (sec)</th>\
						<td><input type='text' name='mqttKeepalive' value='%d'></td>\
					</tr>\
					<tr>\
						<th>Username</th>\
						<td><input type='text' name='mqttUsername' value='%s'></td>\
					</tr>\
					<tr>\
						<th>Password</th>\
						<td><input type='password' name='mqttPassword' value='%s' ></td>\
					</tr>\
					<tr>\
						<th>Version</th>\
						<td>\
							<select name='mqttVersion' id='mqttVersion' class='roundBotton' value='%d'>\
								<option value='3'>3.1</option>\
								<option value='4'>3.1.1</option>\
							</select>\
							<script type='text/javascript'>\
								var select = document.getElementById('mqttVersion');\
								select.value = select.getAttribute('value');\
							</script>\
						</td>\
					</tr>\
					<tr>\
						<td colspan='2'><button class='roundTop roundBotton'>Save</button></td>\
					</tr>\
				</tbody>\
			</table>\
		</form>\
	</body>\
</html>";
	#define PageIndexParams configFlash.wifiSSID, configFlash.wifiPassword,\
		configFlash.mqttHost,\
		configFlash.mqttPort, configFlash.mqttKeepalive,\
		configFlash.mqttUsername, configFlash.mqttPassword,\
		configFlash.mqttVersion

	size_t needed = snprintf(NULL, 0, PageIndex, PageIndexParams) + 1;
	char  *html = malloc(needed);
	snprintf(html, needed, PageIndex, PageIndexParams);
    return html;
}

char * httpServerPageGetStatus(void){

	static const char PageIndex[] = "\
<!DOCTYPE html>\
<html>\
	<head>\
		<title>ESP8266 Status</title>\
		<style type='text/css'>\
			*{\
				box-sizing: border-box;\
			}\
			body{\
				font-family: Arial;\
				color: #ede5ff;\
				background-color:#262626;\
			}\
			td{\
				width:200px;\
			}\
			th{\
				text-align: left;\
				width:125px;\
				font-size: 14px;\
			}\
			input, select, button{\
				background-color:#262626;\
				color: #ede5ff;\
				border:1px solid #ffffff;\
				padding:3px;\
				margin:0px;\
				margin-bottom:-4px;\
				font-size: 14px;\
				width:100%%;\
			}\
			button{\
				margin-top:5px;\
				\
			}\
			.roundTop{\
				border-top-right-radius: 5px;\
				border-top-left-radius: 5px;\
			}\
			.roundBotton{\
				border-bottom-right-radius: 5px;\
				border-bottom-left-radius: 5px;\
			}\
		</style>\
	</head>\
	<body>\
		<h2>ESP8266 Status</h2>\
		<form method='post'>\
			<table>\
				<tbody>\
					<tr>\
						<th colspan='2'><h3>MQTT Status</h3></th>\
					</tr>\
					<tr>\
						<th>Connected</th>\
						<td>Not sure</td>\
					</tr>\
				</tbody>\
			</table>\
	</body>\
</html>";
	#define PageStatusParams ,

	size_t needed = snprintf(NULL, 0, PageIndex) + 1;
	char  *html = malloc(needed);
	snprintf(html, needed, PageIndex);
    return html;
}




char * httpServerPageGet(char * method, char * uri, char * payload){

	if (strcmp(uri, "/") == 0){

		if (strcmp(method, "POST") == 0){
			httpServerPagePostIndex(payload);
		}
		return httpServerPageGetIndex();
	}

	else if (strcmp(uri, "/status") == 0){
		return httpServerPageGetStatus();
	}

	return NULL;
}
