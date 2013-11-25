#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define SERV_PORT 50001
#define BUF_LEN	  1024

void * process_request(void *arg)
{
	int sockfd = *(int*)arg;
	char recvline[BUF_LEN];
	int len;
	while((len=read(sockfd, recvline, BUF_LEN)) > 0)
	{
		recvline[len] = '\0';
		printf("%s\n", recvline);
	}
	close(sockfd);
}

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int addr_len;
	char *client_ip;
	int client_port;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);

	if(listenfd < 0)
	{
		printf("Cannot create socket\n");
		return 1;
	}

	bzero(&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERV_PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	if(bind(listenfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)))
	{
		printf("Cannot bind port\n");
		return 1;
	}

	listen(listenfd, 128);

	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr *)&client_addr, &addr_len);
		client_ip = inet_ntoa(client_addr.sin_addr);
		client_port = ntohs(client_addr.sin_port);
		printf("From %s:%d\n", client_ip, client_port);

		int sockfd = connfd;
		pthread_t tid;
		if(pthread_create(&tid, NULL, process_request, &sockfd) != 0)
		{
			printf("Cannot create new thread\n");
			return 1;
		}
	}

	close(listenfd);
}
