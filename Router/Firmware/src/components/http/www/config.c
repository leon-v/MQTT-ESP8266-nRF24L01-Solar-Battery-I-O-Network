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
	return httpRespond(req, configHTMLStart, configHTMLEnd, HTTPD_TYPE_TEXT, &httpPageConfigGetSSIValue);
}



esp_err_t httpPageConfigPost(httpd_req_t *req) {

	char postString[1024];
	tokens_t post;

	unsigned int postStringLength = sizeof(postString) - 1;
	// httpGetPost(req, postString, postStringLength);
	int ret, remaining = req->content_len;
    int length = 0;
    int min = 0;

    while (remaining > 0) {
        /* Read the data for the request */

        min = (remaining > postStringLength) ? postStringLength : remaining;

        if ((ret = httpd_req_recv(req, postString, min)) < 0) {
        	printf("httpd_req_recv ret1 :%d\n", ret);
        	return ret;
        }

        printf("httpd_req_recv ret2 :%d\n", ret);

        length+= ret;
        remaining -= ret;
    }

    postString[length] = '\0';

	printf("Got post data :%s\n", postString);

	// httpServerParseValues(&post, postString, "&", "=", "");

	// printf("Still Got Post %s\n", postString);

    // nvs_handle nvsHandle;
   	// ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READWRITE, &nvsHandle));

    // char * value;
    
    // value = httpServerGetTokenValue(&post, "wifiSSID");
	// if (value){
		// ESP_ERROR_CHECK(nvs_set_str(nvsHandle, "wifiSSID", value));
	// }

	// printf("Committing \n");

	// ESP_ERROR_CHECK(nvs_commit(nvsHandle));

   	// nvs_close(nvsHandle);

    /* Log data received */
    // printf("Still sill Got Post %s\n", postString);

	return httpRespond(req, configHTMLStart, configHTMLEnd, HTTPD_TYPE_TEXT, &httpPageConfigGetSSIValue);
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