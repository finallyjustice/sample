#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t sem_milk;
pthread_mutex_t mutex;

int milks = 0; 

void * produce(void *arg)
{
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("Producer Before: %d\n", milks);
		milks++;
		printf("Producer After : %d\n", milks);
		sem_post(&sem_milk);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void * consume(void *arg)
{
	while(1)
	{
		sem_wait(&sem_milk);
		pthread_mutex_lock(&mutex);
		printf("Consumer Before: %d\n", milks);
		milks--;
		printf("Consumer After : %d\n", milks);
		pthread_mutex_unlock(&mutex);
		sleep(8);
	}
}

int main(int argc, char **argv)
{
	pthread_t ptid;
	pthread_t ctid;

	pthread_mutex_init(&mutex, 0);
	sem_init(&sem_milk, 0, 0);

	pthread_create(&ptid, NULL, produce, NULL);
	pthread_create(&ctid, NULL, consume, NULL);

	pthread_join(ptid, NULL);
	pthread_join(ctid, NULL);

	sem_destroy(&sem_milk);
	pthread_mutex_destroy(&mutex);

	return 0;
}
