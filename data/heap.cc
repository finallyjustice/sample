#include <iostream>
#include <cstdlib>

using namespace std;

template <typename T>
class MaxHeap 
{
private:
	T *data;
	int size;
	int capacity;

private:
	int parent(int i);
	int left(int i);
	int right(int i);
	void max_heapify(int i);

public:
	MaxHeap(int cap);
	void build_max_heap(T *a, int n);
	void insert(T val);
	T pop();
	void print();
	void print_layer();
	void heapsort(T *a, int n);
};

template <typename T>
int MaxHeap<T>::parent(int i)
{
	return (i+1)/2-1;
}

template <typename T>
int MaxHeap<T>::left(int i)
{
	return i*2+1;
}

template <typename T>
int MaxHeap<T>::right(int i)
{
	return i*2+2;
}

template <typename T>
void MaxHeap<T>::max_heapify(int i)
{
	if(size == 0)
		return;

	int largest;
	int lc = left(i);
	int rc = right(i);

	if(lc<size && data[i]<data[lc])
		largest = lc;
	else
		largest = i;

	if(rc<size && data[largest]<data[rc])
		largest = rc;

	if(largest != i)
	{
		int tmp = data[largest];
		data[largest] = data[i];
		data[i] = tmp;
		max_heapify(largest);
	}
}

template <typename T>
MaxHeap<T>::MaxHeap(int cap)
{
	size = 0;
	capacity = cap;

	data = (T *)malloc(sizeof(T)*capacity);
}

template <typename T>
void MaxHeap<T>::build_max_heap(T *a, int n)
{
	if(n > capacity)
		return;
	for(int i=0; i<n; i++)
		data[i] = a[i];
	size = n;

	for(int i=n/2-1; i>=0; i--)
		max_heapify(i);

}

template <typename T>
void MaxHeap<T>::insert(T val)
{
	if(size >= capacity)
	{
		cout<<"Cannot insert the new value"<<endl;
		return;
	}

	int pos = size;
	data[pos] = val;

	while(pos>0 && data[pos]>data[parent(pos)])
	{
		int tmp = data[pos];
		data[pos] = data[parent(pos)];
		data[parent(pos)] = tmp;
		pos = parent(pos);
	}

	size++;
}

template <typename T>
T MaxHeap<T>::pop()
{
	T ret = data[0];
	data[0] = data[size-1];
	size--;

	max_heapify(0);

	return ret;
}

template <typename T>
void MaxHeap<T>::print()
{
	for(int i=0; i<size; i++)
		cout<<data[i]<<" ";
	cout<<endl;
}

template <typename T>
void MaxHeap<T>::print_layer()
{
	int c = 0;
	int tot = 1;

	while(c < size)
	{
		for(int i=c; i<c+tot; i++)
		{
			if(i >= size)
				break;
			cout<<data[i]<<" ";
		}
		cout<<endl;

		c = c+tot;
		tot = tot*2; 
	}
}

template <typename T>
void MaxHeap<T>::heapsort(T *a, int n)
{
	build_max_heap(a, n);
	for(int i=size-1; i>0; i--)
	{
		T tmp = data[0];
		data[0] = data[i];
		data[i] = tmp;
		size--;
		max_heapify(0);
	}

	size = n;
}

int main(int argc, char **argv)
{
	MaxHeap<int> mh(100);
	/*mh.insert(16);
	mh.insert(14);
	mh.insert(10);
	mh.insert(8);
	mh.insert(7);
	mh.insert(9);
	mh.insert(3);
	mh.insert(2);
	
	mh.print();
	mh.print_layer();

	cout<<"# "<<mh.pop()<<endl;
	cout<<"# "<<mh.pop()<<endl;*/

	int a[] = {5, 6, 3, 4, 1, 9, 7, 8, 2, 11};
	mh.heapsort(a, 10);
	mh.print();

	return 0;
}
