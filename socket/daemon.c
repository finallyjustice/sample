#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	pid_t daemon;
	int i, fd;

	daemon = fork();
	if(daemon < 0)
	{	
		printf("Cannot fork new process\n");
		exit(1);
	}
	else if(daemon > 0)
	{
		printf("Parent process exited\n");
		exit(0);
	}

	setsid();
	umask(0);

	for(i=0; i<getdtablesize(); i++)
		close(i);

	system("wget 0c http://www.qq.com");

	exit(0);
}
