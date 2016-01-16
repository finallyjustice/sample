#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
#include <time.h>  
#include <string.h>  
#include <stdio.h>  
#include <unistd.h>  
#include <stdlib.h>  
    
#define HELLO_PORT 50001  
#define HELLO_GROUP "225.0.0.37"  
    
int main(int argc, char *argv[])  
{  
	struct sockaddr_in addr;  
    int fd, cnt;  
    struct ip_mreq mreq;  
    char *message="Hello, World!\0";  
        
    if ((fd=socket(AF_INET, SOCK_DGRAM, 0)) < 0)   
    {  
		perror("socket");  
        exit(1);  
    }  
    
	memset(&addr, 0, sizeof(addr));  
    addr.sin_family = AF_INET;  
    addr.sin_addr.s_addr = inet_addr(HELLO_GROUP);  
    addr.sin_port = htons(HELLO_PORT);  
        
	while (1)  
    {  
		if (sendto(fd,message, strlen(message)+1, 0, (struct sockaddr *) &addr, sizeof(addr)) < 0)   
        {  
			perror("sendto");  
            exit(1);  
        }  
        sleep(1);  
    }  
        
	return 0;  
}  
