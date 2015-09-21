#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstring>
#include <climits>

using namespace std;

struct node {
	vector<int> nl;
	vector<int> nw;
};

typedef struct node NODE;

void Dijkstra(NODE *graph, int nv, int start)
{
	int finish[nv];
	int prev[nv];
	int dist[nv];
	for(int i=0; i<nv; i++) {
		finish[i] = 0;
		prev[i] = -1;
		dist[i] = INT_MAX;
	}

	finish[start] = 1;
	dist[start] = 0;
	int sn = graph[start].nl.size();
	for(int i=0; i<sn; i++) {
		int ni = graph[start].nl[i];
		int nw = graph[start].nw[i];
		prev[ni] = start;
		dist[ni] = nw;
	}

	for(int i=0; i<nv-1; i++) {
		int mw = INT_MAX;
		int mi = -1;
		for(int j=0; j<nv; j++) {
			if(finish[j]==0 && dist[j]<mw) {
				mw = dist[j];
				mi = j;
			}
		}
		if(mi == -1)
			printf("ERROR\n");

		printf("mi: %d\n", mi);

		finish[mi] = 1;
		
		// update mj neighbors
		sn = graph[mi].nl.size();
		for(int j=0; j<sn; j++) {
			int ni = graph[mi].nl[j];
			int nw = graph[mi].nw[j];
			if(finish[ni] == 1)
				continue;

			if(dist[mi]+nw < dist[ni]) {
				dist[ni] = dist[mi]+nw;
				prev[ni] = mi;
			}
		}
	}

	printf("DIST: ");
	for(int i=0; i<nv; i++) 
		printf("%d ", dist[i]);
	printf("\n");
}

int main(int argc, char **argv)
{
	int nv, ne;
	cin >> nv;
	cin >> ne;
	NODE graph[nv];
	for(int i=0; i<ne; i++) {
		int src, dst, w;
		cin >> src;
		cin >> dst;
		cin >> w;
		graph[src].nl.push_back(dst);
		graph[src].nw.push_back(w);
	}

	int start = 0;
	Dijkstra(graph, nv, 2);

	return 0;
}
