// gcc aio.c -o aio -lrt

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <aio.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define BUFSIZE 1024
#define MAX_LIST 8

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

	struct aioct *cblist[MAX_LIST];
	bzero((char *)cblist, sizeof(cblist));
	cblist[0] = &my_aiocb;

	ret = aio_read(&my_aiocb);
	if (ret < 0)
		perror("aio_read");

	/* 
	 * aio_suspend will return when any "ONE" of the cb is finished!
	 */
	ret = aio_suspend(cblist, MAX_LIST, NULL);

	printf("data: %s\n", (char *)my_aiocb.aio_buf);
	return 0;
}
