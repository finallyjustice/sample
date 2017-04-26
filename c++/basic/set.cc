// implemented with rbtree

#include <iostream>
#include <set>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	// uniqueue element
	set<string> s;

	s.insert("hello1");
	s.insert("hello2");
	s.insert("hello3");
	s.insert("hello4");
	s.insert("hello3");

	cout << "hello3: " << s.count("hello3") << endl;

	s.erase("hello3");

	if (s.find("hello3") != s.end())
		cout << "hello3 found" << endl;
	else
		cout << "hello3 not found" << endl;

	set<string>::iterator it = s.begin();
	for (it = s.begin(); it != s.end(); it++)
		cout << "val: " << *it << endl;

	return 0;
}
