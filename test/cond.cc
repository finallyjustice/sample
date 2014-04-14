#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t counter_lock;
pthread_cond_t counter_nonzero;

int counter = 0;

void * decrement_counter(void *arg)
{
	printf("counter(decrement): %d\n", counter);
	pthread_mutex_lock(&counter_lock);

	while(counter == 0)
		pthread_cond_wait(&counter_nonzero, &counter_lock);

	printf("counter--(before): %d\n", counter);
	counter--;
	printf("counter--(after): %d\n", counter);

	pthread_mutex_unlock(&counter_lock);
}

void * increment_counter(void *arg)
{
	printf("counter(increment): %d\n", counter);
	pthread_mutex_lock(&counter_lock);

	if(counter == 0)
		pthread_cond_signal(&counter_nonzero);

	printf("counter++(before): %d\n", counter);
	counter++;
	printf("counter++(after): %d\n", counter);

	pthread_mutex_unlock(&counter_lock);
}

int main(int argc, char **argv)
{
	printf("counter: %d\n", counter);

	pthread_t tid1;
	pthread_t tid2;
	int ret;

	pthread_mutex_init(&counter_lock, NULL);
	pthread_cond_init(&counter_nonzero, NULL);

	ret = pthread_create(&tid1, NULL, decrement_counter, NULL);
	if(ret)
	{
		perror("del: \n");
		return -1;
	}

	ret = pthread_create(&tid2, NULL, increment_counter, NULL);
	if(ret)
	{
		perror("inc: \n");
		return -1;
	}

	while(counter != 10)
	{
		printf("counter(main): %d\n", counter);
		sleep(1);
		counter++;
	}

	return 0;
}
