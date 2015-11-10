// gcc aio.c -o aio -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 1024

int main(int argc, char **argv)
{
	int fd, ret;
	struct aiocb my_aiocb;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
		perror("open");

	bzero(&my_aiocb, sizeof(struct aiocb));

	my_aiocb.aio_fildes = fd;
	my_aiocb.aio_buf = malloc(BUFSIZE + 1);
	my_aiocb.aio_nbytes = BUFSIZE;
	my_aiocb.aio_offset = 0;

	ret = aio_read(&my_aiocb);
	if (ret < 0)
		perror("aio_read");

	while (aio_error(&my_aiocb) == EINPROGRESS) 
		continue;

	if ((ret=aio_return(&my_aiocb)) > 0) { 
		printf("aio return value: %d\n", ret);
	} else {
		perror("aio_return");
	}
	printf("data: %s\n", (char *)my_aiocb.aio_buf);
	return 0;
}
