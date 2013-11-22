#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
pthread_cond_t ready;
int global = 10;
void * do_thread(void *arg)
{
	int id = *(int *)arg;	
	while(1)
	{
		pthread_mutex_lock(&mutex);

		while(global <= 0)
		{
			pthread_cond_wait(&ready, &mutex);
		}

		global--;
		printf("Consumer %d: global is %d\n", id, global);
			
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

int main(int argc, char **argv)
{
	pthread_t *t1;
	pthread_t *t2;
	int arg1 = 1;
	int arg2 = 2;
	void *p1 = (void *)&arg1;
	void *p2 = (void *)&arg2;

	if(pthread_mutex_init(&mutex, NULL) != 0)
	{
		printf("Cannot init mutex\n");
		exit(1);
	}

	if(pthread_cond_init(&ready, NULL) != 0)
	{
		printf("Cannot init cond\n");
		exit(1);
	}

	if(pthread_create(&t1, NULL, do_thread, p1) != 0)
	{
		printf("Cannot create t1\n");
		exit(1);
	}

	if(pthread_create(&t2, NULL, do_thread, p2) != 0)
	{	
		printf("Cannot create t2\n");
		exit(1);
	}

	while(1)
	{
		pthread_mutex_lock(&mutex);
		global++;
		printf("Produce: global is %d\n", global);
		pthread_cond_signal(&ready);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}

	if(pthread_join(t1, NULL) != 0)
	{
		printf("Cannot join t1\n");
		exit(1);
	}

	if(pthread_join(t2, NULL) != 0)
	{
		printf("Cannot join t2\n");
		exit(1);
	}

	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&ready);

	printf("End\n");

	exit(0);
}
