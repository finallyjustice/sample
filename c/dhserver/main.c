#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "tpool.h"

void *func(void *arg)
{
	int id = (int)arg;
	printf("Thread %d\n", id);
	sleep(2);
}

int main(int argc, char **argv)
{
	if(tpool_create(5) != 1)
	{
		printf("failed\n");
		return 1;
	}

	sleep(3);

	int i;
	for(i=0; i<10; i++)
	{
		tpool_add_job(func, (void*)i);
		//sleep(1);
	}
	sleep(10);
	printf("Hello World\n");
}
