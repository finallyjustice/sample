#include <stdio.h>
#include <string.h>

int str2max(int *data, int start)
{
	if(data[start]*10+data[start+1] > 26)
		return 1;
	else
		return 2;
}

int num_translate_recu(int *data, int start, int end)
{
	if(start == end) 
		return 1;
	if(start == end-1)
		return str2max(data, start);

	int ret1 = num_translate_recu(data, start+1, end) + 1;
	int ret2 = num_translate_recu(data, start+2, end) + str2max(data, start);

	return ret1>=ret2?ret1:ret2;
}

int num_translate_iter(int *data, int size)
{
	int buf[size];
	memset(buf, 0, size);

	buf[size-1] = 1;
	buf[size-2] = str2max(data, size-2);

	printf("%d, %d\n", buf[size-1], buf[size-2]);

	return 0;
}

int main(int argc, char **argv)
{
	int data[] = {'1', '2', '2', '1'};	
	int end = 3;
	printf("MAX: %d\n", num_translate_iter(data, 4));
}
