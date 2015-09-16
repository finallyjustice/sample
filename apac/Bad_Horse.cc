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

#define DATA_SIZE 128

struct node {
	int color;
	vector<int> nl;
};
typedef struct node NODE;

bool select_node(NODE *graph, int num_node, int *start)
{
	for(int i=0; i<num_node; i++) {
		if(graph[i].color == -1) {
			*start = i;
			return true;
		}
	}
	return false;
}

bool is_bipartite(NODE *graph, int num_node)
{
	for(int i=0; i<num_node; i++)
		graph[i].color = -1;

	int start = 0;
	queue<int> q;
	do {
		graph[start].color = 0;
		q.push(start);
		while(!q.empty()) {
			int current = q.front();
			q.pop();
			
			int nn = graph[current].nl.size();
			for(int i=0; i<nn; i++) {
				int ni = graph[current].nl[i];
				if(graph[ni].color == graph[current].color)
					return false;
				if(graph[ni].color == -1) {
					graph[ni].color = 1-graph[current].color;
					q.push(ni);
				}
			}
		}
	} while(select_node(graph, num_node, &start));

	return true;
}

int main(int argc, char **argv)
{
	if(argc != 2) {
		printf("No input\n");
		return -1;
	}

	int num_case;

	ifstream fin(argv[1]);

	fin >> num_case;
	for(int nc=0; nc<num_case; nc++) {
		int num_line;
		fin >> num_line;
		map<string, int> mp;
		
		NODE graph[DATA_SIZE];

		int num_node = 0;
		for(int nl=0; nl<num_line; nl++) {
			string s1, s2;
			int id1, id2;
			fin >> s1;
			fin >> s2;

			if(mp.find(s1) == mp.end()) {
				id1 = num_node++;
				mp[s1] = id1; 
			} else {
				id1 = mp[s1];
			}
			if(mp.find(s2) == mp.end()) {
				id2 = num_node++;
				mp[s2] = id2;
			} else {
				id2 = mp[s2];
			}

			graph[id1].nl.push_back(id2); 
			graph[id2].nl.push_back(id1); 
		}

		if(is_bipartite(graph, num_node) == true)
			printf("Case #%d: Yes\n", nc+1);
		else
			printf("Case #%d: No\n", nc+1);
	}

	fin.close();
	return 0;	
}
