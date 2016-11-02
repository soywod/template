#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

#include "../headers/server.h"

typedef struct Server
{
	int port;
	void (*handler)(int sockfd, char* ip, char* data);
} Server;

Server* srvNew(int port, void (*handler)(int sockfd, char* ip, char* data))
{
	Server* srv;

	srv = malloc(sizeof(Server));
	srv->port = port;
	srv->handler = handler;

	return srv;
}

void srvListen(Server* srv)
{
	int sockfd, newsockfd, sockopt, bindfd, clilen, pid, readfd, i;
	char clip[INET_ADDRSTRLEN];
	struct sockaddr_in servaddr, cliaddr;
	char *buffer, *output;

	sockopt = 1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("Error opening the socket");
		return;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(srv->port);

	bindfd = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	if (bindfd < 0)
	{
		perror("Error binding socket");
		return;
	}

	listen(sockfd, 5);

	clilen = sizeof(cliaddr);

	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);
		i = 0;

		if (newsockfd < 0)
		{
			perror("Error accepting request");
			return;
		}

		pid = fork();

		if (pid < 0)
		{
			perror("Error forking process");
			return;
		}

		if (pid == 0)
		{
			close(sockfd);
			buffer = malloc(SRV_BUFF_SIZE + 1);
			memset(buffer, 0, SRV_BUFF_SIZE + 1);

			while((readfd = recv(newsockfd, buffer, SRV_BUFF_SIZE - 1, MSG_DONTWAIT)) > 0 && readfd == SRV_BUFF_SIZE - 1)
			{
				if (i++ == 0)
				{
					output = malloc(SRV_BUFF_SIZE * i + 1);
					strcpy(output, buffer);
				}
				else
				{
					output = realloc(output, (SRV_BUFF_SIZE * i + 1));
					strcat(output, buffer);
				}

				memset(buffer, 0, SRV_BUFF_SIZE + 1);
			}

			inet_ntop(AF_INET, &(cliaddr.sin_addr), clip, INET_ADDRSTRLEN);
			srv->handler(newsockfd, clip, output);

			//send(newsockfd, reply, strlen(reply), 0);

			close(newsockfd);

			return;
		}
		else
		{
			close(newsockfd);
		}
	}

	return;
}

void srvClose(Server* srv)
{
	free(srv);
}
