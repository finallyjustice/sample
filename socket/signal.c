#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

void handler(int arg)
{
	if(arg == SIGINT)
		printf("Hello World\n");
	if(arg == SIGQUIT)
		printf("Hello Quit\n");
	exit(0);
}

int main(int argc, char **argv)
{
	signal(SIGINT, handler);
	while(1)
	{
		
	}
}
