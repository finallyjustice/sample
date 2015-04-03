#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define SYS_CONCACTFILES 316

struct concat_params
{
	char **in_files;
	char *out_file;
	int num_files;
};

int main(int argc, char **argv)
{
	int opt, idx, i;
	const char *opt_str = "n:i:o:";
	struct concat_params *cp = malloc(sizeof(struct concat_params));
	cp->num_files = 0;
	char *tmp;

	opt = getopt(argc, argv, opt_str);
	while(opt != -1)
	{
		switch(opt)
		{
			case 'n':
				cp->num_files = atoi(optarg);
				break;

			case 'o':
				tmp = optarg;
				cp->out_file = (char *)malloc(strlen(tmp)+1);
				memcpy(cp->out_file, tmp, strlen(tmp)+1);
				break;

			case 'i':
				if(cp->num_files == 0)
					goto out;
				cp->in_files = (char **)malloc(sizeof(char *)*cp->num_files);
				for(i=0; i<cp->num_files; i++)
				{
					idx = optind-1+i;
					if(idx >= argc)
						goto out;
					cp->in_files[i] = (char *)malloc(strlen(argv[idx])+1);
					memcpy(cp->in_files[i], argv[idx], strlen(argv[idx])+1);
				}
				break;
		}
		opt = getopt(argc, argv, opt_str);
	}

	syscall(SYS_CONCACTFILES, cp);
	return 0;

out:
	printf("usage error\n");
	return -1;
}
