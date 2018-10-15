#include <http_server.h>
#include <nvs.h>

#include "http.h"


extern const char  configHTMLStart[]	asm("_binary_config_html_start");
extern const char  configHTMLEnd[]		asm("_binary_config_html_end");

void httpPageConfigGetSSIValue(char * name, char * value) {
	
	if(strcmp(name, "wifiSSID") == 0) {
		sprintf(value, HTML_INPUT_STRING, "text", "wifiSSID", "ssid1");
	}
	else if(strcmp(name, "wifiPassword") == 0) {
		sprintf(value, HTML_INPUT_STRING, "password", "wifiPassword", "password1");
	}
}

esp_err_t httpPageConfigGet(httpd_req_t *req) {

	httpd_resp_set_type(req, HTTPD_TYPE_TEXT);

	return httpRespond(req, configHTMLStart, configHTMLEnd, &httpPageConfigGetSSIValue);
}



esp_err_t httpPageConfigPost(httpd_req_t *req) {

	char postString[512];
	tokens_t post;
	nvs_handle nvsHandle;

	ESP_ERROR_CHECK(httpGetPost(req, postString, sizeof(postString)));

	printf("Got post data :%s\n", postString);	

	httpServerParseValues(&post, postString, "&", "=", "\0");

	printf("Still Got Post %s\n", postString);

    ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READWRITE, &nvsHandle));

    char * value;
    
    value = httpServerGetTokenValue(&post, "wifiSSID");
	if (value){
		ESP_ERROR_CHECK(nvs_set_str(nvsHandle, "wifiSSID", value));
		printf("Got wifiSSID=%s\n", value);
	}

	printf("Committing \n");

	ESP_ERROR_CHECK(nvs_commit(nvsHandle));

   	nvs_close(nvsHandle);

    /* Log data received */
    printf("Still sill Got Post %s\n", postString);

    return httpPageConfigGet(req);
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