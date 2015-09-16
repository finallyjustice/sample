#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <list>
#include <vector>
#include <queue>

using namespace std;

struct node {
	vector<int> nl;
};

typedef struct node NODE;

void bfs_graph(vector<node> &vert, int nv, int start)
{
	int color[nv];
	for(int i=0; i<nv; i++)
		color[i] = -1;
	queue<int> q;
	color[start] = 1;
	q.push(start);

	printf("BFS: ");
	while(!q.empty()) {
		int cur = q.front();
		q.pop();
		printf("%d ", cur);

		int sc = vert[cur].nl.size();
		for(int i=0; i<sc; i++) {
			int idx = vert[cur].nl[i];
			if(color[idx] == -1) {
				color[idx] = 1;
				q.push(idx);
			}
		}
	}
	printf("\n");
}

void dfs_recv(vector<node> &vert, int *color, int idx)
{
	color[idx] = 1;
	printf("%d ", idx);

	int sc = vert[idx].nl.size();
	for(int i=0; i<sc; i++) {
		int ni = vert[idx].nl[i];
		if(color[ni] == -1)
			dfs_recv(vert, color, ni);
	}
}

void dfs_graph(vector<node> &vert, int nv, int start)
{
	int color[nv];
	for(int i=0; i<nv; i++)
		color[i] = -1;

	printf("DFS: ");
	dfs_recv(vert, color, start);
	printf("\n");
}

int main(int argc, char **argv)
{
	int nv, ne;
	cin >> nv;
	cin >> ne;
	
	vector<struct node> vert(nv);
	for(int i=0; i<ne; i++) {
		int src, dst;
		cin >> src;
		cin >> dst;
		vert[src].nl.push_back(dst);
		vert[dst].nl.push_back(src);
	}

	bfs_graph(vert, nv, 4);
	dfs_graph(vert, nv, 4);

	return 0;
}
