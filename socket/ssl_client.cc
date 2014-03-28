/** File:		ssl_client.cc
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

/* This is the program running SSL client */

// usage: g++ ssl_client.cc -o ssl_client -lssl -lcrypto
// openssl genrsa -out privkey.pem 2048
// openssl req -new -x509 -key privkey.pem -out cacert.pem -days 1095

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <openssl/evp.h>

using namespace std;

#define SRV_PORT 50000
#define BUF_LEN 1024

int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in srv_addr;

	SSL_CTX *ctx;
	SSL *ssl;

	// Initialize the SSL library
	SSL_library_init();

	// Load all SSL algorithms	
	OpenSSL_add_all_algorithms();

	// Load SSL error messages
	SSL_load_error_strings();

	// create a SSL Content Text with SSL V2 and V3 standard
	ctx = SSL_CTX_new(SSLv23_client_method());
	if(ctx == NULL)
	{
		ERR_print_errors_fp(stdout);
		return 1;
	}

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	bzero(&srv_addr, sizeof(srv_addr));
	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	srv_addr.sin_port = htons(SRV_PORT);

	if(connect(sockfd, (struct sockaddr *)&srv_addr, sizeof(struct sockaddr)) != 0)
	{
		perror("Cannot connect to server\n");
		return 1;
	}

	// Create a new SSL 
	ssl = SSL_new(ctx);

	// add sockfd into SSL
	SSL_set_fd(ssl, sockfd);

	// connect to SSL server
	if(SSL_connect(ssl) == -1)
	{
		ERR_print_errors_fp(stderr);
		return 1;
	}

	// print the information of received SSL certificate from server
	X509 *cert;
	char *cert_info;
	cert = SSL_get_peer_certificate(ssl);
	if(cert != NULL)
	{
		printf("Certificate Info:\n");

		cert_info = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		printf("Cert: %s\n", cert_info);
		free(cert_info);

		X509_free(cert);
	}
	else
	{
		printf("No certificate received from server side\n");
	}

	char send_line[BUF_LEN];
	char recv_line[BUF_LEN];
	memset(send_line, 0, BUF_LEN);
	memset(recv_line, 0, BUF_LEN);

	int len = SSL_read(ssl, recv_line, BUF_LEN);
	if(len > 0)
	{
		printf("RECV: %s\n", recv_line);
	}

	sprintf(send_line, "This is client");
	len = SSL_write(ssl, send_line, strlen(send_line));
	if(len < 0)
	{
		printf("Failed to send message\n");
		return 1;
	}

	SSL_shutdown(ssl);
	SSL_free(ssl);
	close(sockfd);
	SSL_CTX_free(ctx);

	return 0;
}
