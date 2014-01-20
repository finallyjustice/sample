#include <stdio.h>
#include <string.h>

void reverse_intact(char *s)
{
	int len = (int)(strlen(s));
	int i;
	for(i=0; i<len/2; i++)
	{
		int tmp = s[i];
		s[i] = s[len-1-i];
		s[len-1-i] = tmp;
	}

	int b, e;
	b = 0;
	while(b < len)
	{
		e = b;
		while(s[e]!=' ' && e<len)
			e++;

		int l = e-b;
		for(i=0; i<l/2; i++)
		{
			int tmp = s[b+i];
			s[b+i] = s[b+l-1-i];
			s[b+l-1-i] = tmp;
		}

		b = e+1;
	}
}

int main(int argc, char **argv)
{
	char s[] = "This is a question";
	printf("%s\n", s);
	reverse_intact(s);
	printf("%s\n", s);
}
