#ifndef HTTP_SERVER_
#define HTTP_SERVER_

typedef struct { char *name, *value; } header_t;

void httpServerInit(void);

#endif /* HTTP_SERVER_ */