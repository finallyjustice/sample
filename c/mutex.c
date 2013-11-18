#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int global = 0;

void * do_thread(void *arg)
{
	int i;
	for(i=0; i<5; i++)
	{
		pthread_mutex_lock(&mutex);
		global++;	
		printf("Global: %d\n", global);
		sleep(4);
		pthread_mutex_unlock(&mutex);
	}
}

int main(int argc, char **argv)
{
	pthread_t tid1;
	pthread_t tid2;

	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Cannot init mutex\n");
		return 1;
	}

	if(pthread_create(&tid1, NULL, do_thread, NULL) != 0)
	{
		printf("Cannot create new thread 1\n");
		return 1;
	}

	if(pthread_create(&tid2, NULL, do_thread, NULL) != 0)
	{
		printf("Cannot create new thread 2\n");
		return 1;
	}

	if(pthread_join(tid1, NULL) != 0)
	{
		printf("Cannot join thread 1\n");
		return 1;
	}

	if(pthread_join(tid2, NULL) != 0)
	{
		printf("Cannot join thread 2\n");
		return 1;
	}

	printf("End\n");

	return 0;
}
