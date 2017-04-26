#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int arhc, char **argv)
{
	fstream f;
	f.open("data.txt", fstream::in | fstream::out);

	if (!f.is_open()) {
		cout << "open error" << endl;
		return -1;
	}
	f << "hello" << endl;
	f.close();

	f.open("data.txt", fstream::in | fstream::out);
	string s;

	f >> s;

	cout << s << endl;

	f.close();

	return 0;
}
