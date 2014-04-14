#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>

using namespace std;

void * thread_func1(void *arg)
{
	while(1)
	{
		cout<<"This is thread 1"<<endl;
		sleep(1);
	}
	return 0;
}

void * thread_func2(void *arg)
{
	while(1)
	{
		cout<<"This is thread 2"<<endl;
		sleep(1);
	}
	return 0;
}

int main(int argc, char **argv)
{
	pthread_t tid1;
	pthread_t tid2;

	if(pthread_create(&tid1, NULL, thread_func1, NULL) != 0)
	{
		cout<<"Failed to create thread 1"<<endl;
		return -1;
	}

	if(pthread_join(tid1, NULL) != 0)
	{
		cout<<"Failed to join thread 1"<<endl;
		return -1;
	}

	if(pthread_create(&tid2, NULL, thread_func2, NULL) != 0)
	{
		cout<<"Failed to create thread 2"<<endl;
		return -1;
	}

	if(pthread_join(tid2, NULL) != 0)
	{
		cout<<"Failed to join thread 2"<<endl;
		return -1;
	}

	return 0;
}
