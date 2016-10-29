#ifndef TEMPLATE_H
#define TEMPLATE_H

typedef struct Template Template;
struct TemplateParam;

Template* tplOpen(char* path);
void tplAddParam(char* key, char* val, Template* tpl);
char* tplGetParam(char* key, Template* tpl);
char* tplRender(Template* tpl);
void tplClose(Template* tpl);

#endif
