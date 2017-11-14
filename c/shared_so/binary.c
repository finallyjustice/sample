/*
 * gcc -Wall -o binary binary.c -lfoo -L.
 * LD_LIBRARY_PATH=. ./binary
 * LD_LIBRARY_PATH=. gdb ./binary
 */

#include <stdio.h>

extern void foo(int a, int b);

int main(int argc, char **argv)
{
	printf("Test SO\n");
	foo(3, 4);
	return 0;
}
