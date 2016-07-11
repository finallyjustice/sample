#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <net/route.h>

int interface_up(char *interface_name)
{
	int s;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error create socket: %d\n", errno);
		return -1;
	}

	struct ifreq ifr;
	strcpy(ifr.ifr_name, interface_name);

	short flag;
	flag = IFF_UP;
	if (ioctl(s, SIOCGIFFLAGS, &ifr) < 0) {
		printf("Error up %s:%d\n", interface_name, errno);
		return -1;
	}

	ifr.ifr_ifru.ifru_flags |= flag;

	if (ioctl(s, SIOCSIFFLAGS, &ifr) < 0) {
		printf("Error up %s:%d\n", interface_name, errno);
		return -1;
	}

	return 0;
}

int set_ipaddr(char *interface_name, char *ip)
{
	int s;

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("Error up %s:%d\n", interface_name, errno);
		return -1;
	}

	struct ifreq ifr;
	strcpy(ifr.ifr_name, interface_name);

	struct sockaddr_in addr;
	bzero(&addr, sizeof(struct sockaddr_in));
	addr.sin_family = PF_INET;
	inet_aton(ip, &addr.sin_addr);

	memcpy(&ifr.ifr_ifru.ifru_addr, &addr, sizeof(struct sockaddr_in));

	if (ioctl(s, SIOCSIFADDR, &ifr) < 0) {
		printf("Error set %s ip: %d\n", interface_name, errno);
		return -1;
	}

	return 0;
}

int tun_create(char *dev, int flags)
{
	struct ifreq ifr;
	int fd, err;

	if ((fd = open("/dev/net/tun", O_RDWR)) < 0) {
		printf("Error open: %d\n", errno);
		return -1;
	}

	memset(&ifr, 0, sizeof(ifr));
	ifr.ifr_flags |= flags;

	if (*dev != '\0')
		strncpy(ifr.ifr_name, dev, IFNAMSIZ);
	
	if ((err = ioctl(fd, TUNSETIFF, (void *)&ifr)) < 0) {
		printf("Error ioctl: %d\n", errno);
		close(fd);
		return -1;
	}

	strcpy(dev, ifr.ifr_name);

	return fd;
}

/* add route to 10.0.0.1
 * # route add 10.0.0.1 dev tun0
 */
int route_add(char *interface_name)
{
	int skfd;
	struct rtentry rt;

	struct sockaddr_in dst;
	struct sockaddr_in gw;
	struct sockaddr_in genmask;

	memset(&rt, 0, sizeof(struct rtentry));

	genmask.sin_addr.s_addr = inet_addr("255.255.255.255");

	bzero(&dst, sizeof(struct sockaddr_in));
	dst.sin_family = PF_INET;
	dst.sin_addr.s_addr = inet_addr("10.0.0.1");

	rt.rt_metric = 0;
	rt.rt_dst = *(struct sockaddr *)&dst;
	rt.rt_genmask = *(struct sockaddr *)&genmask;

	rt.rt_dev = interface_name;
	rt.rt_flags = RTF_UP | RTF_HOST;

	skfd = socket(AF_INET, SOCK_DGRAM, 0);
	if (ioctl(skfd, SIOCADDRT, &rt) < 0) {
		printf("Error route add : %d\n", errno);
		return -1;
	}
}

int main(int argc, char **argv)
{
	int tun, ret;
	char tun_name[IFNAMSIZ];
	unsigned char buf[4096];
	unsigned char ip[4];

	tun_name[0] = '\0';
	tun = tun_create(tun_name, IFF_TUN | IFF_NO_PI);
	if (tun < 0)
		return 1;
	printf("TUN name is %s\n", tun_name);

	interface_up(tun_name);
	route_add(tun_name);

	while (1) {
		ret = read(tun, buf, sizeof(buf));
		printf("read %d bytes\n", ret);

		int i;
		for (i = 0; i < ret; i++)
			printf("%02x", buf[i]);
		printf("\n");

		if (ret < 0)
			break;

		memcpy(ip, &buf[12], 4);
		memcpy(&buf[12], &buf[16], 4);
		memcpy(&buf[16], ip, 4);
		buf[20] = 0;
		*((unsigned short *)&buf[22]) += 8;

		ret = write(tun, buf, ret);
		printf("write %d bytes\n", ret);
	}

	return 0;
}
