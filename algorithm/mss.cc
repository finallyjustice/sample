// max substring sum

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int max3(int a, int b, int c)
{
	int t = a>=b?a:b;
	return t>=c?t:c;
}

int mss_naive(int *a, int n)
{
	int i, j, max, current;

	max = (int)-INFINITY;
	for(i=0; i<n; i++)
	{
		current = 0;
		for(j=i; j<n; j++)
		{
			current += a[j];
			if(current > max)
				max = current;
		}
	}

	return max;
}

int mss_div(int *a, int p, int q)
{
	if(p == q)
		return a[p];

	int m = p+(q-p)/2;
	int rl = mss_div(a, p, m);
	int rr = mss_div(a, m+1, q);

	int ml, mr;
	int i, current;

	current = a[m];
	ml = a[m];
	for(i=m-1; i>=p; i--)
	{
		current += a[i];
		if(current > ml)
			ml = current;
	}

	current = a[m+1];
	mr = a[m+1];
	for(i=m+2; i<=q; i++)
	{
		current += a[i];
		if(current > mr)
			mr = current;
	}

	int ret = max3(rl, rr, ml+mr);

	return ret;
}

int mss_dp(int *a, int n)
{
	int start, current, i;

	start = a[n-1];
	current = a[n-1];

	for(i=n-2; i>=0; i--)
	{
		start = max(start+a[i], a[i]);
		current = max(start, current);
	}

	return current;
}

int main(int argc, char **argv)
{
	int a[] = {-2, 5, 3, -6, 4, -8, 6}; // 8
	//int a[] = {1, -2, 3, 5, -3, 2}; // 8
	//int a[] = {0, -2, 3, 5, -1, 2}; // 9
	//int a[] = {-9, -2, -3, -5, -3}; // -2
	int n = sizeof(a)/sizeof(int);

	cout<<"Naive:               "<<mss_naive(a, n)<<endl;
	cout<<"Divide and Conquer:  "<<mss_div(a, 0, n-1)<<endl;
	cout<<"Dynamic Programming: "<<mss_dp(a, n)<<endl;

	return 0;
}
