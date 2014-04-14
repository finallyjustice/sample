#include <iostream>
#include <cstdio>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

sem_t sem1;
sem_t sem2;

void * thread_func_a(void *arg)
{
	sem_wait(&sem1);
	cout<<"This is thread a"<<endl;
}

void * thread_func_b(void *arg)
{
	sem_wait(&sem2);
	cout<<"This is thread b"<<endl;
	sem_post(&sem1);
}

void * thread_func_c(void *arg)
{
	cout<<"This is thread c"<<endl;
	sem_post(&sem2);
}

int main(int argc, char **argv)
{
	pthread_t tid1;
	pthread_t tid2;
	pthread_t tid3;

	sem_init(&sem1, 0, 0);
	sem_init(&sem2, 0, 0);

	pthread_create(&tid1, NULL, thread_func_a, NULL);
	pthread_create(&tid2, NULL, thread_func_b, NULL);
	pthread_create(&tid3, NULL, thread_func_c, NULL);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);

	sem_destroy(&sem1);
	sem_destroy(&sem2);

	cout<<"Main thread is over"<<endl;

	return 0;
}

