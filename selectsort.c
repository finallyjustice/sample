#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void select_sort(int *data, int n)
{
    int i, j;
    int tmp;

    for(i=1; i<n; i++)
    {
		j = i;
        while(data[j]<data[j-1] && j>=1)
        {
            tmp = data[j];
            data[j] = data[j-1];
            data[j-1] = tmp;
			j--;
        }
    }
}

int main(int argc, char **argv)
{
    int a[] = {5, 4, 6, 3, 2, 7, 1, 8, 9, 10, 0};
    int i;

    select_sort(a, 11);
    for(i=0; i<11; i++)
    {
        printf("value: %d\n", a[i]);
    }
}
