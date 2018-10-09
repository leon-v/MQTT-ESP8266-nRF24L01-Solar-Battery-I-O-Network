#include <http_server.h>

#include "wifi.h"

/* Maintain a variable which stores the number of times
 * the "/adder" URI has been visited */
static unsigned visitors = 0;

/* Function to free context */
void adder_free_func(void *ctx) {
    printf("http: / Free Context function called");
    free(ctx);
}

// typedef struct {
// 	unsigned char fileStart[];
// 	unsigned char fileEnd[];
// } http_file_t;



extern const char  okHTHStart[]		asm("_binary_200_hth_start");
extern const char  okHTHEnd[]		asm("_binary_200_hth_end");

extern const char  indexHTMLStart[]	asm("_binary_index_html_start");
extern const char  indexHTMLEnd[]	asm("_binary_index_html_end");

/* This handler gets the present value of the accumulator */
esp_err_t adder_get_handler(httpd_req_t *req) {

    /* Log total visitors */
    unsigned *visitors = (unsigned *)req->user_ctx;
    printf("http: / visitor count = %d", ++(*visitors));

    /* Create session's context if not already available */
    if (!req->sess_ctx) {
        printf("http: /r GET allocating new session");
        req->sess_ctx = malloc(sizeof(int));
        req->free_ctx = adder_free_func;
        *(int *)req->sess_ctx = 0;
    }

    unsigned int okHTHLength = okHTHEnd - okHTHStart;
    unsigned int indexHTMLLength = indexHTMLEnd - indexHTMLStart;

    char outBuffer[1024];
    outBuffer[0] = '\0';

    printf("http: / GET handler send %d", *(int *)req->sess_ctx);

    strncat(outBuffer, okHTHStart, okHTHLength);
    strncat(outBuffer, indexHTMLStart, indexHTMLLength);

    httpd_resp_send(req, outBuffer, strlen(outBuffer));

    return ESP_OK;
}

httpd_uri_t adder_get = {
    .uri      = "/",
    .method   = HTTP_GET,
    .handler  = adder_get_handler,
    .user_ctx = &visitors
};

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
        httpd_register_uri_handler(server, &adder_get);
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