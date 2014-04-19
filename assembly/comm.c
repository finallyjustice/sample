#include <stdio.h>

int main(int argc, char **argv)
{
	int value = 3;
	int result = 100;

	__asm__("mov %1, %%eax;"
			"add $1, %%eax;"
			"mov %%eax, %0;"
			: "=r"(result)
			: "r"(value)
			: "%eax"
			);

	printf("Result: %d\n", result);
}
