#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

struct edge {
	int v1;
	int v2;
	int w;
	bool operator<(struct edge other) const {
		return w < other.w; 
	}
};

typedef struct edge EDGE;

int find_set(int *root, int a)
{
	int ret = a;
	while(root[ret] != ret)
		ret = root[ret];
	return ret;
}

void union_set(int *root, int ra, int rb)
{
	//int ra = find_set(root, a);
	//int rb = find_set(root, b);
	root[rb] = ra;
}

void mst_kruskal(vector<EDGE> &e, int nv, int ne)
{
	sort(e.begin(), e.end());

	int root[nv];
	for(int i=0; i<nv; i++)
		root[i] = i;

	for(int i=0; i<ne; i++) {
		int v1 = e[i].v1;
		int v2 = e[i].v2;
		
		int ra = find_set(root, v1);
		int rb = find_set(root, v2);

		if(ra != rb) {
			union_set(root, ra, rb);
			printf("edge: %d %d\n", v1, v2);
		}
	}
}

int main(int argc, char **argv)
{
	int nv;
	int ne;
	cin >> nv;
	cin >> ne;

	vector<EDGE> e(ne);
	for(int i=0; i<ne; i++) {
		cin >> e[i].v1;
		cin >> e[i].v2;
		cin >> e[i].w;
	}

	mst_kruskal(e, nv, ne);

	return 0;
}
