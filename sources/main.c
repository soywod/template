#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/template.h"

int main()
{
	Template* tpl;
	char* html;

	tpl = tplOpen("../views/index.tpl.html");

	tplAddParam("name", "lol", tpl);
	tplAddParam("title", "yeah", tpl);

	html = tplRender(tpl);

	printf("%s", html);
	tplClose(tpl);

	return 0;
}
