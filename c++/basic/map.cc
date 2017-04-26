// implemented with rbtree

#include <iostream>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
	// each element is unique
	map<string, int> m;

	m.insert(pair<string, int>("hello1", 1));
	m.insert(pair<string, int>("hello2", 2));
	m.insert(pair<string, int>("hello3", 3));
	m.insert(pair<string, int>("hello3", 4));

	m["hello4"] = 4;

	cout << "size: " << m.size() << endl;

	// this is equivalent to insert hello5
	if (m["hello5"] == 0)
		cout << "hello5 does not exist" << endl;
	else
		cout << "hello5 does exist" << endl;

	if (m.find("hello3") != m.end())
		cout << "hello3 does exist" << endl;
	else
		cout << "hello3 does not exist" << endl;

	cout << "hello3 count: " << m.count("hello3") << endl;

	m.erase("hello3");
	
	if (m.find("hello3") != m.end())
		cout << "hello3 does exist" << endl;
	else
		cout << "hello3 does not exist" << endl;

	map<string, int>::iterator it;
	for (it = m.begin(); it != m.end(); it++)
		cout << "val: " << it->first << ", " << it->second << endl;

	return 0;
}
