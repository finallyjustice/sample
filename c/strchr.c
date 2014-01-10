#include <stdio.h>
#include <string.h>

int main(int argc, char **argv)
{
	char string[100];
	char *ptr, c = ',';

	strcpy(string, "1.45,0.34,5.45");
	ptr = strchr(string, c);
	
	printf("%s\n", ptr);
}
