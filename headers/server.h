#ifndef SERVER_H
#define SERVER_H

#define SRV_BUFF_SIZE 20

typedef struct Server Server;

Server* srvNew(int port, void (*handler)(int sockfd, char* ip, char* data));
void srvListen(Server* srv);
void srvClose(Server* srv);

#endif
