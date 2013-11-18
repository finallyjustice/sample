#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem;

void * do_thread(void *arg)
{
	while(1)
	{
		sem_wait(&sem);
		printf("Hello World\n");
		sleep(2);
	}
}

int main(int argc, char **argv)
{
	pthread_t tid;

	if(sem_init(&sem, 0, 5) != 0)
	{
		printf("Init sem failed\n");
		return 1;
	}

	if(pthread_create(&tid, NULL, do_thread, NULL) != 0)
	{
		printf("Cannot create thread\n");
		return 1;
	}

	while(1)
	{
		//sem_post(&sem);
		printf("In wait sleep for a while\n");
		sleep(2);
	}

	if(pthread_join(tid, NULL) != 0)
	{
		printf("Cannot join thread\n");
		return 1;
	}

	printf("Ene\n");

	return 0;
}
