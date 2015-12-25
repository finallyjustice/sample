#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned int words[4];
    unsigned int func = 1;
    unsigned int ecx = 0;
    volatile int i;
 
	if (argc > 1)
		func = strtol(argv[1], NULL, 0);
    
    asm("cpuid"
        : "=a" (words[0]),
        "=b" (words[1]),
        "=c" (words[2]),
        "=d" (words[3])
        : "a" (func),
        "c" (ecx));
	
	printf("CPUID 0x%08x: eax = 0x%08x ebx = 0x%08x ecx = 0x%08x edx = 0x%08x\n",
			func, words[0], words[1], words[2], words[3]);
}
