#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "../headers/template.h"
#include "../headers/server.h"
//#include "../headers/router.h"

void handler(int sockfd, char* ip, char* data) {
	printf(data);
}

int main()
{
	/*
	Template* tpl;
	char* html;

	tpl = tplOpen("../views/index.tpl.html");

	tplAddParam("name", "lol", tpl);
	tplAddParam("title", "yeah", tpl);

	html = tplRender(tpl);

	printf("%s", html);
	tplClose(tpl);

	*/

	Server* srv = srvNew(8080, &handler);
	srvListen(srv);
	srvClose(srv);
	
	return 0;
}
