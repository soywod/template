#ifndef TEMPLATE_H
#define TEMPLATE_H

struct TemplateData
{
	char* name;
	char* value;
};

struct Template
{	
	struct TemplateData* data;
	char* (*get)(char* key);
	void (*set)(char* key, char* val);
};

// New API


// Old API
int strpos(char* haystack, char* needle);
char* substr(char* source, int start, int end);
char* processTemplate(char* src, struct TemplateData data[], int dataSize);
char *getFileContent(char *path);

#endif
