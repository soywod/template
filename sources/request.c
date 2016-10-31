#include <stdlib.h>
#include <string.h>

#include "../headers/request.h"
#include "../headers/string.h"
#include "../headers/assoc.h"

typedef struct Request
{
	char* method;
	char* url;
	char* protocol;
	char* content;
	Assoc* headers;
} Request;

Request* reqNew(char* html)
{
	char *cursor, *key, *val;
	int cursorpos;
	Request* req;

	req = malloc(sizeof(Request));
	req->headers = assocNew();

	// Set method
	cursorpos = charpos(html, ' ');
	req->method = substr(html, 0, cursorpos - 1);
	cursor = html + cursorpos + 1;

	// Set url
	cursorpos = charpos(cursor, ' ');
	req->url = substr(cursor, 0, cursorpos - 1);
	cursor += cursorpos + 1;

	// Set protocol
	cursorpos = charpos(cursor, '\r');
	req->protocol = substr(cursor, 0, cursorpos - 1);
	cursor += cursorpos + 2;

	// Set headers
	while(*cursor != '\r')
	{
		cursorpos = charpos(cursor, ':');
		key = substr(cursor, 0, cursorpos - 1);
		cursor += cursorpos + 2;

		cursorpos = charpos(cursor, '\r');
		val = substr(cursor, 0, cursorpos - 1);
		cursor += cursorpos + 2;

		assocAdd(key, val, req->headers);

		free(key);
		free(val);
	}

	cursor += 2;
	req->content = substr(cursor, 0, strlen(cursor));

	return req;
}

void reqClose(Request* req)
{
	assocClose(req->headers);

	free(req->method);
	free(req->url);
	free(req->protocol);
	free(req->content);
	free(req);
}
