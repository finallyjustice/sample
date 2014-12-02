// all subset of a set

#include <iostream>
#include <list>

using namespace std;

list< list<int> > subset(int *a, int p, int n)
{
	if(p == n)
	{
		list< list<int> > ll;
		list<int> l;
		ll.push_back(l);
		return ll;
	}

	list< list<int> > nl;
	list< list<int> > ll = subset(a, p+1, n);
	list< list<int> >::iterator it;
	for(it=ll.begin(); it!=ll.end(); it++)
	{
		list<int> tmp = *it;
		tmp.push_back(a[p]);
		nl.push_back(*it);
		nl.push_back(tmp);
	}
	return nl;
}

int main(int argc, char **argv)
{
	int a[] = {1, 2, 3, 4};
	int n = sizeof(a)/sizeof(int);

	list< list<int> > ll = subset(a, 0, n);

	list< list<int> >::iterator it1;
	int tot = 0;
	for(it1=ll.begin(); it1!=ll.end(); it1++)
	{
		list<int>::iterator it2;
		for(it2=it1->begin(); it2!=it1->end(); it2++)
			cout<<*it2<<" ";
		cout<<endl;
		tot++;
	}

	cout<<"Total: "<<tot<<endl;

	return 0;
}
