#include <stdio.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
	FILE *fp;
	char ch;
	struct stat st;
	int size;

	stat(argv[1], &st);
	size = st.st_size; 
	printf("File Size: %d\n", size);

	if((fp=fopen(argv[1], "r")) == NULL)
	{
		printf("Cannot open file\n");
		return 1;
	}

	while((ch=fgetc(fp)) != EOF)
	{
		putchar(ch);
	}
	fclose(fp);

	if((fp=fopen(argv[2], "rw")) == NULL)
	{
		printf("Cannot open write file\n");
		return 1;
	}

	return 0;
}
