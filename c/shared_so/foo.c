/*
 * gcc -c -Wall -Werror -fpic foo.c
 * gcc -shared -o libfoo.so foo.o
 */

#include <stdio.h>

void foo(int a, int b)
{
	printf("Hello, foo of %d and %d is %d\n",
			a, b, a + b);
}
