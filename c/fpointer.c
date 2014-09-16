#include <stdio.h>

int init1(void)
{
	printf("init1\n");
	return 0;
}

int init2(void)
{
	printf("init2\n");
	return 0;
}

int init3(void)
{
	printf("init3\n");
	return 1;
}

int init4(void)
{
	printf("init4\n");
	return 0;
}

int main(int argc, char **argv)
{
	unsigned long funcv[] = 
	{
		(unsigned long)init1,
		(unsigned long)init2,
		(unsigned long)init3,
		(unsigned long)init4
	};

	int (*p)(void);
	int i;

	for(i=0; i<4; i++)
	{
		p = funcv[i];
		if(p() == 1)
		{
			printf("Error with %d\n", i);
			return -1;
		}
	}

	return 0;
}
