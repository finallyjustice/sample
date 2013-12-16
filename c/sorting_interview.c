#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert_sort(int *a, int n)
{
	int i;
	for(i=1; i<n; i++)
	{
		int j = i;
		while(j>0 && a[j-1]>a[j])
		{
			int tmp = a[j-1];
			a[j-1] = a[j];
			a[j] = tmp;
			j--;
		}
	}
}

void merge(int *a, int *b, int p, int r, int q)
{
	int s1 = p;
	int e1 = r;
	int s2 = r+1;
	int e2 = q;
	int c = p;

	while(s1<=e1 && s2<=e2)
	{
		if(a[s1] <= a[s2])
		{
			b[c] = a[s1];
			s1++;
		}
		else
		{
			b[c] = a[s2];
			s2++;
		}
		c++;
	}

	while(s1 <= e1)
	{
		b[c] = a[s1];
		c++;
		s1++;
	}

	while(s2 <= e2)
	{
		b[c] = a[s2];
		c++;
		s2++;
	}

	for(c=p; c<=q; c++)
		a[c] = b[c];
}

void merge_sort_recv(int *a, int *b, int p, int q)
{
	if(p >= q) return;
	int r = (q-p)/2 + p;
	merge_sort_recv(a, b, p, r);
	merge_sort_recv(a, b, r+1, q);
	merge(a, b, p, r, q);
}

void merge_sort(int *a, int n)
{
	int p = 0;
	int q = n-1;
	int *b = (int *)malloc(sizeof(int)*n);
	merge_sort_recv(a, b, p, q);
	free(b);
}

int partition(int *a, int p, int q)
{
	int pv = q;
	int pivot = a[q];

	int i = p-1;
	int j = p;

	while(j < q)
	{
		if(a[j] <= pivot)
		{
			// swap a[j] and a[i+1]
			int tmp = a[j];
			a[j] = a[i+1];
			a[i+1] = tmp;
			i++;
		}
		
		j++;
	}

	int tmp = a[q];
	a[q] = a[i+1];
	a[i+1] = tmp;

	return i;
}

void quick_sort(int *a, int p, int q)
{
	if(p >= q) return;
	int r = partition(a, p, q);
	quick_sort(a, p, r);
	quick_sort(a, r+1, q);
}

int main(int argc, char **argv)
{
	int a[] = {1, 3, 7, 9, 2, 4, 6, 0, 5};
	int n = 9;
	int c;

	quick_sort(a, 0, n-1);
	for(c=0; c<n; c++)
		printf("Val: %d\n", a[c]);
}
