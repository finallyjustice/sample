#include <sys/mman.h>  /* for mmap and munmap */
#include <sys/types.h> /* for open */
#include <sys/stat.h>  /* for open */
#include <fcntl.h>     /* for open */
#include <unistd.h>   /* for lseek and write */
#include <string.h>    /* for memcpy */
#include <stdio.h>

int main(int argc, char **argv)
{
	int fd;
	int len;
	char *mapped_mem;
	void *start_addr = 0;

	fd = open("testmmap", O_RDWR, S_IRUSR|S_IWUSR);
	len = lseek(fd, 1, SEEK_END);

	mapped_mem = mmap(start_addr, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	int i;
	for(i=0; i<len; i++)
	{
		printf("%c", mapped_mem[i]);
	}

	close(fd);
	munmap(mapped_mem, len);

	return 0;
}
