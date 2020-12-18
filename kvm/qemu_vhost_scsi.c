/*
 * This is to demonstrate how to use "getfd" to attach vhost-scsi.
 *
 * Boot VM with monitor.sock as QMP.
 *
 * # qemu-system-x86_64 -m 3000M -enable-kvm -smp 8 -vnc :7 \
 *   -net nic -net user,hostfwd=tcp::5027-:22 -hda ol7.qcow2 \
 *   -chardev socket,id=monitor0,server,path=monitor.sock,nowait \
 *   -mon monitor0,mode=control
 *
 * Create vhost target "naa.5001405324af0985" with targetcli.
 *
 * Run below to attach vhost-scsi.
 *
 * ./qemu_vhost_scsi
 * recv: {"QMP": {"version": {"qemu": {"micro": 0, "minor": 2, "major": 5}, "package": ""}, "capabilities": ["oob"]}}
 *
 * send: {"execute":"qmp_capabilities"}
 *
 * recv: {"return": {}}
 *
 * send: {"execute":"getfd","arguments":{"fdname":"vhostfd-name"}}
 *
 * recv: {"return": {}}
 *
 * send: {"execute":"device_add","arguments":{"driver":"vhost-scsi-pci","id":"virtscsi0","wwpn":"naa.5001405324af0985","vhostfd":"vhostfd-name","num_queues":"4"}}
 *
 * recv: {"return": {}}
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char **argv)
{
	int vhostfd, sockfd, ret;
	struct sockaddr_un addr;
	char *buf_getfd = "{\"execute\":\"getfd\",\"arguments\":{\"fdname\":\"vhostfd-name\"}}\r\n";
	char *buf_cap = "{\"execute\":\"qmp_capabilities\"}\r\n";
	char *buf_add = "{\"execute\":\"device_add\",\"arguments\":{\"driver\":\"vhost-scsi-pci\",\"id\":\"virtscsi0\",\"wwpn\":\"naa.5001405324af0985\",\"vhostfd\":\"vhostfd-name\",\"num_queues\":\"4\"}}\r\n";
	char buf_rcv[500];

	struct msghdr msg;
	struct iovec iov[1];
	char control[CMSG_SPACE(sizeof(int))];
	struct cmsghdr *cmsg;

	vhostfd = open("/dev/vhost-scsi", O_RDWR);
	if (vhostfd < 0) {
		printf("failed to open vhost\n");
		return 1;
	}

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	if (sockfd < 0) {
		printf("failed to create socket\n");
		return 1;
	}

	memset(&addr, 0, sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy(addr.sun_path, "monitor.sock");
	
	ret = connect(sockfd, (const struct sockaddr *) &addr, sizeof(addr));
	if (ret < 0) {
		printf("failed to connect");
		return 1;
	}
	
	/* stage 1: enable qmp_capabilities */

	memset(buf_rcv, 0, 500);
	recv(sockfd, buf_rcv, 500, 0);
	printf("recv: %s\n", buf_rcv);

	send(sockfd, buf_cap, strlen(buf_cap), 0);
	printf("send: %s\n", buf_cap);
	
	memset(buf_rcv, 0, 500);
	recv(sockfd, buf_rcv, 500, 0);
	printf("recv: %s\n", buf_rcv);

	/* stage 2: send getfd with SCM_RIGHTS */

	memset(&msg, 0, sizeof(msg));
	memset(control, 0, sizeof(control));

	iov[0].iov_base = (void *)buf_getfd;
	iov[0].iov_len = strlen(buf_getfd);

	msg.msg_iov = iov;
	msg.msg_iovlen = 1;

	msg.msg_control = control;
	msg.msg_controllen = sizeof(control);

	cmsg = CMSG_FIRSTHDR(&msg);
	cmsg->cmsg_len = CMSG_LEN(sizeof(int));
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	memcpy(CMSG_DATA(cmsg), &vhostfd, sizeof(int));

	do {
		ret = sendmsg(sockfd, &msg, 0);
	} while (ret < 0 && errno == EINTR);

	printf("send: %s\n", buf_getfd);

	memset(buf_rcv, 0, 500);
	recv(sockfd, buf_rcv, 500, 0);
	printf("recv: %s\n", buf_rcv);

	/* stage 3: attach the vhost-scsi device */

	send(sockfd, buf_add, strlen(buf_add), 0);
	printf("send: %s\n", buf_add);

	memset(buf_rcv, 0, 500);
	recv(sockfd, buf_rcv, 500, 0);
	printf("recv: %s\n", buf_rcv);

	close(vhostfd);
	close(sockfd);

	return 0;
}
