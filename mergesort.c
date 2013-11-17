#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void merge(int *data, int s, int m, int e)
{
    int size = e-s+1;
    int tmp[size];
    int i = s;
    int j = m+1;
    int c = 0;

    while(i<=m && j<=e)
    {
        if(data[i] <= data[j])
        {
            tmp[c] = data[i];
            i++;
        }
        else
        {
            tmp[c] = data[j];
            j++;
        }
        c++;
    }
    
    if(i <= m)
    {
        while(i <= m)
        {
            tmp[c] = data[i];
            i++;
            c++;
        }
    }
    
    if(j <= e)
    {
        while(j <= e)
        {
            tmp[c] = data[j];
            j++;
            c++;
        }
    }

    for(c=0; c<size; c++)
    {
        data[s+c] = tmp[c];
    }
}

void merge_sort(int *data, int s, int e)
{
    int m = (e-s)/2 + s;
    if(s == e)
	{
        return;
	}
        
    merge_sort(data, s, m);
    merge_sort(data, m+1, e);
    merge(data, s, m, e);
}

int main(int argc, char **argv)
{
    int data[] = {5, 4, 6, 3, 7, 2, 1, 8, 9, 10};
    int size = 10;
    int i;

    merge_sort(data, 0, 10);
    for(i=0; i<size; i++)
    {
        printf("Value: %d\n", data[i]);
    }
}
