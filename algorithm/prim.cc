#include <iostream>
#include <cstdio>
#include <set>
#include <vector>
#include <cstdlib>
#include <climits>

using namespace std;

void prim_mst(int **graph, int nv)
{
	int lowcost[nv];
	int prev[nv];

	for(int i=0; i<nv; i++) {
		lowcost[i] = INT_MAX;
		prev[i] = -1;
	}

	lowcost[0] = 0;
	prev[0] = 0;
	for(int i=1; i<nv; i++) { 
		lowcost[i] = graph[0][i];
		prev[i] = 0;
	}

	for(int i=1; i<nv; i++) {
		int min = INT_MAX;
		int mj;
		for(int j=0; j<nv; j++) {
			if(lowcost[j]<min && lowcost[j]!=0) {
				min = lowcost[j];
				mj = j;
			}
		}

		printf("edge: %d %d\n", prev[mj], mj);

		for(int j=0; j<nv; j++) {
			if(graph[mj][j]<lowcost[j] && graph[mj][j]!=-1) {
				lowcost[j] = graph[mj][j];
				prev[j] = mj;
			}
		}
	}
}

int main(int argc, char **argv)
{
	int nv, ne;
	cin >> nv;
	cin >> ne;

	int **graph = (int **)malloc(sizeof(int*)*nv);
	for(int i=0; i<nv; i++)
		graph[i] = (int *)malloc(sizeof(int)*nv);

	for(int i=0; i<nv; i++) {
		for(int j=0; j<nv; j++) {
			if(i == j)
				graph[i][j] = 0;
			else
				graph[i][j] = INT_MAX;
		}
	}

	for(int i=0; i<ne; i++) {
		int src, dst, w;
		cin >> src;
		cin >> dst;
		cin >> w;
		graph[src][dst] = w;
		graph[dst][src] = w;
	}

	prim_mst(graph, nv);

	free(graph);
	return 0;
}
