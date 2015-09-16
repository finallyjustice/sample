#include <iostream>
#include <cstdio>
#include <vector>
#include <math.h>

using namespace std;

int main(int argc, char **argv)
{
	int num_case;
	cin >> num_case;

	for(int i=0; i<num_case; i++) {
		printf("Case #%d:\n", i+1);
		int m, n;
		cin >> n;
		cin >> m;
		vector<int> vd;
		for(int j=0; j<n; j++) {
			int dim;
			cin >> dim;
			vd.push_back(dim);
		}

		// solution
		for(int j=0; j<m; j++) {
			int l, r;
			cin >> l;
			cin >> r;
			double ret = 0.0;
			double nd = r-l+1; 
			for(int k=l; k<=r; k++)
				ret = ret + log(vd[k]);
			ret = ret / nd;
			ret = exp(ret);
			printf("%.8lf\n", ret);
		}
	}
	return 0;
}
