#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <string.h>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <math.h>

using namespace std;

double calc_angle(double v, double d)
{
	double r = d*9.8/v/v;
	if(r > 1.0)
		r = 1.0;
	return asin(r) / 2.0 * 180.0 / M_PI;
}

int main(int argc, char **argv)
{
	if(argc != 2) {
		printf("No input\n");
		return -1;
	}

	ifstream ifs(argv[1]);

	int num_case;
	ifs >> num_case;

	for(int i=0; i<num_case; i++) {
		int v, d;
		ifs >> v;
		ifs >> d;
		printf("Case #%d: %.7lf\n", i+1, calc_angle((double)v, (double)d));
	}

	ifs.close();
	return 0;
}
