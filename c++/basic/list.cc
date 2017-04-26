#include <iostream>
#include <list>

using namespace std;

int main(int argc, char **argv)
{
	list<int> l;
	list<int>::iterator it = l.begin();

	l.push_back(1);
	l.push_back(2);
	l.push_back(3);
	l.push_back(4);
	l.push_back(5);

	while (*it != 3)
		it++;

	l.insert(it, 6);
	
	while (*it != 4)
		it++;
	
	l.erase(it);
	l.remove(2);

	it = l.begin();

	for (it; it != l.end(); it++)
		cout << "val: " << *it <<endl;

	return 0;
}
