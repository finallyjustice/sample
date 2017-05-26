#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int c;
	char *val;

	printf("init optind=%d\n", optind);

	while ((c = getopt(argc, argv, "abc:d")) != -1) {
		switch (c) {
		case 'a':
			printf("option a optind=%d\n", optind);
			break;
		case 'b':
			printf("option b optind=%d\n", optind);
			break;
		case 'c':
			val = optarg;
			printf("option c optind=%d %s\n", optind, val);
			break;
		case 'd':
			printf("option d optind=%d\n", optind);
			break;
		}
	}

	if (argc != optind + 2) {
		printf("usage: %s [-abc] file1 file2\n", argv[0]);
		return 1;
	}

	return 0;
}
