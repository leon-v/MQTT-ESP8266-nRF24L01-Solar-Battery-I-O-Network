#include <http_server.h>
#include "http.h"

extern const char  httpTemplateStyleCSSStart[]	asm("_binary_style_css_start");
extern const char  httpTemplateStyleCSSEnd[]	asm("_binary_style_css_end");

esp_err_t httpPageStyleCSSGet(httpd_req_t *req) {
	httpd_resp_set_type(req, "text/css");
	return httpRespond(req, httpTemplateStyleCSSStart, httpTemplateStyleCSSEnd, NULL, 0);
}

httpd_uri_t httpPageStyleCSSURI = {
    .uri      = "/style.css",
    .method   = HTTP_GET,
    .handler  = httpPageStyleCSSGet
};

void httpPageStyleCSSInit(httpd_handle_t server) {
	httpd_register_uri_handler(server, &httpPageStyleCSSURI);
}