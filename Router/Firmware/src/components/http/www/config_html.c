#include <http_server.h>

#include "http.h"

extern const char  configHTMLStart[]	asm("_binary_config_html_start");
extern const char  configHTMLEnd[]		asm("_binary_config_html_end");

const ssiTag_t ssiTags[] = {
	{"wifiSSID", SSI_TYPE_TEXT},
	{"wifiPassword",SSI_TYPE_PASSWORD}
};

esp_err_t httpPageConfigGet(httpd_req_t *req) {
	httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
	return httpRespond(req, configHTMLStart, configHTMLEnd, (ssiTag_t *) &ssiTags, sizeof(ssiTags) / sizeof(ssiTags[0]));
}

httpd_uri_t httpPageConfigGetURI = {
    .uri      = "/config.html",
    .method   = HTTP_GET,
    .handler  = httpPageConfigGet
};

httpd_uri_t httpPageConfigPostURI = {
    .uri      = "/config.html",
    .method   = HTTP_POST,
    .handler  = httpPageConfigGet
};



void httpPageConfigHTMLInit(httpd_handle_t server) {
	httpd_register_uri_handler(server, &httpPageConfigGetURI);
	httpd_register_uri_handler(server, &httpPageConfigPostURI);
}
