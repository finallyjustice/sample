#include <iostream>
#include <pthread.h>
#include <cstdlib>

using namespace std;

void* my_task(void *arg)
{
	cout<<"hello world"<<endl;
	sleep(5);
}

int main(int argc, char **argv)
{
	pthread_t tid;

	if(pthread_create(&tid, NULL, my_task, NULL) != 0)
	{
		cout<<"Failed to create task"<<endl;
		return 1;
	}

	if(pthread_join(tid, NULL) != 0)
	{
		cout<<"Cannot join thread"<<endl;
		return 1;
	}

	cout<<"Main End"<<endl;

	return 0;
}
