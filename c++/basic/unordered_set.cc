// implemented with hash
// g++ unordered_set.cc -o unordered_set -std=gnu++11

#include <iostream>
#include <unordered_set>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	unordered_set<string> us;

	us.insert("hello1");
	us.insert("hello2");
	us.insert("hello3");
	us.insert("hello3");
	us.insert("hello3");
	us.insert("hello4");
	us.insert("hello4");
	us.insert("hello5");

	cout << "hello3 :" << us.count("hello3") << endl;
	us.erase("hello3");
	cout << "hello3 :" << us.count("hello3") << endl;

	if (us.find("hello5") != us.end())
		cout << "hello5 does exist" << endl;
	else
		cout << "hello5 does not exist" << endl;

	unordered_set<string>::iterator it;
	for (it = us.begin(); it != us.end(); it++)
		cout << "val: " << *it << endl;

	return 0;
}
