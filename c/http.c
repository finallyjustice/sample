#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

#define BUF_LEN 1028
#define SERV_PORT 8000

const static char http_error_hdr[]	= "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n";  
const static char http_html_hdr[]	= "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";  
const static char http_index_html[] = "<html><head><title>Congrats!</title></head><body><h1>Welcome to our HTTP server demo!</h1><p>This is a just small test page.</body></html>";  

int http_send_file(char *filename, int sockfd)
{
	if(!strcmp(filename, "/"))
	{
		write(sockfd, http_html_hdr, strlen(http_html_hdr));
		write(sockfd, http_index_html, strlen(http_index_html));
	}
	else
	{
		printf("File not found\n");
		write(sockfd, http_error_hdr, strlen(http_error_hdr));
	}

	return 0;
}

void serve(int sockfd)
{
	char buf[BUF_LEN];
	read(sockfd, buf, BUF_LEN);
	if(!strncmp(buf, "GET", 3))
	{
		char *file = buf+4;
		char *space = strchr(file, ' ');
		*space = '\0';
		http_send_file(file, sockfd);
	}
	else
	{
		printf("unsupported request\n");
		return;
	}
}
	
int main(int argc, char **argv)
{
	int sockfd;
	int subfd;
	struct sockaddr_in servaddr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		printf("Cannot create socket\n");
		return 1;
	}

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(SERV_PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if(bind(sockfd, (struct sockaddr *)&servaddr, sizeof(struct sockaddr_in)))
	{
		perror("Cannot bind port\n");
		return 1;
	}

	listen(sockfd, 128);

	for(;;)
	{
		subfd = accept(sockfd, NULL, NULL);
		serve(subfd);
		close(subfd);
	}

	return 0;	
}
