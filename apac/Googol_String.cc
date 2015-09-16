#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

#define MAX_RD 100
long long len[MAX_RD];

int ret_kth(int r, long long k)
{
	if(r == 1)
		return 0;
	long long mid = len[r]/2+1;

	if(k < mid)
		return ret_kth(r-1, k); 
	else if(k == mid)
		return 0;
	else
		return 1-ret_kth(r-1, 2*mid-k);

	return 0;
}

int main(int argc, char **argv)
{
	int num_case;
	cin >> num_case;
	vector <long long> vk;

	long long maxk = 0;
	for(int i=0; i<num_case; i++) {
		long long k;
		cin >> k;
		vk.push_back(k);
		if(k > maxk)
			maxk = k;
	}

	int gg = 0;
	long long last = 0;
	len[gg] = last;
	while(last < maxk) {
		gg++;
		last = last*2+1;
		len[gg] = last;
	}

	for(int i=0; i<num_case; i++) {
		printf("Case #%d: %d\n", i+1, ret_kth(gg, vk[i]));
	}

	return 0;
}
