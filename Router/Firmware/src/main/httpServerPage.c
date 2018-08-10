#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "configFlash.h"

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
							<th>WiFi SSID</th>\
							<td><input type='text' name=\"wifiSSID\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<th>WiFi Password</th>\
							<td><input type='password' name=\"wifiPassword\" value=\"%s\" ></td>\
						</tr>\
						<tr>\
							<td colspan\"2\" ><button>Save</button></td>\
						</tr>\
					</tbody>\
				</table>\
			</form>\
		</body>\
	";
	#define PageIndexParams configFlash.wifiSSID, configFlash.wifiPassword

	size_t needed = snprintf(NULL, 0, PageIndex, PageIndexParams) + 1;
	char  *html = malloc(needed);
	snprintf(html, needed, PageIndex, PageIndexParams);
    return html;
}


char * httpServerPageGet(char * requestURI){

	if (strcmp(requestURI, "/") == 0){
		return httpServerPageGetIndex();
	}

	return NULL;
}
