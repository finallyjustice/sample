// implemented with hash
// g++ unordered_map.cc -o unordered_map -std=gnu++11

#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	unordered_map<string, int> um;

	um.insert(pair<string, int>("hello1", 1));
	um.insert(pair<string, int>("hello2", 2));
	um.insert(pair<string, int>("hello3", 301));
	um.insert(pair<string, int>("hello3", 302));
	um.insert(pair<string, int>("hello3", 303));
	um.insert(pair<string, int>("hello4", 401));
	um.insert(pair<string, int>("hello4", 402));
	um.insert(pair<string, int>("hello4", 403));
	um["hello5"] = 1;

	if (um.find("hello6") != um.end())
		cout << "hello6 does exist" << endl;
	else
		cout << "hello6 does not exist" << endl;

	cout << "hello4 is " << um["hello4"] << endl;

	cout << "hello3 count: " << um.count("hello3") << endl;
	um.erase("hello3");
	cout << "hello3 count: " << um.count("hello3") << endl;

	unordered_map<string, int>::iterator it;
	for (it = um.begin(); it != um.end(); it++)
		cout << "val " << it->first << ", " << it->second << endl;

	return 0;
}
