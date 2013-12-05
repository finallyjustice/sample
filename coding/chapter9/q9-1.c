#include <stdio.h>
#include <string.h>

int compute_step(int n)
{
	if(n == 0) return 1;
	if(n == 1) return 1;
	if(n == 2) return 2;

	int r1 = compute_step(n-1);
	int r2 = compute_step(n-2);
	int r3 = compute_step(n-3);

	return r1+r2+r3;
}

int main(int argc, char **argv)
{
	int n = 4;
	printf("NUM: %d\n", compute_step(n));
	return 0;
}
