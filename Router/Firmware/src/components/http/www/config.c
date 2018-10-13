#include <http_server.h>
#include <nvs.h>
#include "http.h"


extern const char  configHTMLStart[]	asm("_binary_config_html_start");
extern const char  configHTMLEnd[]		asm("_binary_config_html_end");

void httpPageConfigGetSSIValue(char * name, char * value) {
	
	if (strcmp(name, "test") == 0){
		strcpy(value, "Test Value");
	}
	else if(strcmp(name, "wifiSSID") == 0) {
		sprintf(value, HTML_INPUT_STRING, "text", "wifiSSID", "Yay");
	}
}

esp_err_t httpPageConfigGet(httpd_req_t *req) {
	return httpRespond(req, configHTMLStart, configHTMLEnd, HTTPD_TYPE_TEXT, &httpPageConfigGetSSIValue);
}



esp_err_t httpPageConfigPost(httpd_req_t *req) {

	char postString[1024];
	tokens_t post;
	esp_err_t espError;

	httpGetPost(req, postString, post);

    nvs_handle nvsHandle;
   	espError = nvs_open("BeelineNVS", NVS_READWRITE, &nvsHandle);

   	if (espError != ESP_OK){
   		printf("nvs_open return %d\n", espError);
   		return ESP_OK;
   	}

    char * value;
    
    value = httpServerGetTokenValue(&post, "wifiSSID");
	if (value){

		espError = nvs_set_str(nvsHandle, "wifiSSID", value);

		if (espError != ESP_OK){
   			printf("nvs_set_str wifiSSID %d\n", espError);
   			return ESP_OK;
   		}
		printf("wifiSSID = %s\n", value);
	}

	espError = nvs_commit(nvsHandle);
	if (espError != ESP_OK){
   		printf("nvs_commit return %d\n", espError);
   		return ESP_OK;
   	}

    /* Log data received */
    printf("%s\n\n", postString);

	return httpRespond(req, configHTMLStart, configHTMLEnd, HTTPD_TYPE_TEXT, httpPageConfigGetSSIValue);
}

httpd_uri_t httpPageConfigGetURI = {
    .uri      = "/config.html",
    .method   = HTTP_GET,
    .handler  = httpPageConfigGet
};

httpd_uri_t httpPageConfigPostURI = {
    .uri      = "/config.html",
    .method   = HTTP_POST,
    .handler  = httpPageConfigPost
};



void httpPageConfigHTMLInit(httpd_handle_t server) {
	httpd_register_uri_handler(server, &httpPageConfigGetURI);
	httpd_register_uri_handler(server, &httpPageConfigPostURI);
}