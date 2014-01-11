#include <stdio.h>
#include <stdlib.h>

int *len;
int *idx;

void lis(int *s, int l)
{
	int i, j;
	for(i=0; i<l; i++)
	{
		len[i] = 1;
		idx[i] = i;
	}

	for(i=0; i<l; i++)
	{
		int max = 1;
		for(j=0; j<i; j++)
		{
			if(s[i] > s[j])	
			{
				if(max < len[j]+1)
				{
					max = len[j]+1;
					idx[i] = j;
				}
			}
		}
		len[i] = max; 
	}

	for(i=0; i<l; i++)
		printf("%d ", len[i]);
	printf("\n");
	for(i=0; i<l; i++)
		printf("%d ", idx[i]);
	printf("\n");
}

void print_lis(int *s, int i)
{
	if(i == 0)
	{
		printf("%d ", s[i]);
		return;
	}
	else
	{
		print_lis(s, idx[i]);
		printf("%d ", s[i]);
	}
}

int main(int argc, char **argv)
{
	int s[] = {1, 10, 4, 3, 5, 7, 8, 2};
	int l = 8;
	len = (int *)malloc(sizeof(int)*l);
	idx = (int *)malloc(sizeof(int)*l);
	lis(s, l);

	int i;
	int mi = 0;
	for(i=0; i<l; i++)
	{
		if(len[i] > len[mi])
			mi = i;
	}
	print_lis(s, mi);
	printf("\n");

	return 1;
}
