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

using namespace std;

int count_money(vector<string> vs)
{
	int size = vs.size();
	int money = 0;
	string last = " ";
	for(int i=0; i<size; i++) {
		if(vs[i] < last)
			money++;
		else
			last = vs[i];
	}
	return money;
}

int main(int argc, char **argv)
{
	if(argc != 2) {
		printf("No input\n");
		return -1;
	}

	ifstream ifs(argv[1]);
	string num_case_str;
	getline(ifs, num_case_str);
	int num_case = atoi(num_case_str.c_str());

	for(int i=0; i<num_case; i++) {
		string num_card_str;
		getline(ifs, num_card_str);
		int num_card = atoi(num_card_str.c_str());		
		vector<string> vs;
		for(int j=0; j<num_card; j++) {
			string card;
			getline(ifs, card);
			vs.push_back(card);
		}
		printf("Case #%d: %d\n", i+1, count_money(vs));
	}

	ifs.close();
	return 0;
}
