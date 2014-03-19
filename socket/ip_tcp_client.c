#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <linux/tcp.h>

unsigned short inet_checksum(unsigned short *ptr,int nbytes)
{
	register long           sum;            /* assumes long == 32 bits */
	u_short                 oddbyte;
	register u_short        answer;         /* assumes u_short == 16 bits */

	/*
	* Our algorithm is simple, using a 32-bit accumulator (sum),
	* we add sequential 16-bit words to it, and at the end, fold back
	* all the carry bits from the top 16 bits into the lower 16 bits.
	 */

	sum = 0;
	while (nbytes > 1)
	{
		sum += *ptr++;
		nbytes -= 2;
	}

	/* mop up an odd byte, if necessary */
	if (nbytes == 1)
	{
		oddbyte = 0;            /* make sure top half is zero */
		*((u_char *) &oddbyte) = *(u_char *)ptr;   /* one byte only */
		sum += oddbyte;
	}

	/*
	* Add back carry outs from top 16 bits to low 16 bits.
	*/

	sum  = (sum >> 16) + (sum & 0xffff);    /* add high-16 to low-16 */
	sum += (sum >> 16);                     /* add carry */
	answer = ~sum;          /* ones-complement, then truncate to 16 bits */
	return(answer);
}


int main(int argc, char **argv)
{
	int sockfd;
	struct sockaddr_in srvaddr;
	
	bzero(&srvaddr, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr("192.168.71.130");
	srvaddr.sin_port = htons(50010); // port is not necessary

	sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
	if(sockfd < 0)
	{
		perror("Cannot create socket\n");
		return 1;
	}

	int on = 1;
	setsockopt(sockfd, IPPROTO_IP, IP_HDRINCL, &on, sizeof(on));
	setuid(getpid());

	char buf[128];
	int buf_size;
	memset(buf, 0, 128);

	//buf_size = sizeof(struct ip)+sizeof(struct tcphdr)+64;
	buf_size = sizeof(struct ip)+sizeof(struct tcphdr);
	
	struct ip *ip = (struct ip *)buf;
	ip->ip_v = IPVERSION;
	ip->ip_hl = sizeof(struct ip)>>2;
	ip->ip_tos = 0;
	ip->ip_len = htons(buf_size);
	ip->ip_id = 0;
	ip->ip_off = 0;
	ip->ip_ttl = MAXTTL;
	ip->ip_p = IPPROTO_TCP;
	ip->ip_sum = 0;
	ip->ip_src.s_addr = inet_addr("192.168.71.128");
	ip->ip_dst.s_addr = inet_addr("192.168.71.130");

	struct tcphdr *tcp = (struct tcphdr *)(buf+sizeof(struct ip));
	tcp->source = htons(50004);
	tcp->dest = htons(50010);
	tcp->seq = htonl(100);
	tcp->ack_seq = htonl(0);
	tcp->doff = 5;
	tcp->syn = 1;
	tcp->window = htons(5840);
	tcp->check = inet_checksum((unsigned short *)ip, sizeof(struct ip) + sizeof(struct tcphdr));

	//char *cont = buf+sizeof(struct ip)+sizeof(struct tcphdr);
	//sprintf(cont, "Hello World");

	sendto(sockfd, buf, buf_size, 0, (struct sockaddr *)&srvaddr, sizeof(struct
				sockaddr));	

	return 0;
}
