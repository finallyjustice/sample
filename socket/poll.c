#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <poll.h>
#include <limits.h>

#define MAXLINE 10240
#define OPEN_MAX 40960

void handle(struct pollfd *clients, int max_client, int nready)
{
	int connfd;
	int i, nread;
	char buf[MAXLINE];

	if(nready == 0)
		return;

	for(i=0; i<max_client; i++)
	{
		connfd = clients[i].fd;
		if(connfd == -1)
			continue;
		if(clients[i].revents & (POLLIN | POLLERR))
		{
			nread = read(connfd, buf, MAXLINE);
			if(nread < 0)
			{
				perror("read error");
				close(connfd);
				clients[i].fd = -1;
				continue;
			}

			if(nread == 0)
			{
				printf("client close the connection");
				close(connfd);
				clients[i].fd = -1;
				continue;
			}

			write(connfd, buf, nread);
			if(--nready <= 0)
				break;
		}
	}
}

int main(int argc, char **argv)
{
	int serv_port = 50001;
	int listenq = 1024;
	int listenfd, connfd;
	struct pollfd clients[OPEN_MAX];
	int maxi;
	socklen_t socklen = sizeof(struct sockaddr_in);
	struct sockaddr_in cliaddr, servaddr;
	char buf[MAXLINE];
	int nready;

	bzero(&servaddr, socklen);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(serv_port);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		perror("socket error");
	}

	int opt = 1;
	if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
	{
		perror("setsockopt error");
	}

	if(bind(listenfd, (struct sockaddr *)&servaddr, socklen) == -1)
	{
		perror("bind error");
		exit(-1);
	}

	if(listen(listenfd, listenq) < 0)
	{
		perror("listen error");
	}

	clients[0].fd = listenfd;
	clients[0].events = POLLIN;

	int i;
	for(i=1; i<OPEN_MAX; i++)
		clients[i].fd = -1;
	maxi = listenfd + 1;

	printf("pollechoserver startup, listen on port:%d\n", serv_port);
	printf("max connection is %d\n", OPEN_MAX);

	for( ; ; )
	{
		nready = poll(clients, maxi+1, -1);
		if(nready == -1)
		{
			perror("poll error");
		}

		if(clients[0].revents & POLLIN)
		{
			connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &socklen);
			sprintf(buf, "accept from %s:%d\n", inet_ntoa(cliaddr.sin_addr), cliaddr.sin_port);
		
			printf("%s\n", buf);

			for(i=0; i<OPEN_MAX; i++)
			{
				if(clients[i].fd == -1)
				{
					clients[i].fd = connfd;
					clients[i].events = POLLIN;
					break;
				}
			}

			if(i == OPEN_MAX)
			{
				fprintf(stderr, "too many connections\n");
				close(connfd);
				continue;
			}

			if(i > maxi)
			{
				maxi = i;
			}

			--nready;
		}

		handle(clients, maxi, nready);
	}

	return 0;
}
