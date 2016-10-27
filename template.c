#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

typedef struct {
	char* name;
	char* value;
} template_s;

int strpos(char* haystack, char* needle);
char* substr(char* source, int start, int end);
char* processTemplate(char* src, template_s data[], int dataSize);

int main() {
	char* html;
	template_s data[] = {
		{
			"user",
			"Paul"
		},
		{
			"lol",
			"yeah"
		},
		{
			"prout",
			"ppppapapappapap"
		}
	};

	html = processTemplate("coucoooo @(lol) yayaya @(user) - @(prout) # @(yop)", data, sizeof(data));
	printf("%s\n", html);
	free(html);
}

char* processTemplate(char* template, template_s data[], int dataSize) {
	int htmlPartLen, paramLen, nextTemplatePartLen, templateLen, dataLen;
	int leftParamPos, rightParamPos, i;
	char *htmlPart, *param, *templatePart, *nextTemplatePart, *finalHtml;

	templateLen = strlen(template);
	leftParamPos = strpos(template, "@(");

	// If no param found, stop recursion
	if (leftParamPos == -1) {
		finalHtml = malloc(templateLen + 1);
		return strcpy(finalHtml, template);
	}

	rightParamPos = strpos(template + leftParamPos, ")");

	// Extract all parts of the template
	htmlPart = substr(template, 0, leftParamPos - 1);
	param = substr(template, leftParamPos + 2, leftParamPos + rightParamPos - 1);
	templatePart = substr(template, leftParamPos + rightParamPos + 1, templateLen);

	// Process the next template part (recursion)
	nextTemplatePart = processTemplate(templatePart, data, dataSize);

	htmlPartLen = strlen(htmlPart);
	nextTemplatePartLen = strlen(nextTemplatePart);
	dataLen = dataSize / sizeof(template_s);

	// Replace param by the value given in data
	for (i = 0; i < dataLen; i++) {
		if (*param == *(data[i].name)) {
			param = realloc(param, strlen(data[i].value) + 1);
			strcpy(param, data[i].value);
			break;				
		}
	}

	paramLen = strlen(param);
	finalHtml = malloc(htmlPartLen + paramLen + nextTemplatePartLen + 1);

	strcpy(finalHtml, htmlPart);
	strcat(finalHtml, param);
	strcat(finalHtml, nextTemplatePart);

	free(htmlPart);
	free(param);
	free(templatePart);
	free(nextTemplatePart);

	return finalHtml;
}

int strpos(char* haystack, char* needle) {
	char* str;

	str = strstr(haystack, needle);

	return (str == NULL ? -1 : str - haystack);
}

char* substr(char* source, int start, int end) {
	int size;
	char* output;

	size = end - start + 1;
	output = malloc(size + 1);

	output = memcpy(output, source + start, size);
	output[size] = '\0';

	return output;
}

