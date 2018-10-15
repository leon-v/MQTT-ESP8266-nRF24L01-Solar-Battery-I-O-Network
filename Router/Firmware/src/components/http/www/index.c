#include <http_server.h>
#include "http.h"


extern const char  indexHTMLStart[]	asm("_binary_index_html_start");
extern const char  indexHTMLEnd[]	asm("_binary_index_html_end");
esp_err_t httpPageIndexGet(httpd_req_t *req) {
	httpd_resp_set_type(req, HTTPD_TYPE_TEXT);
	return httpRespond(req, indexHTMLStart, indexHTMLEnd, NULL);
}

httpd_uri_t httpPageIndexURI = {
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = httpPageIndexGet
};

void httpPageIndexHTMLInit(httpd_handle_t server) {
	httpd_register_uri_handler(server, &httpPageIndexURI);
}