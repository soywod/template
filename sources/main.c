#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "../headers/template.h"
#include "../headers/server.h"

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
	char* http = "GET / HTTP/1.1\n"
	"Host: 192.168.1.13:8080\n"
	"Connection: keep-alive\n"
	"Cache-Control: max-age=0\n"
	"Upgrade-Insecure-Requests: 1\n"
	"User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/54.0.2840.71 Safari/537.36\n"
	"Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\n"
	"Accept-Encoding: gzip, deflate, sdch\n"
	"Accept-Language: fr-FR,fr;q=0.8,en-US;q=0.6,en;q=0.4\n\nlol";

	//srvListen();
	printf("%s", http);

	return 0;
}
