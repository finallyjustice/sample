#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int SERVER_PORT=1;

#define  WRITE_BUF_SIZE  1024
#define  SUCCESS 0
#define  FAILURE -1

int main(int argc, char **argv)
{
    int iSockFd;
    int iReadNum;
    char acBuf[WRITE_BUF_SIZE];
    struct sockaddr_in stServerAddr;
    struct sockaddr_in stClientAddr;
    int iServerLen;
    int iClientLen;
    int iReturn;

    printf("scanning ...... \n");

    while(SERVER_PORT<60000)
    {
    	// create server socket
    	iSockFd = socket(AF_INET, SOCK_STREAM, 0);
    	if (iSockFd < 0)
    	{
        	printf("socket create failed in CommManageServerRecvThread.\n");
			return FAILURE;
    	}
   	 	stServerAddr.sin_family = AF_INET;
    	inet_pton(AF_INET, argv[1], &stServerAddr.sin_addr);
    	stServerAddr.sin_port = htons(SERVER_PORT);
    	iServerLen = sizeof(stServerAddr);
     	
		iReturn = connect(iSockFd, (const struct sockaddr *)&stServerAddr, iServerLen);
        if(iReturn >= 0)
        {
			sleep(1);
			printf("port %d open\n",SERVER_PORT);
        }
		//else
		//{
		//	printf("Hello\n");
		//}
		
		close(iSockFd);
		SERVER_PORT++;
	}
    return SUCCESS;
}
