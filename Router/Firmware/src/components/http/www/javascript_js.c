#include <http_server.h>
#include "http.h"

extern const char  javascriptJSStart[]	asm("_binary_javascript_js_start");
extern const char  javascriptJSEnd[]	asm("_binary_javascript_js_end");

esp_err_t httpPageJavascriptJSGet(httpd_req_t *req) {
	httpd_resp_set_type(req, "application/javascript");
	return httpRespond(req, javascriptJSStart, javascriptJSEnd, NULL, 0);
}

httpd_uri_t httpPageJavascriptJSURI = {
    .uri      = "/javascript.js",
    .method   = HTTP_GET,
    .handler  = httpPageJavascriptJSGet
};

void httpPageJavascriptJSInit(httpd_handle_t server) {
	httpd_register_uri_handler(server, &httpPageJavascriptJSURI);
}