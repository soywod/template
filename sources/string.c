#include <stdlib.h>
#include <string.h>

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
