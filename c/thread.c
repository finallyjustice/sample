#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void * do_thread(void *arg)
{
	printf("Hello World\n");
	sleep(5);
}

int main(int argc, char **argv)
{
	pthread_t tid;

	if(pthread_create(&tid, NULL, do_thread, NULL) != 0)
	{
		printf("Cannot create new thread\n");
		return 1;
	}

	if(pthread_join(tid, NULL) != 0)
	{
		printf("Cannot join thread\n");
		return 1;
	}

	printf("Main Ends\n");

	return 0;
}
