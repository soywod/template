#ifndef REQUEST_H
#define REQUEST_H

typedef struct Request Request;

Request* reqNew(char* html);
void reqClose(Request* req);

#endif
