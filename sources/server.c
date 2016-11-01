#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

#define BUFFER_SIZE 20

int srvListen()
{
	int sockfd, newsockfd, sockopt, bindfd, clilen, pid, readfd, i;
	char buffer[BUFFER_SIZE];
	char clip[INET_ADDRSTRLEN];
	struct sockaddr_in servaddr, cliaddr;
	char* output;

	sockopt = 1;
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		perror("Error opening the socket");
		return 1;
	}

	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &sockopt, sizeof sockopt);

	memset(&servaddr, 0, sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(8080);

	bindfd = bind(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

	if (bindfd < 0)
	{
		perror("Error binding socket");
		return 1;
	}

	listen(sockfd, 5);

	clilen = sizeof(cliaddr);

	while(1)
	{
		newsockfd = accept(sockfd, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);

		if (newsockfd < 0)
		{
			perror("Error accepting request");
			return 1;
		}

		pid = fork();

		if (pid < 0)
		{
			perror("Error forking process");
			return 1;
		}

		if (pid == 0)
		{
			close(sockfd);
			//output = malloc(1);
			//*output = '\0';
			//memset(&buffer, 0, BUFFER_SIZE);
			//i = 0;

			//for (i = 0; readfd == BUFFER_SIZE - 1; i++, readfd = read(newsockfd, buffer, BUFFER_SIZE - 1))

			//while((readfd = read(newsockfd, buffer, BUFFER_SIZE - 1)) == BUFFER_SIZE - 1);
			//{
			//	output = realloc(output, (BUFFER_SIZE * (++i)) + 1);
			//	strcat(output, buffer);
			//	printf("%d - %d - %s", readfd, BUFFER_SIZE, buffer);
			//} 
			do
			{
				readfd = recv(newsockfd, buffer, BUFFER_SIZE - 1, MSG_DONTWAIT);
				printf("%d\n", readfd);
			} while(readfd > 0 && readfd == BUFFER_SIZE - 1);
			printf("FINISHED");
			
		//	if (readfd < 0) 
		//	{
		//		perror("Error reading data");
		//		return 1;
		//	}

			inet_ntop(AF_INET, &(cliaddr.sin_addr), clip, INET_ADDRSTRLEN);

			//send(newsockfd, reply, strlen(reply), 0);

			close(newsockfd);

			return 0;

		}
		else
		{
			close(newsockfd);
		}
	}

	return 0;
}
