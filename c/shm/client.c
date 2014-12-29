#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define BUF_SIZE 1024
#define MYKEY 115

int main(int argc, char **argv)
{
	int shmid;
	char *shmptr;

	if(shmid=shmget(MYKEY, BUF_SIZE, IPC_CREAT) == -1)
	{
		printf("shmget error\n");
		return 1;
	}

	if((shmptr=shmat(shmid, 0, 0)) == (void*)-1)
	{
		printf("shmat error\n");
		return 1;
	}

	while(1)
	{
		printf("string: %s\n", shmptr);
		sleep(3);
	}

	return 0;
}
