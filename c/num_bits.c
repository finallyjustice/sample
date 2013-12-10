#include <stdio.h>

int linear_num_bits(int num)
{
	int base = 1;
	int last = 1;
	int ret;
	while(1)
	{
		ret = num / base;
		if(ret != 0)
		{
			last++;
			base *= 10;
		}
		else
		{
			return last-1;
		}
	}
}

int main(int argc, char **argv)
{
	int num = 953080080;
	printf("Linear: %d\n", linear_num_bits(num));
}
