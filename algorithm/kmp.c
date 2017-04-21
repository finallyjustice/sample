#include <stdio.h>
#include <string.h>

int vio_strstr(char *t, char *p)
{
	int lt = strlen(t);
	int lp = strlen(p);
	int i = 0, j = 0;
	
	while (i < lt && j < lp) {
		if (t[i] == p[j]) {
			i++;
			j++;
		} else {
			i = i - j + 1;
			j = 0;
		}
	}

	if (j == lp)
		return i - j;
	else
		return -1;
}

void vio_strall(char *t, char *p)
{
	int lt = strlen(t);
	int lp = strlen(p);
	int i = 0, j = 0;

	while (i < lt) {
		if (t[i] == p[j]) {
			i++;
			j++;
		} else {
			i = i - j + 1;
			j = 0;
		}

		if (j == lp) {
			printf("vio: find match at %d\n", i - j);
			j = 0;
		}
	}
}

void compute_next(char *p, int *next)
{
	int len = strlen(p);
	int i = 0, j = -1;
	next[0] = -1;

	while (i < len - 1) {
		if (j == -1 || p[i] == p[j]) {
			next[i+1] = j + 1;
			i++;
			j++;
		} else {
			j = next[j];
		}
	}
}

int kmp_strstr(char *t, char *p)
{
	int lt = strlen(t);
	int lp = strlen(p);
	int i = 0, j = 0;
	int next[lp];

	compute_next(p, next);

	while (i < lt && j < lp) {
		if (j == -1 || t[i] == p[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}
	}

	if (j == lp)
		return i - j;
	else
		return -1;
}

void kmp_strall(char *t, char *p)
{
	int lt = strlen(t);
	int lp = strlen(p);
	int i = 0, j = 0;
	int next[lp];

	compute_next(p, next);

	while (i < lt) {
		if (j == -1 || t[i] == p[j]) {
			i++;
			j++;
		} else {
			j = next[j];
		}

		if (j == lp) {
			printf("kmp: find match at %d\n", i - j);
			j = 0;
		}
	}
}

int main(int argc, char **argv)
{
	char t[] = "abcababababdcdeababc";
	char p[] = "aba";

	printf("vio_strstr: %d\n", vio_strstr(t, p));
	printf("kmp_strstr: %d\n", kmp_strstr(t, p));

	vio_strall(t, p);
	kmp_strall(t, p);
	return 0;
}
