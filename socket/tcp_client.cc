#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SRV_PORT 50001

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in srvaddr;

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr("192.168.71.130");
	srvaddr.sin_port = htons(SRV_PORT);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	if(connect(sockfd, (struct sockaddr *)&srvaddr, sizeof(struct sockaddr)) < 0)
	{
		perror("Cannot connect\n");
		return 1;
	}

	while(1);

	char buf[1024];
	memset(buf, 0, 1024);
	sprintf(buf, "Hello World");
	write(sockfd, buf, strlen(buf));

	close(sockfd);

	return 0;
}
