#include <sys/param.h>
#include <http_server.h>
#include <nvs.h>

#include "wifi.h"
#include "http.h"
#include "config.h"

#include "index.h"
#include "config_html.h"


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


void httpReaplceSSI(char * outBuffer, const char * fileStart, const char * fileEnd, const ssiTag_t * ssiTags, int ssiTagsLength) {

	char * file = (char * ) fileStart;
	char * out = outBuffer;

	int ssiTagsIndex = 0;
	char ssiKey[MAX_HTTP_SSI_KEY_LENGTH] = {"\0"};
	

	nvs_handle nvsHandle;
	ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READWRITE, &nvsHandle));

	unsigned int appendLength = 0;

	while (true)  {

		if ( ((fileEnd - file) < sizeof(START_SSI)) || (strncmp(file, START_SSI, strlen(START_SSI)) != 0) ) {


			appendLength = 1;

			if ((file + appendLength) > fileEnd) {
				nvs_close(nvsHandle);
				return;
			}

			strncpy(out, file, appendLength);

			file+= appendLength;
			out+= appendLength;

			continue;
		}

		file+= strlen(START_SSI);

		ssiKey[0] = '\0';

		while ( ((fileEnd - file) < sizeof(END_SSI)) || (strncmp(file, END_SSI, strlen(END_SSI)) != 0) ) {

			appendLength = 1;

			if ((file + appendLength) > fileEnd) {
				nvs_close(nvsHandle);
				return;
			}

			if (strlen(ssiKey) >= (sizeof(ssiKey) - 1)){
				file+= appendLength;
				continue;
			}

			strncat(ssiKey, file, appendLength);

			file+= appendLength;
		}

		file+= sizeof(END_SSI) - 1;

		char replaceSSIValue[MAX_HTTP_SSI_VALUE_LENGTH];
		strcpy(replaceSSIValue, "SSI Value Unhandled");

		for (ssiTagsIndex = 0; ssiTagsIndex < ssiTagsLength; ssiTagsIndex++) {

			const ssiTag_t ssiTag = ssiTags[ssiTagsIndex];

			if (strcmp(ssiKey, ssiTag.key) != 0) {
				continue;
			}


			char nvsValue[MAX_CONFIG_STRING_LENGTH];
			size_t nvsLength = sizeof(nvsValue);

			switch (ssiTag.type) {

				case SSI_TYPE_TEXT:
					nvs_get_str(nvsHandle, ssiTag.key, nvsValue, &nvsLength);
					nvsValue[nvsLength] = '\0';
					sprintf(replaceSSIValue, "<input type=\"text\" name=\"%s\" value=\"%s\" />", ssiTag.key, nvsValue);
				break;

				case SSI_TYPE_PASSWORD:
					nvs_get_str(nvsHandle, ssiTag.key, nvsValue, &nvsLength);
					nvsValue[nvsLength] = '\0';
					sprintf(replaceSSIValue, "<input type=\"password\" name=\"%s\" value=\"%s\" />", ssiTag.key, nvsValue);
				break;

				case SSI_TYPE_INTEGER:
				break;
			}

			break;
		}
		// strcpy(replaceSSIValue, "TEST");

		appendLength = strlen(replaceSSIValue);
		strncpy(out, replaceSSIValue, appendLength);
		out+= appendLength;
	}

	nvs_close(nvsHandle);
}

esp_err_t httpGetPost(httpd_req_t *req, char * postString, unsigned int postStringLength){
	    
	int ret, remaining = req->content_len;

    while (remaining > 0) {
        /* Read the data for the request */
        if ((ret = httpd_req_recv(req, postString, MIN(remaining, postStringLength))) < 0) {
            return ESP_FAIL;
        }

        remaining -= ret;
    }

    postString[req->content_len] = '\0';

    return ESP_OK;
}

void httpServerSavePost(httpd_req_t * req, char * buffer, unsigned int bufferLength, const ssiTag_t * ssiTags, int ssiTagsLength){

	ESP_ERROR_CHECK(httpGetPost(req, buffer, bufferLength));

	printf("Got post data :%s\n", buffer);	

	tokens_t post;
	httpServerParseValues(&post, buffer, "&", "=", "\0");

	nvs_handle nvsHandle;
	ESP_ERROR_CHECK(nvs_open("BeelineNVS", NVS_READWRITE, &nvsHandle));
    
    for (int ssiTagsIndex = 0; ssiTagsIndex < ssiTagsLength; ssiTagsIndex++) {

		const ssiTag_t ssiTag = ssiTags[ssiTagsIndex];

		char * value = httpServerGetTokenValue(&post, ssiTag.key);

		if (!value){
			continue;
		}

		printf("I=%d, K=%s, V=%s\n", ssiTagsIndex, ssiTag.key, value);

		ESP_ERROR_CHECK(nvs_set_str(nvsHandle, ssiTag.key, value));

		ESP_ERROR_CHECK(nvs_commit(nvsHandle));
	}

   	nvs_close(nvsHandle);
}

esp_err_t httpRespond(httpd_req_t *req, const char * fileStart, const char * fileEnd, const ssiTag_t * ssiTags, int ssiTagsLength) {

	char outBuffer[2048];

	if (req->method == HTTP_POST){
		httpServerSavePost(req, outBuffer, sizeof(outBuffer), ssiTags, ssiTagsLength);
	}


	if (ssiTags) {
		httpReaplceSSI(outBuffer, fileStart, fileEnd, ssiTags, ssiTagsLength);
	}

	else{
		strncpy(outBuffer, fileStart, fileEnd - fileStart);
	}
	

	return httpd_resp_send(req, outBuffer, strlen(outBuffer));
}



extern const char  styleCSSStart[]	asm("_binary_style_css_start");
extern const char  styleCSSLEnd[]	asm("_binary_style_css_end");
esp_err_t httpGetStyleCSS(httpd_req_t *req) {

	httpd_resp_set_type(req, "text/css");
	
	return httpRespond(req, styleCSSStart, styleCSSLEnd, NULL, 0);
}
httpd_uri_t httpStyleCSS = {
    .uri      = "/style.css",
    .method   = HTTP_GET,
    .handler  = httpGetStyleCSS
};


extern const char  javaScriptStart[]	asm("_binary_javascript_js_start");
extern const char  javaScriptEnd[]		asm("_binary_javascript_js_end");
esp_err_t httpGetJavascriptJS(httpd_req_t *req) {

	httpd_resp_set_type(req, "application/javascript");

	return httpRespond(req, javaScriptStart, javaScriptEnd, NULL, 0);
}
httpd_uri_t httpJavascriptJS = {
    .uri      = "/javascript.js",
    .method   = HTTP_GET,
    .handler  = httpGetJavascriptJS
};

void stop_webserver(httpd_handle_t server) {
    // Stop the httpd server
    httpd_stop(server);
}


httpd_handle_t start_webserver(void) {

    httpd_config_t config = HTTPD_DEFAULT_CONFIG();
    config.recv_wait_timeout = 5;
    config.send_wait_timeout = 5;
    config.stack_size = 8192;

    // Start the httpd server
    printf("http: Starting server on port: '%d'", config.server_port);
    httpd_handle_t server;

    if (httpd_start(&server, &config) == ESP_OK) {
        // Set URI handlers
        printf("http: Registering URI handlers");

        httpPageIndexHTMLInit(server);
        httpPageConfigHTMLInit(server);

        httpd_register_uri_handler(server, &httpStyleCSS);
        httpd_register_uri_handler(server, &httpJavascriptJS);
        
        

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

	// http_semaphore = xSemaphoreCreateMutex();

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


	xTaskCreate(&httpServerTask, "http", 8192, NULL, 12, NULL);
}