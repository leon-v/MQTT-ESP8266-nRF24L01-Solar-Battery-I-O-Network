#include <sys/param.h>

#include <http_server.h>

#include "wifi.h"

/* Function to free context */
void adder_free_func(void *ctx) {
    printf("http: / Free Context function called");
    free(ctx);
}


void httpGetSSIValue(char * name, char * reaplceValue){

	if (strcmp(name, "test") == 0){
		strcpy(reaplceValue, "Test Value");
	}
}

#define START_SSI "<!--#"
#define END_SSI "-->"
#define SSI_TAG_MAX_LENGTH 64


void httpReaplceSSI(char * outBuffer, const char * fileStart, const char * fileEnd){

	const char * file = fileStart;
	char * out = outBuffer;

	char ssiTag[SSI_TAG_MAX_LENGTH] = {"\0"};
	char ssiValue[SSI_TAG_MAX_LENGTH] = {"\0"};

	unsigned int appendLength = 0;

	while (true)  {

		if ( ((fileEnd - file) < sizeof(START_SSI)) || (strncmp(file, START_SSI, strlen(START_SSI)) != 0) ) {


			appendLength = 1;

			if ((file + appendLength) > fileEnd) {
				return;
			}

			strncpy(out, file, appendLength);

			file+= appendLength;
			out+= appendLength;

			continue;
		}

		file+= strlen(START_SSI);

		ssiTag[0] = '\0';

		while ( ((fileEnd - file) < sizeof(END_SSI)) || (strncmp(file, END_SSI, strlen(END_SSI)) != 0) ) {

			appendLength = 1;

			if ((file + appendLength) > fileEnd) {
				return;
			}

			if (strlen(ssiTag) >= (sizeof(ssiTag) - 1)){
				file+= appendLength;
				continue;
			}

			strncat(ssiTag, file, appendLength);

			file+= appendLength;
		}

		file+= sizeof(END_SSI) - 1;

		httpGetSSIValue(ssiTag, ssiValue);

		if (ssiValue == NULL) {
			continue;
		}

		appendLength = strlen(ssiValue);

		strncpy(out, ssiValue, appendLength);
		out+= appendLength;
	}
}

void httpPost(httpd_req_t *req){

	/* An HTTP POST handler */
    char buf[100];
    int ret, remaining = req->content_len;

    while (remaining > 0) {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, buf, MIN(remaining, sizeof(buf)))) < 0) {
            return ESP_FAIL;
        }

        /* Send back the same data */
        httpd_resp_send_chunk(req, buf, ret);
        remaining -= ret;

        /* Log data received */
        printf("%.*s\n\n", ret, buf);
    }

    // End response
    httpd_resp_send_chunk(req, NULL, 0);
    return ESP_OK;
}

esp_err_t httpRespond(httpd_req_t *req, const char * fileStart, const char * fileEnd, const char * contentType) {

	httpd_resp_set_type(req, contentType);

	char outBuffer[2048] = "\0";

	if (strcmp(contentType, HTTPD_TYPE_TEXT) == 0){
		httpReaplceSSI(outBuffer, fileStart, fileEnd);
	}

	else{
		strncpy(outBuffer, fileStart, fileEnd - fileStart);
	}
	

	httpd_resp_send(req, outBuffer, strlen(outBuffer));

	return ESP_OK;
}

extern const char  configHTMLStart[]	asm("_binary_config_html_start");
extern const char  configHTMLEnd[]		asm("_binary_config_html_end");
esp_err_t httpGetConfigHTML(httpd_req_t *req) {

	if (req->method == HTTP_POST){
		httpPost(req);
	}

	return httpRespond(req, configHTMLStart, configHTMLEnd, HTTPD_TYPE_TEXT);
}
httpd_uri_t httpdGetConfigHTML = {
    .uri      = "/config.html",
    .method   = HTTP_GET,
    .handler  = httpGetConfigHTML
};
httpd_uri_t httpdPostConfigHTML = {
    .uri      = "/config.html",
    .method   = HTTP_POST,
    .handler  = httpGetConfigHTML
};


extern const char  indexHTMLStart[]	asm("_binary_index_html_start");
extern const char  indexHTMLEnd[]	asm("_binary_index_html_end");
esp_err_t httpGetIndexHTML(httpd_req_t *req) {
	return httpRespond(req, indexHTMLStart, indexHTMLEnd, HTTPD_TYPE_TEXT);
}
httpd_uri_t httpIndexHTML = {
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = httpGetIndexHTML
};


extern const char  styleCSSStart[]	asm("_binary_style_css_start");
extern const char  styleCSSLEnd[]	asm("_binary_style_css_end");
esp_err_t httpGetStyleCSS(httpd_req_t *req) {
	return httpRespond(req, styleCSSStart, styleCSSLEnd, "text/css");
}
httpd_uri_t httpStyleCSS = {
    .uri      = "/style.css",
    .method   = HTTP_GET,
    .handler  = httpGetStyleCSS
};


extern const char  javaScriptStart[]	asm("_binary_javascript_js_start");
extern const char  javaScriptEnd[]		asm("_binary_javascript_js_end");
esp_err_t httpGetJavascriptJS(httpd_req_t *req) {
	return httpRespond(req, javaScriptStart, javaScriptEnd, "application/javascript");
}
httpd_uri_t httpJavascriptJS = {
    .uri      = "/javascript.js",
    .method   = HTTP_GET,
    .handler  = httpGetJavascriptJS
};



/* This handler gets the present value of the accumulator */
// esp_err_t adder_get_handler(httpd_req_t *req) {

//     /* Log total visitors */
//     unsigned *visitors = (unsigned *)req->user_ctx;
//     printf("http: / visitor count = %d\n", ++(*visitors));

//     /* Create session's context if not already available */
//     if (!req->sess_ctx) {
//         printf("http: /r GET allocating new session\n");
//         req->sess_ctx = malloc(sizeof(int));
//         req->free_ctx = adder_free_func;
//         *(int *)req->sess_ctx = 0;
//     }

//     httpd_resp_set_type(req, HTTPD_TYPE_TEXT);

//     unsigned int indexHTMLLength = indexHTMLEnd - indexHTMLStart;

//     char outBuffer[1024];
//     outBuffer[0] = '\0';

//     printf("http: / GET handler send %d\n", *(int *)req->sess_ctx);

//     strcat(outBuffer, "\r\n");

//     strncat(outBuffer, indexHTMLStart, indexHTMLLength);

    

//     return httpRespond()
// }

void stop_webserver(httpd_handle_t server) {
    // Stop the httpd server
    httpd_stop(server);
}


httpd_handle_t start_webserver(void) {

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();

    // Start the httpd server
    printf("http: Starting server on port: '%d'", config.server_port);
    httpd_handle_t server;

    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        printf("http: Registering URI handlers");

        httpd_register_uri_handler(server, &httpIndexHTML);
        httpd_register_uri_handler(server, &httpStyleCSS);
        httpd_register_uri_handler(server, &httpJavascriptJS);
        
        httpd_register_uri_handler(server, &httpdGetConfigHTML);
        httpd_register_uri_handler(server, &httpdPostConfigHTML);
        
        

        // httpd_register_uri_handler(server, &adder_put);
        // httpd_register_uri_handler(server, &adder_post);
        return server;
    }

    printf("http: / Error starting server!");
    return NULL;
}

static void httpServerTask(void *arg){

	EventBits_t EventBits;
	httpd_handle_t server = NULL;

	while (true){

		EventBits = xEventGroupWaitBits(wifiGetEventGroup(), WIFI_CONNECTED_BIT, false, true, 5000 / portTICK_RATE_MS);

		if (WIFI_CONNECTED_BIT & EventBits) {

			/* Start the web server */
	        if (server == NULL) {
	            server = start_webserver();
	        }
		}

		else{
			/* Stop the webserver */
	        if (server) {
	            stop_webserver(server);
	            server = NULL;
	        }
		}
	}
	
	vTaskDelete(NULL);
    return;
}

void httpServerInit(){


	xTaskCreate(&httpServerTask, "http", 2048, NULL, 12, NULL);
}