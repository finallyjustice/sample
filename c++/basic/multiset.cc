#include <iostream>
#include <set>

using namespace std;

int main(int argc, char **argv)
{
	multiset<string> ms;

	ms.insert("hello1");
	ms.insert("hello2");
	ms.insert("hello3");
	ms.insert("hello3");
	ms.insert("hello4");
	ms.insert("hello4");
	ms.insert("hello4");

	cout << "size: " << ms.size() << endl;

	cout << "hello3 (prev erase): " << ms.count("hello3") << endl;
	ms.erase("hello3");
	cout << "hello3 (post erase): " << ms.count("hello3") << endl;

	cout << "hello4 (prev erase): " << ms.count("hello4") << endl;
	ms.erase(ms.find("hello4"));
	cout << "hello4 (post erase): " << ms.count("hello4") << endl;

	multiset<string>::iterator it;
	for (it = ms.begin(); it != ms.end(); it++)
		cout << "val: " << *it << endl;

	return 0;
}
