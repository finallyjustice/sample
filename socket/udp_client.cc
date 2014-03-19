#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define SRV_PORT 50001

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in srvaddr;

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	srvaddr.sin_port = htons(SRV_PORT);

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(sockfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	int n;
	char buf[1024];
	memset(buf, 0, 1024);
	sprintf(buf, "Hello World");
	sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr *)&srvaddr,
			sizeof(struct sockaddr));

	return 0;
}
