#include <iostream>
#include <list>

using namespace std;

list< list<int> > permutation(list<int> input)
{
	// final result
	list< list<int> > ret;

	// base case - return if size is 1
	if(input.size() == 1)
	{
		ret.push_back(input);
		return ret;
	}

	// for each head element - recursively
	list<int>::iterator itf;
	for(itf=input.begin(); itf!=input.end(); itf++)
	{
		int v = *itf;
		list<int> ninput;
		for(list<int>::iterator itn=input.begin(); itn!=input.end(); itn++)
		{
			if(itn != itf)
				ninput.push_back(*itn);
		}

		// result of recursive function call
		list< list<int> > ret1 = permutation(ninput);
		list< list<int> >::iterator itr;
		for(itr=ret1.begin(); itr!=ret1.end(); itr++)
		{
			itr->push_front(v);
			ret.push_back(*itr);
		}
	}

	return ret;
}

int main(int argc, char **argv)
{
	list<int> input;
	input.push_back(1);
	input.push_back(2);
	input.push_back(3);
	input.push_back(4);
	input.push_back(5);
	input.push_back(6);
	input.push_back(7);

	list< list<int> > ret = permutation(input);

	list< list<int> >::iterator it;
	int c;
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
