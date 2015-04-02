#include <stdio.h>
#include <getopt.h>

int main(int argc, char **argv)
{
	int opt;
	const char * opt_str = "abcAm:h";
	opt = getopt(argc, argv, opt_str);

	while(opt != -1)
	{
		switch(opt)
		{
			case 'a':
				printf("[a]\n");
				break;

			case 'b':
				printf("[b]\n");
				break;

			case 'c':
				printf("[c]\n");
				break;
		
			case 'A':
				printf("[A]\n");
				break;

			case 'm':
				printf("[m]: %s\n", optarg);
				break;

			case 'h':
				printf("[h]\n");
				break;
			default:
				printf("error: option [%c] is not supported\n", opt);
				break;
		}
		opt = getopt(argc, argv, opt_str);
	}
	return 0;
}
