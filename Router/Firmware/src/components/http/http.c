#include <sys/param.h>
#include <http_server.h>
#include <nvs.h>

#include "wifi.h"
#include "http.h"

#include "index.h"

typedef void (*httpSSIParser_t)(char * name, char * value);

/* Function to free context */
void adder_free_func(void *ctx) {
    printf("http: / Free Context function called");
    free(ctx);
}

char * httpServerParseValues(tokens_t * tokens, char * buffer, const char * rowDelimiter, const char * valueDelimiter, const char * endMatch){

	tokens->length = 0;

	// Start parsing the values by creating a new string from the payload 
	char * token = strtok(buffer, rowDelimiter);

	char * end = buffer + strlen(buffer);

	// break apart the string getting all the parts delimited by &
	while (token != NULL) {

		if (strlen(endMatch) > 0){
			end = token + strlen(token) + 1;

			if (strncmp(end, endMatch, strlen(endMatch)) == 0) {
				end+= strlen(endMatch);
				break;
			}
		}

		tokens->tokens[tokens->length++].key = token;

		token = strtok(NULL, rowDelimiter);
	}

	// Re-parse the strigns and break them apart into key / value pairs
	for (unsigned int index = 0; index < tokens->length; index++){

		tokens->tokens[index].key = strtok(tokens->tokens[index].key, valueDelimiter);

		tokens->tokens[index].value = strtok(NULL, valueDelimiter);

		// If the value is NULL, make it point to an empty string.
		if (tokens->tokens[index].value == NULL){
			tokens->tokens[index].value = tokens->tokens[index].key + strlen(tokens->tokens[index].key);
		}
	}

	return end;
}

char * httpServerGetTokenValue(tokens_t * tokens, const char * key){

	for (unsigned int index = 0; index < tokens->length; index++){

		if (strcmp(tokens->tokens[index].key, key) == 0){
			return tokens->tokens[index].value;
		}
	}

	return NULL;
}

#define START_SSI "<!--#"
#define END_SSI "-->"
#define SSI_TAG_MAX_LENGTH 64


void httpReaplceSSI(char * outBuffer, const char * fileStart, const char * fileEnd, httpSSIParser_t httpSSIParser){

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
		ssiValue[0] = '\0';

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

		if (httpSSIParser) {
			httpSSIParser(ssiTag, ssiValue);
		}
		

		if (ssiValue == NULL) {
			continue;
		}

		appendLength = strlen(ssiValue);

		strncpy(out, ssiValue, appendLength);
		out+= appendLength;
	}
}

void httpGetPost(httpd_req_t *req, char * postString, tokens_t post){
	    
    int ret, remaining = req->content_len;

    while (remaining > 0) {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, postString, MIN(remaining, sizeof(postString)))) < 0) {
            return;
        }

        remaining -= ret;
    }
    
    httpServerParseValues(&post, postString, "&", "=", "");
}

esp_err_t httpRespond(httpd_req_t *req, const char * fileStart, const char * fileEnd, const char * contentType, httpSSIParser_t httpSSIParser) {

	httpd_resp_set_type(req, contentType);

	char outBuffer[2048] = "\0";

	if (strcmp(contentType, HTTPD_TYPE_TEXT) == 0){
		if (httpSSIParser) {
			httpReaplceSSI(outBuffer, fileStart, fileEnd, httpSSIParser);
		}
		
	}

	else{
		strncpy(outBuffer, fileStart, fileEnd - fileStart);
	}
	

	httpd_resp_send(req, outBuffer, strlen(outBuffer));

	return ESP_OK;
}



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

        httpPageIndexHTMLInit(server);

        // httpd_register_uri_handler(server, &httpIndexHTML);
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