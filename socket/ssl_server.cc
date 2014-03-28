/** File:		ssl_server.cc
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

/* This is the program running SSL server */

// Usage: g++ ssl_server.cc -o ssl_server -lssl -lcrypto
// openssl genrsa -out privkey.pem 2048
// openssl req -new -x509 -key privkey.pem -out cacert.pem -days 1095

#include <cstdio>
#include <cstdlib>
#include <errno.h>
#include <cstring>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

using namespace std;

#define SRV_PORT 50000
#define BUF_LEN 1024


int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in srv_addr;
	SSL_CTX *ctx;

	// initialize the SSL library
	SSL_library_init();

	// Load all SSL algorithms
	OpenSSL_add_all_algorithms();

	// Load SSL error messages
	SSL_load_error_strings();

	// create a SSL Content Text with SSL V2 and V3 standard
	// we can also use SSv2_server_method() or SSLv3_server_method()
	ctx = SSL_CTX_new(SSLv23_server_method());
	if(ctx == NULL)
	{
		ERR_print_errors_fp(stdout);
		return 1;
	}

	// load the digital certificate and send it to client, including public key
	if(SSL_CTX_use_certificate_file(ctx, "cert.pem", SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stdout);
		return 1;
	}

	// load the secret key
	if(SSL_CTX_use_PrivateKey_file(ctx, "prv.pem", SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stdout);
		return 1;
	}

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("cannot create socket\n");
		return 1;
	}

	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = INADDR_ANY;
	srv_addr.sin_port = htons(SRV_PORT);

	int yes = 1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1)
	{
		perror("setsockopt failed\n");
		return 1;
	}

	if(bind(sockfd, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr)) < 0)
	{
		perror("failed to bind\n");
		return 1;
	}

	listen(sockfd, 100);

	char send_line[BUF_LEN];
	char recv_line[BUF_LEN];

	for(;;)
	{
		int subfd = accept(sockfd, NULL, NULL);
		int len;

		// create a new SSL
		SSL *ssl = SSL_new(ctx);

		// add subfd into SSL
		SSL_set_fd(ssl, subfd);
		if(SSL_accept(ssl) == -1)
		{
			perror("Cannot accept SSL\n");
			goto finish;
		}

		memset(send_line, 0, BUF_LEN);
		sprintf(send_line, "Hello World!");
		
		// send the message over SSL connection
		len = SSL_write(ssl, send_line, strlen(send_line));
		if(len <= 0)
		{
			perror("Failed to send message over SSL\n");
			goto finish;
		}

		memset(recv_line, 0, BUF_LEN);

		// receive the message over SSL connection
		len = SSL_read(ssl, recv_line, BUF_LEN);
		if(len > 0)
		{
			printf("RECV: %s\n", recv_line);
		}

	finish:
		// close the SSL connection
		SSL_shutdown(ssl);
		// free SSL 
		SSL_free(ssl);

		close(subfd);
	}

	close(sockfd);
	// free CTX
	SSL_CTX_free(ctx);
	return 0;
}
