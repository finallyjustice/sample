#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define random(x) (rand()%x)

int partition(int *data, int p, int r)
{
    int tmp;
	int myrand;
back:
	myrand = random(r-p);
	if(myrand < 0) goto back;
	int pivot_index = myrand+p;
	tmp = data[pivot_index];
	data[pivot_index] = data[r];
	data[r] = tmp;

    int pivot = data[r];

    int i = p-1;
    int j;
    
    for(j=p; j<r; j++)
    {
        if(data[j] <= data[r])
        {
            i++;
            //swap data[j] with data[i]
            tmp = data[j];
            data[j] = data[i];
            data[i] = tmp;
        }
    }
    //swap data[i+1] with data[r]
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
    int data[] = {5, 4, 6, 3, 7, 8, 1, 2, 0, 10, 9};
    int size = 11;
    int i;
    
    quick_sort(data, 0, size-1);
    
    for(i=0; i<size; i++)
    {
        printf("Value: %d\n", data[i]);
    }
}
