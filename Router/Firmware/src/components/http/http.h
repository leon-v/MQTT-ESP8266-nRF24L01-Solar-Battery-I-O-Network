#ifndef HTTP_SERVER_H

#include <http_server.h>

#define HTML_INPUT_STRING "<input type=\"%s\" name=\"%s\" value=\"%s\" />"
#define HTML_INPUT_INT "<input type=\"%s\" name=\"%s\" value=\"%u\" />"
#define HTML_ULONG "%lu"
#define HTML_UINT "%u"

typedef struct{
	char * key;
	char * value;
} token_t;

typedef struct{
	token_t tokens[32];
	unsigned int length;
} tokens_t;

typedef void (*httpSSIParser_t)(char * name, char * value);

void httpServerInit(void);

esp_err_t httpRespond(httpd_req_t *req, const char * fileStart, const char * fileEnd, const char * contentType, httpSSIParser_t httpSSIParser);

void httpGetPost(httpd_req_t *req, char * postString, tokens_t post);

char * httpServerGetTokenValue(tokens_t * tokens, const char * key);

#define HTTP_SERVER_H
#endif