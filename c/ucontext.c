#include <stdio.h>
#include <ucontext.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	ucontext_t context;
	int val = 1;

	getcontext(&context);
	printf("Hello World! val=%d\n", val);
	sleep(1);
	val++;
	setcontext(&context);

	return 0;
}
