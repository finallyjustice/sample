#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	string s = "hello";
	int len = s.size();

	s[1] = 'a';

	for (int i = 0 ; i < len; i++)
		cout << s[i] << endl;

	const char *cs = s.c_str();
	cout << cs << endl;
	return 0;
}
