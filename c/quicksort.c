#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int partition(int *data, int p, int r)
{
	int pivot = data[r];
	int i = p-1;
	int j;
	int tmp;

	for(j=p; j<r; j++)
	{
		if(data[j] <= pivot)
		{
			i++;
			tmp = data[i];
			data[i] = data[j];
			data[j] = tmp;
		}
	}

	tmp = data[i+1];
	data[i+1] = data[r];
	data[r] = tmp;

	return i+1;
}

void quick_sort(int *data, int p, int r)
{
	if(p >= r) return;
	int q = partition(data, p, r);
	quick_sort(data, p, q-1);
	quick_sort(data, q+1, r);
}

int main(int argc, char **argv)
{
	int data[] = {5, 4, 6, 3, 7, 7, 9, 0, 10, 1, 8};
	int i;

	quick_sort(data, 0, 10);

	for(i=0; i<11; i++)
	{
		printf("value: %d\n", data[i]);
	}
}
