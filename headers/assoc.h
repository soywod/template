#ifndef ASSOC_H
#define ASSOC_H

typedef struct Assoc Assoc;
struct AssocItem;

Assoc* assocNew();
void assocAdd(char* key, char* val, Assoc* assoc);
void assocSet(char* key, char* val, Assoc* assoc);
char* assocGet(char* key, Assoc* assoc);
void assocClose(Assoc* assoc);

#endif
