#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char **argv)
{
	queue<int> q;

	q.push(1);
	q.push(2);
	q.push(3);
	q.push(4);

	cout << "size: " << q.size() << endl;
	cout << "back: " << q.back() << endl;

	while (!q.empty()) {
		cout << "val: " << q.front() << endl;
		q.pop();
	}

	return 0;
}
