#include <stdio.h>
#include <time.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int signal)
{
	printf("This is alarm!\n");
}

int main(int argc, char **argv)
{
	int i = 0;
	struct sigaction sa;
	
	sa.sa_handler = alarm_handler;
	sa.sa_flags = 0;

	if(sigaction(SIGALRM, &sa, NULL))
	{
		printf("sigaction error!\n");
		return -1;
	}

	alarm(5);

	while(1);
	printf("Hello World!\n");

	return 0;
}
