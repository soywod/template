#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../headers/template.h"

int main()
{
	char *html, *tpl;
	struct TemplateData data[] =
	{
		{
			"title",
			"My first template"
		},
		{
			"content",
			"LOLOLOLOLOL"
		}
	
	};
	
	tpl = getFileContent("../views/index.tpl.html");
	html = processTemplate(tpl, data, sizeof(data));
	printf("%s\n", html);
	free(html);
	free(tpl);

	return 0;
}

