// strongly connected components

#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

struct node {
	vector<int> nl;
};

typedef struct node NODE;

void dfs1(int idx, vector<NODE> &graph, stack<int> &stk, int *color)
{
	if(color[idx] != -1)
		return;
	color[idx] = 1;

	int nc = graph[idx].nl.size();
	for(int i=0; i<nc; i++) {
		int ni = graph[idx].nl[i];
		dfs1(ni, graph, stk, color);
	}
	stk.push(idx);
}

void dfs2(int idx, vector<NODE> &tgraph, int *color, vector<int> &comp)
{
	if(color[idx] != -1)
		return;
	color[idx] = 1;

	comp.push_back(idx);
	int nc = tgraph[idx].nl.size();
	for(int i=0; i<nc; i++) {
		int ni = tgraph[idx].nl[i];
		dfs2(ni, tgraph, color, comp);
	}
}

void conn_comp(vector<NODE> &graph, vector<NODE> &tgraph, int nv)
{
	stack<int> stk;
	int color[nv];
	for(int i=0; i<nv; i++)
		color[i] = -1;
	for(int i=0; i<nv; i++)
		dfs1(i, graph, stk, color);

	for(int i=0; i<nv; i++)
		color[i] = -1;

	int ci = 0;
	while(!stk.empty()) {
		int idx = stk.top();
		stk.pop();
		vector<int> comp;
		dfs2(idx, tgraph, color, comp);

		if(comp.size() > 0) {
			printf("COMP %d: ", ci++);
			for(int i=0; i<comp.size(); i++)
				printf("%d ", comp[i]);
			printf("\n");
		}
	}
}

int main(int argc, char **argv)
{
	int nv, ne;
	cin >> nv;
	cin >> ne;
	vector<NODE> graph(nv);
	vector<NODE> tgraph(nv);

	for(int i=0; i<ne; i++) {
		int src, dst;
		cin >> src;
		cin >> dst;
		graph[src].nl.push_back(dst);
		tgraph[dst].nl.push_back(src);
	}

	conn_comp(graph, tgraph, nv);	

	return 0;
}
