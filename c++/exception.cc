#include <iostream>
#include <stdio.h>

using namespace std;

class MyException
{
public:
	MyException(int val)
		: _val(val)
	{

	}

	int GetVal()
	{
		return _val;
	}

private:
	int _val;
};

void TestException(int val) throw(MyException)
{
		if(val < 0)
		{
			printf("throwing exception...\n");
			throw MyException(val);
		}
		else
		{
			printf("Normal %d\n", val);
		}
}

int main(int argc, char **argv)
{
	try
	{
		TestException(-1);
		TestException(2);
	}
	catch(MyException &me)
	{
		printf("catching exception...\n");
		printf("val is %d\n", me.GetVal());
	}
		TestException(2);

	return 0;
}
