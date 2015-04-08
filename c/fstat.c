#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	struct stat st;
	stat(argv[1], &st);
	int size = st.st_size;
	printf("Size of %s is %d\n", argv[1], size);
	return 0;
}
