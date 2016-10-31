#ifndef ROUTER_H
#define ROUTER_H

typedef struct Router Router;

Router* routerNew();
void routerAdd(char* method, char* route, void (*action)(), Router* router);
void* routerGet(char* key, Router* router);

#endif
