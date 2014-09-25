#include <iostream>
#include <list>

using namespace std;

list< list<int> > subset(int a[], int idx, int n)
{
	list< list<int> > ret;

	if(idx == n)
	{
		list<int> tmp;
		ret.push_back(tmp);
		return ret;
	}

	list< list<int> > ll;
	ll = subset(a, idx+1, n);

	list< list<int> >::iterator itll;
	for(itll=ll.begin(); itll!=ll.end(); itll++)
		ret.push_back(*itll);	
	
	for(itll=ll.begin(); itll!=ll.end(); itll++)
	{
		itll->push_front(a[idx]);
		ret.push_back(*itll);	
	}

	return ret;
}

int main(int argc, char **argv)
{
	int a[] = {0, 1, 2, 3, 4, 5};
	int idx = 0;
	int n   = 6;

	list< list<int> > ret = subset(a, idx, n);

	list< list<int> >::iterator it;
	int c = 0;
	for(it=ret.begin(); it!=ret.end(); it++)
	{
		list<int>::iterator it1;
		for(it1=it->begin(); it1!=it->end(); it1++)
			cout<<*it1<<" ";
		cout<<endl;
		c++;
	}

	cout<<"Total: "<<c<<endl;

	return 0;
}
