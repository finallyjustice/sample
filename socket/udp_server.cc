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
	int listenfd;
	struct sockaddr_in srvaddr;
	struct sockaddr_in cliaddr;
	char *client_ip;
	int client_port;
	socklen_t addr_len;

	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = INADDR_ANY;
	srvaddr.sin_port = htons(SRV_PORT); 

	listenfd = socket(AF_INET, SOCK_DGRAM, 0);
	if(listenfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	if(bind(listenfd, (struct sockaddr *)&srvaddr, sizeof(struct sockaddr)) < 0)
	{
		perror("Cannot bind\n");
		return 1;
	}

	while(1)
	{
		int n;
		char buf[1024];

		recvfrom(listenfd, buf, 1024, 0, (struct sockaddr *)&cliaddr, &addr_len);
		client_ip = inet_ntoa(cliaddr.sin_addr);
		client_port = ntohs(cliaddr.sin_port);
		cout<<"From: "<<client_ip<<":"<<client_port<<endl;
		cout<<"Conten: "<<buf<<endl;
	}

	close(listenfd);

	return 0;
}
