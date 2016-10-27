#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

int strpos(char* haystack, char* needle) {
	char* substr = strstr(haystack, needle);
	return (substr == NULL ? -1 : substr - haystack);
}

char* substr(char* source, int start, int end) {
	int size = end - start + 1;
	char* output = malloc(sizeof(char) * size);

	memcpy(output, source + start, size);
	return output;
}

int main() {
	char* template = "coucouc {{name}} la forme ?";
	char* lpart = substr(template, 0, strpos(template, "{{")-1);
	char* rpart = substr(template, strpos(template, "}}")+2, strlen(template));
	char* variable = substr(template, strpos(template, "{{")+2, strpos(template, "}}")-1);
	printf("lpart: %s\nrpart: %s\nvariable: %s", lpart, rpart, variable);
}
