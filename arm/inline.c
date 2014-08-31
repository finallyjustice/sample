// arm-linux-gnueabi-gcc inline.c -o inline -static
// qemu-arm inline
// Expected Result:
//    Hello World
//    value 1: 10
//    value 2: 11

#include <stdio.h>

int main(int argc, char **argv)
{
	printf("Hello World\n");

	int value = 10;
	printf("value 1: %d\n", value);
	
	__asm__ volatile(
		"mov r1, %0\n\t"
		:
		: "r"(value)
		: "r1"
	);

	__asm__ volatile(
		"add r2, r1, #1\n\t"
		"mov %0, r2\n\t"
		: "=r"(value)
		: 
		: "r2"
	);

	printf("value 2: %d\n", value);
	
	return 0;
}
