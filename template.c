#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

typedef struct {
	char* name;
	char* value;
} template_s;

int strpos(char* haystack, char* needle);
char* substr(char* source, int start, int end);
char* processTpl(char* template, template_s data[], int dataSize);

int main() {
	template_s data[] = {
		{
			"user",
			"Paul"
		},
		{
			"lol",
			"yeah"
		}
	};

	char* html = processTpl("coucoooo @(user) la forme ? yeah @(user)@(lol) !", data, sizeof(data));
	printf("%s", html);
}

char* processTpl(char* template, template_s data[], int dataSize) {
	int templateLen, leftParamPos, rightParamPos, dataLen, i;
	char *param, *leftTemplate, *rightTemplate, *newTemplate;

	templateLen = strlen(template);
	leftParamPos = strpos(template, "@(");

	if (leftParamPos == -1) return template;

	rightParamPos = strpos(template + leftParamPos, ")");

	param = substr(template, leftParamPos + 2, leftParamPos + rightParamPos - 1);
	leftTemplate = substr(template, 0, leftParamPos - 1);
	rightTemplate = substr(template, leftParamPos + rightParamPos + 1, templateLen);
	newTemplate = malloc((strlen(leftTemplate) + strlen(param)) * sizeof(char));
	printf("Alloc %d\n", (strlen(leftTemplate) + strlen(param)) * sizeof(char));
	dataLen = dataSize / sizeof(template_s);

	for (i = 0; i < dataLen; i++) {
		if (*param == *(data[i].name)) {
			param = data[i].value;
			break;				
		}
	}

	strcpy(newTemplate, leftTemplate);
	strcat(newTemplate, param);
	
	return strcat(newTemplate, processTpl(rightTemplate, data, dataSize));
}

int strpos(char* haystack, char* needle) {
	char* str = strstr(haystack, needle);

	return (str == NULL ? -1 : str - haystack);
}

char* substr(char* source, int start, int end) {
	int size = end - start + 1;
	char* output = malloc(sizeof(char) * size);
	printf("Alloc %d\n", sizeof(char) * size);

	memcpy(output, source + start, size);

	return output;
}
