#include <iostream>
#include <cstdio>
#include <stack>
#include <cstdlib>
#include <string.h>

class Heap
{
protected:
	int *val;
	int size;
	int cap;

protected:
	int parent(int i) 
	{
		return (i-1)/2;
	}
	int left(int i) 
	{
		return i*2+1;
	}
	int right(int i) 
	{
		return i*2+2;
	}

public:
	Heap(int *val, int n) 
	{
		size = 0;
		cap = n;
		this->val = (int *)malloc(sizeof(int)*cap);
		memcpy(this->val, val, sizeof(int)*cap);
	}
	void build_heap() 
	{
		size = cap;
		for(int i=size/2-1; i>=0; i--)
			heapify(i);
	}
	void dump_heap() 
	{
		printf("Heap: ");
		for(int i=0; i<size; i++)
			printf("%d ", val[i]);
		printf("\n");
	}
	virtual void heapify(int i) = 0;
	virtual void sort() = 0;
};

class MinHeap : public Heap
{
public:
	MinHeap(int *val, int n) : Heap(val, n)
	{
	}
	virtual void heapify(int i) 
	{
		int min = i;
		int li = left(i);
		int ri = right(i);
		if(li<size && val[li]<val[i])
			min = li;
		if(ri<size && val[ri]<val[min])
			min = ri;
		if(min != i) {
			int tmp = val[min];
			val[min] = val[i];
			val[i] = tmp;
			return heapify(min);
		}
		return;
	}

	void sort()
	{
		int num = size;
		for(int i=size-1; i>0; i--) {
			int tmp = val[0];
			val[0] = val[i];
			val[i] = tmp;
			size--;
			heapify(0);
		}
		size = num;
	}
};

class MaxHeap : public Heap
{
public:
	MaxHeap(int *val, int n) : Heap(val, n)
	{
	}
	virtual void heapify(int i) 
	{
		int max = i;
		int li = left(i);
		int ri = right(i);
		if(li<size && val[li]>val[i])
			max = li;
		if(ri<size && val[ri]>val[max])
			max = ri;
		if(max != i) {
			int tmp = val[max];
			val[max] = val[i];
			val[i] = tmp;
			return heapify(max);
		}
		return;
	}

	void sort()
	{
		int num = size;
		for(int i=size-1; i>0; i--) {
			int tmp = val[0];
			val[0] = val[i];
			val[i] = tmp;
			size--;
			heapify(0);
		}
		size = num;
	}
};

int main(int argc, char **argv)
{
	int a[] = {2, 6, 5, 1, 9, 4, 8, 7, 3};
	int n = 9;
	printf("MinHeap\n");
	MinHeap minh(a, n);
	minh.build_heap();
	minh.dump_heap();
	minh.sort();
	minh.dump_heap();
	printf("Maxheap\n");
	MaxHeap maxh(a, n);
	maxh.build_heap();
	maxh.dump_heap();
	maxh.sort();
	maxh.dump_heap();
	return 0;
}
