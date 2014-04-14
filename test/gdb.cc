#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>

using namespace std;

void * print_message_func(void *arg)
{
	char *msg;
	msg = (char *)arg;
	cout<<msg<<endl;
	while(1)
		sleep(1);
}

int main(int argc, char **argv)
{
	pthread_t tid1;
	pthread_t tid2;
	int iret1;
	int iret2;
	char *msg1 = "Thread 1\n";
	char *msg2 = "Thread 2\n";

	iret1 = pthread_create(&tid1, NULL, print_message_func, (void *)msg1);
	iret2 = pthread_create(&tid2, NULL, print_message_func, (void *)msg2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	cout<<"Thread 1 returns: "<<iret1<<endl;
	cout<<"Thread 2 returns: "<<iret2<<endl;

	exit(0);
}
