#include <stdlib.h>
#include <string.h>

#include "../headers/router.h"
#include "../headers/assoc.h"

typedef struct Router
{
	Assoc* routes;
} Router;

Router* routerNew()
{
	Router* router;

	router = malloc(sizeof(Router));
	router->routes = assocNew();

	return router;
}

void routerAdd(char* method, char* route, void (*action)(), Router* router)
{
	char* key;

	key = malloc(strlen(method) + strlen(route) + 2);
	strcpy(key, method);
	strcat(key, " ");
	strcat(key, route);

	assocAdd(key, action, router->routes);
}

void* routerGet(char* key, Router* router)
{
	return assocGet(key, router->routes);
}
