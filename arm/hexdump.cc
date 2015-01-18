#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

void hexdump(vector<unsigned char> &v)
{
	int len = v.size();
	int i = 0;

	while(i < len)
	{
		printf("%08x ", i);
		for(int j=0; j<16; j++)
		{
			printf("%02x ", v[i+j]);
		}
		printf("  ");
		for(int j=0; j<16; j++)
		{
			if(isprint(v[i+j]))
				printf("%c", v[i+j]);
			else
				printf(".");
		}
		printf("\n");

		i += 16;
	}

	/*int len = v.size();

	for(int i=0; i<len; i++)
	{
		if(i%16 == 0)
			printf("\n%08x ", i);
		printf("%02x", v[i]);
		if(i%2 == 1)
			printf(" ");
	}

	printf("\n");*/
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("hexdump filename\n");
		return -1;
	}

	vector<unsigned char> v;

	FILE *fp = fopen(argv[1], "r");
	if(fp == NULL)
	{
		printf("Failed to open file\n");
		return -1;
	}

	int tmp;
	int cnt = 0;

	tmp = fgetc(fp);
	while(tmp != EOF)
	{
		unsigned char c = tmp;
		v.push_back(c);
		cnt++;

		/*if(cnt%2==0 && cnt>0)
		{
			unsigned char buf = v[cnt-2];
			v[cnt-2] = v[cnt-1];
			v[cnt-1] = buf;
		}*/

		tmp = fgetc(fp);
	}

	fclose(fp);

	hexdump(v);
	return 0;
}
