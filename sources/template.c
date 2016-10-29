#include <stdlib.h> 
#include <stdio.h>
#include <string.h>

#include "../headers/template.h"
#include "../headers/string.h"

typedef struct TemplateParam
{
	char* key;
	char* val;
} TemplateParam;

typedef struct Template
{
	char* input;
	char* output;
	int psize;
	TemplateParam* params;
} Template;

static char* _tplProcess(char* rendered, Template* tpl)
{
	int renderlen, ldatapos, rdatapos;
	char *output, *lpart, *datakey, *dataval, *rpart, *npart;

	renderlen = strlen(rendered);
	ldatapos = strpos(rendered, "@(");

	// If no param found, stop recursion
	if (ldatapos == -1)
	{
		output = malloc(renderlen + 1);
		return strcpy(output, rendered);
	}

	rdatapos = strpos(rendered + ldatapos, ")");

	// Extract all parts of the template
	lpart = substr(rendered, 0, ldatapos - 1);
	datakey = substr(rendered, ldatapos + 2, ldatapos + rdatapos - 1);
	dataval = tplGetParam(datakey, tpl);
	rpart = substr(rendered, ldatapos + rdatapos + 1, renderlen);

	// Process the next template part (recursion)
	npart = _tplProcess(rpart, tpl);
	output = malloc(strlen(lpart) + strlen(dataval) + strlen(npart) + 1);

	strcpy(output, lpart);
	strcat(output, dataval);
	strcat(output, npart);

	free(lpart);
	free(datakey);
	free(rpart);
	free(npart);

	return output;
}

Template* tplOpen(char* path)
{
	FILE *file;
	int fsize;
	Template* tpl;

	tpl = malloc(sizeof(Template));

	// Get file size
	file = fopen(path, "r");
	fseek(file, 0, SEEK_END);
	fsize = ftell(file);

	// Set template input
	fseek(file, 0, SEEK_SET);
	tpl->input = malloc(fsize + 1);
	fread(tpl->input, 1, fsize, file);
	(tpl->input)[fsize] = '\0';

	tpl->params = NULL;
	tpl->psize = 0;
	tpl->output = NULL;

	fclose(file);

	return tpl;
}

void tplAddParam(char* key, char* val, Template* tpl)
{
	if (tpl->psize == 0)
	{
		tpl->params = malloc(sizeof(TemplateParam));
		tpl->params->key = key;
		tpl->params->val = val;
	}
	else
	{
		tpl->params = realloc(tpl->params, sizeof(TemplateParam) * (tpl->psize + 1));
		(tpl->params + tpl->psize)->key = key;
		(tpl->params + tpl->psize)->val = val;
	}

	tpl->psize++;
}

char* tplGetParam(char* key, Template* tpl)
{
	int i;

	for (i = 0; i < tpl->psize; i++)
	{
		if (strcmp((tpl->params + i)->key, key) == 0)
		{
			return (tpl->params + i)->val;
		}
	}

	return key;
}

char* tplRender(Template* tpl)
{
	tpl->output = _tplProcess(tpl->input, tpl);
	return tpl->output;
}


void tplClose(Template* tpl)
{
	if (tpl->output) free(tpl->output);
	if (tpl->params) free(tpl->params);
	free(tpl->input);
	free(tpl);
}
