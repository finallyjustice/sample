#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define SRV_PORT 50002

int main(int argc, char **argv)
{
	int listenfd;
	int connfd;
	struct sockaddr_in srvaddr;
	struct sockaddr_in cliaddr;
	socklen_t addr_len;
	char *client_ip;
	int client_port;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = INADDR_ANY;
	srvaddr.sin_port = htons(SRV_PORT);

	if(bind(listenfd, (struct sockaddr *)&srvaddr, sizeof(struct sockaddr)) < 0)
	{
		perror("Cannot bind\n");
		return 1;
	}

	listen(listenfd, 128);

	while(1)
	{
		connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &addr_len);

		client_ip = inet_ntoa(cliaddr.sin_addr);
		client_port = ntohs(cliaddr.sin_port);
		cout<<"From: "<<client_ip<<":"<<client_port<<endl;
		
		char buf[1024];
		int len;
		memset(buf, 0, 1024);
		while((len=read(connfd, buf, 1024)) > 0)
		{
			buf[len] = '\0';
			cout<<"Content: "<<buf<<endl;
		}

		close(connfd);
	}

	close(listenfd);
}
