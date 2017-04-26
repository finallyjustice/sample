#include <iostream>
#include <deque>

using namespace std;

int main(int argc, char **argv)
{
	deque<int> dq;

	dq.push_back(1);
	dq.push_back(2);
	dq.push_back(3);

	dq.push_front(4);
	dq.push_front(5);
	dq.push_front(6);

	cout << "size: " << dq.size() << endl;
	cout << "front: " << dq.front() << endl;
	cout << "end: " << dq.back() << endl;

	dq.pop_front();
	dq.pop_back();
	
	cout << "size: " << dq.size() << endl;
	cout << "front: " << dq.front() << endl;
	cout << "end: " << dq.back() << endl;


	return 0;
}
