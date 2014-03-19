#include <iostream>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <errno.h>
#include <cstring>
#include <stdlib.h>

using namespace std;

#define SRV_PORT 50002

int main(int argc, char **argv)
{
	int epfd;
	int listenfd;
	
	struct epoll_event ev;         // for registration of events
	struct epoll_event events[20]; // events returned by epoll
	epfd = epoll_create(256);

	struct sockaddr_in srvaddr;
	struct sockaddr_in cliaddr;
	
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	ev.data.fd = listenfd;
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
	
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

	int maxi = 0;
	while(1)
	{
		int nfds = epoll_wait(epfd, events, 20, 500);

		int i;
		for(i=0; i<nfds; i++)
		{
			if(events[i].data.fd == listenfd)
			{
				int connfd = accept(listenfd, NULL, NULL);
				if(connfd < 0)
				{
					perror("connfd<0\n");
					exit(1);
				}

				cout<<"Accept a connection"<<endl;

				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);
			}
			else if(events[i].events & EPOLLIN)
			{
				int sockfd = events[i].data.fd;	
				if(sockfd < 0)
					continue;

				int n;
				char buf[1024];
				memset(buf, 0, 1024);
				n=read(sockfd, buf, 1024);
				if(n > 0)
				{
					buf[n] = '\0';
					cout<<"Content: "<<buf<<endl;
				}
			}
		}
	}

	close(listenfd);

	return 0;
}
