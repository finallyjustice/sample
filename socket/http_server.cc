/** File:		single_server.c
 ** Author:		Dongli Zhang
 ** Contact:	dongli.zhang0129@gmail.com
 **
 ** Copyright (C) Dongli Zhang 2013
 **
 ** This program is free software;  you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY;  without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 ** the GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program;  if not, write to the Free Software 
 ** Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/* This program is a single thread regular HTTP server.
   It can help understand HTTP protocol and how to implement 
   the HTTP server.
   In this program, only one HTTP is processed each time.
*/

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

using namespace std;

#define PEND_CONNECTIONS 100  
#define SRV_PORT 8000		 // port number of web server
#define BUF_LEN 1024

/* 
  The following const chars:
  http_error_hdr : html 404 error header
  http_error_html: html 404 error body
  http_html_hdr  : html response image header
  http_image_hdr : html response regular header
*/
const static char http_error_hdr[]  = "HTTP/1.1 404 Not Found\r\nContent-type: text/html\r\n\r\n";
const static char http_error_html[] = "<html><body><h1>FILE NOT FOUND</h1></body></html>";
const static char http_html_hdr[]   = "HTTP/1.1 200 OK\r\nContent-type: text/html\r\n\r\n";
const static char http_image_hdr[]  = "HTTP/1.1 200 OK\r\nContent-Type: image/gif\r\n\r\n";

int main(int argc, char **argv)
{
	int sockfd; // listening socket
	int subfd;  // accepted socket
	struct sockaddr_in srv_addr;
	struct sockaddr_in cli_addr;

	char *cli_ip;
	int cli_port;
	socklen_t addr_len;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_port = htons(SRV_PORT);
	srv_addr.sin_addr.s_addr = INADDR_ANY;

	// allow reuse the port number if server failed
	int yes = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) 
	{
		perror("setsockopt failed\n");
		return 1;
	}

	if(bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr_in)) < 0)
	{
		perror("Cannot bind port\n");
		return 1;
	}

	listen(sockfd, PEND_CONNECTIONS);

	for(;;)
	{
		// collect the client IP and client port
		addr_len = sizeof(cli_addr);
		subfd = accept(sockfd, (struct sockaddr *)&cli_addr, &addr_len);
		cli_ip = inet_ntoa(cli_addr.sin_addr);
		cli_port = ntohs(cli_addr.sin_port);

		printf("HTTP request from: %s:%d.\n", cli_ip, cli_port);

		char request_content[BUF_LEN];  // HTTP requested detail
		int fd;							// file descriptor of client's requested file

		// receive the http request
		read(subfd, request_content, BUF_LEN);

		// process the HTTP request
		// check if the command is GET
		if(!strncmp(request_content, "GET", 3))
		{
			// file path is the path of requested file
			char *file_path = request_content + 5;
			file_path = strchr(file_path, ' ');
			*file_path = '\0';
			file_path = request_content + 5;

			// open the requested file
			// file_path caches the requested file path(name)
			fd = open(file_path, O_RDONLY, S_IREAD | S_IWRITE);
			if(fd == -1)	// if file does NOT exist
			{
				printf("Failed to open file %s.\n", file_path);
				// send back error header and error message
				write(subfd, http_error_hdr, strlen(http_error_hdr));
				write(subfd, http_error_html, strlen(http_error_html));
			}
			else // send the file back to client
			{
				printf("File %s is being sent.\n", file_path);
		
				// send html header to client to specify the type of this response
				if(strstr(file_path, ".jpg")!=NULL || strstr(file_path, ".gif")!=NULL)
					write(subfd, http_image_hdr, strlen(http_image_hdr));
				else
					write(subfd, http_html_hdr, strlen(http_html_hdr));

				char send_buf[BUF_LEN];
				int buf_len = 1;
				
				while(buf_len > 0)
				{
					buf_len = read(fd, send_buf, BUF_LEN);
					if(buf_len > 0)
					{
						// send file back to client
						write(subfd, send_buf, buf_len);
					}
				}
			}

			// close the requested file
			close(fd);
		}
		else
		{
			// ignore this request if the command is not GET
			cout<<"unsupported request!"<<endl;
		}

		// close the accepted connection socket
		close(subfd);
	}

	return 1;
}
