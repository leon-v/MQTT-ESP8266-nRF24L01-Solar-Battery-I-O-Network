#ifndef HTTP_SERVER_
#define HTTP_SERVER_

typedef struct{
	char * key;
	char * value;
} token_t;

typedef struct{
	token_t tokens[32];
	unsigned int length;
} tokens_t;

void httpServerInit(void);
char * httpServerParseValues(tokens_t * tokens, char * buffer, const char * rowDelimiter, const char * valueDelimiter, const char * endMatch);
char * httpServerGetTokenValue(tokens_t * tokens, const char * key);

#endif /* HTTP_SERVER_ */