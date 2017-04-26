#include <iostream>
#include <queue>

using namespace std;

int main(int argc, char **argv)
{
	priority_queue<int> pq;

	pq.push(1);
	pq.push(3);
	pq.push(5);
	pq.push(7);
	pq.push(2);
	pq.push(8);
	pq.push(6);
	pq.push(4);

	cout << "size: " << pq.size() << endl;
	cout << "top: " << pq.top() << endl;

	while (!pq.empty()) {
		cout << "val: " << pq.top() << endl;
		pq.pop();
	}

	return 0;
}
