#include <iostream>
#include <stack>

using namespace std;

int main(int argc, char **argv)
{
	stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);

	cout <<  "size: " << s.size() << endl;

	while (!s.empty()) {
		cout << "val: " << s.top() << endl;
		s.pop();
	}

	return 0;
}
