#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	// vector<int> v(2); === v.push_back(0) and v.push_back(0)
	vector<int> v;
	v.push_back(1);
	v.push_back(2);
	v.push_back(3);
	v.push_back(4);

	int len = v.size();

	for (int i = 0; i < 4; i++) {
		cout << "val: " << v[i] << endl;
	}

	cout << "size: " << v.size() << endl;
	cout << "max_size: " << v.max_size() << endl;
	cout << "capacity: " << v.capacity() << endl;

	vector<int>::iterator it;

	for (it = v.begin(); it != v.end(); it++)
		cout << "it: " << *it << endl;

	return 0;
}
