#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;

#define SRV_PORT1 50001 // port number of server 1
#define SRV_PORT2 50002 // port number of server 2

int main(int argc, char **argv)
{
	int listenfd1, listenfd2;
	struct sockaddr_in srvaddr1, srvaddr2;
	int connfd;
	struct sockaddr_in cliaddr;
	socklen_t addr_len;
	char *client_ip;
	int client_port;

	srvaddr1.sin_family = AF_INET;
	srvaddr1.sin_addr.s_addr = INADDR_ANY;
	srvaddr1.sin_port = htons(SRV_PORT1);
	srvaddr2.sin_family = AF_INET;
	srvaddr2.sin_addr.s_addr = INADDR_ANY;
	srvaddr2.sin_port = htons(SRV_PORT2);

	listenfd1 = socket(AF_INET, SOCK_STREAM, 0);
	listenfd2 = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd1<0 || listenfd2<0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	if(bind(listenfd1, (struct sockaddr *)&srvaddr1, sizeof(struct sockaddr)) < 0)
	{
		perror("Cannot bind server 1\n");
		return 1;
	}
	if(bind(listenfd2, (struct sockaddr *)&srvaddr2, sizeof(struct sockaddr)) < 0)
	{
		perror("Cannot bind server 2\n");
		return 1;
	}

	listen(listenfd1, 128);
	listen(listenfd2, 128);

	int maxfdp1;
	fd_set rset;
	char buf[1024];
	
	FD_ZERO(&rset);
	while(1)
	{
		FD_SET(listenfd1, &rset); // add server 1 listensock in rset
		FD_SET(listenfd2, &rset); // add server 2 listensock in rset
		FD_SET(fileno(stdin), &rset);
		
		maxfdp1 = max(listenfd1, listenfd2);
		maxfdp1 = max(maxfdp1, fileno(stdin))+1;

		select(maxfdp1, &rset, NULL, NULL, NULL);
		
		// connection request for server 1
		if(FD_ISSET(listenfd1, &rset))
		{
			bzero(&cliaddr, sizeof(cliaddr));
			connfd = accept(listenfd1, (struct sockaddr *)&cliaddr,
					&addr_len);
			client_ip = inet_ntoa(cliaddr.sin_addr);
			client_port = ntohs(cliaddr.sin_port);
			cout<<"Server1: From "<<client_ip<<":"<<client_port<<endl;
			int len;
			memset(buf, 0, 1024);
			while((len=read(connfd, buf, 1024)) > 0)
			{
				buf[len] = '\0';
				cout<<"Content: "<<buf<<endl;
			}
			close(connfd);
		}

		// connection request for server 2
		if(FD_ISSET(listenfd2, &rset))
		{
			bzero(&cliaddr, sizeof(cliaddr));
			connfd = accept(listenfd2, (struct sockaddr *)&cliaddr, 
					&addr_len);
			client_ip = inet_ntoa(cliaddr.sin_addr);
			client_port = ntohs(cliaddr.sin_port);
			cout<<"Server2: From"<<client_ip<<":"<<client_port<<endl;
			int len;
			memset(buf, 0, 1024);
			while((len=read(connfd, buf, 1024)) > 0)
			{
				buf[len] = '\0';
				cout<<"Content: "<<buf<<endl;
			}
			close(connfd);
		}

		// close both servers
		if(FD_ISSET(fileno(stdin), &rset))
		{
			break;
		}
	}

	close(listenfd1);
	close(listenfd2);

	return 0;
}
