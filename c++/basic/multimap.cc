#include <iostream>
#include <map>

using namespace std;

int main(int argc, char **argv)
{
	multimap<string, int> mm;

	mm.insert(pair<string, int>("hello1", 1));
	mm.insert(pair<string, int>("hello2", 2));
	mm.insert(pair<string, int>("hello3", 3));
	mm.insert(pair<string, int>("hello3", 4));
	mm.insert(pair<string, int>("hello3", 5));
	mm.insert(pair<string, int>("hello4", 4));
	mm.insert(pair<string, int>("hello5", 500));
	mm.insert(pair<string, int>("hello5", 501));
	mm.insert(pair<string, int>("hello5", 502));
	mm.insert(pair<string, int>("hello6", 6));
	
	// multiset does not support []
	//mm["hello3"] = 3;
	
	cout << "hello3 count: " << mm.count("hello3") << endl;
	mm.erase("hello3");
	cout << "hello3 count: " << mm.count("hello3") << endl;

	if (mm.find("hello7") != mm.end())
		cout << "hello7 does exist" << endl;
	else
		cout << "hello7 does not exist" << endl;

	multimap<string, int>::iterator it;
	for (it = mm.begin(); it != mm.end(); it++)
		cout << "val: " << it->first << ", " << it->second << endl;

	pair<multimap<string, int>::iterator, multimap<string, int>::iterator> ret;
	ret = mm.equal_range("hello5");
	
	for (it = ret.first; it != ret.second; it++)
		cout << "search for " << it->first << ": " << it->second << endl;

	return 0;
}
