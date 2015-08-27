#include <stdio.h>

void __attribute__ ((constructor)) test1(void)
{
	printf("This is the constructor function 1\n");
}

void __attribute__ ((constructor)) test2(void)
{
	printf("This is the constructor function 2\n");
}

int main(int argc, char **argv)
{
	printf("Hello World!\n");
	return 1;
}
