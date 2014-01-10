#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

// 1-left 2-up 3-corner

int **t1;
int **t2;

int value[3];

void lcs(char *s1, char *s2, int l1, int l2)
{
	int i, j;
	int k;
	for(i=1; i<l2+1; i++)
	{
		for(j=1; j<l1+1; j++)
		{
			value[0] = t1[i][j-1];
			value[1] = t1[i-1][j];
			value[2] = 0;
			if(s1[j-1] == s2[i-1])
			{
				value[2] = t1[i-1][j-1]+1;
			}
			
			int max = 0;
			for(k=0; k<3; k++)
			{
				if(value[k] >= value[max])
				{
					max = k;
				}
			}
			
			t1[i][j] = value[max];
			t2[i][j] = max + 1;
		}
	}
}

void print_table(int l1, int l2)
{
	int i, j;
	printf("Table 1:\n");
	for(i=0; i<l2+1; i++)
	{
		for(j=0; j<l1+1; j++)
		{
			printf("%d ", t1[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	printf("Table 2:\n");
	for(i=0; i<l2+1; i++)
	{
		for(j=0; j<l1+1; j++)
		{
			printf("%d ", t2[i][j]);
		}
		printf("\n");
	}
}

void print_lcs(int i, int j, char *s1, char *s2)
{
	if(t2[i][j] == 0)
		return;
	if(t2[i][j] == 3)
	{
		print_lcs(i-1, j-1, s1, s2);
		printf("%c\n", s2[i-1]);
	}
	if(t2[i][j] == 1)
		print_lcs(i, j-1, s1, s2);
	if(t2[i][j] == 2)
		print_lcs(i-1, j, s1, s2);
}

int main(int argc, char **argv)
{
	char s1[] = {'a', 'b', 'c', 'f', 'g', 'i', 'j', 'k'};
	char s2[] = {'b', 'c', 'd', 'e', 'f', 'h', 'i'};
	int l1 = 8;
	int l2 = 7;

	t1 = (int **)malloc(sizeof(int *)*(l2+1));
	t2 = (int **)malloc(sizeof(int *)*(l2+1));

	int i, j;
	for(i=0; i<l2+1; i++)
	{
		t1[i] = (int *)malloc(sizeof(int)*(l1+1));
		t2[i] = (int *)malloc(sizeof(int)*(l1+1));
	}

	for(i=0; i<l2+1; i++)
	{
		for(j=0; j<l1+1; j++)
		{
			t1[i][j] = 0;
			t2[i][j] = 0;
		}
	}

	lcs(s1, s2, l1, l2);
	print_table(l1, l2);

	printf("\nLCS:\n");
	print_lcs(l2, l1, s1, s2);

	for(i=0; i<l2+1; i++)
	{
		free(t1[i]);
		free(t2[i]);
	}
	free(t1);
	free(t2);
}

