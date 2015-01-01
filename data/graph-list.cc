#include <iostream>
#include <string>
#include <cstdlib>
#include <queue>
#include <stack>

using namespace std;

template <typename T>
class Node
{
public:
	Node *next;
	int idx;
	int w;
	T val;
};

template <typename T>
class GraphList
{
private:
	Node<T> **nd;
	int num;

private:
	void insert(Node<T> *n, int idx);
	void dfs_recv(int idx, int *visited);

public:
	GraphList();
	void init();
	void debug();
	void bfs();
	void dfs();
	void topology_sort();
};

template <typename T>
void GraphList<T>::insert(Node<T> *n, int idx)
{
	if(nd[idx] == NULL)
	{
		nd[idx] = n;
		n->next = NULL;
		return;
	}

	n->next = nd[idx];
	nd[idx] = n;
}

template <typename T>
GraphList<T>::GraphList()
{
	nd = NULL;
	num = 0;
}

template <typename T>
void GraphList<T>::init()
{
	int tmp;
	int count;
		
	cout<<"Please input graph node number: ";
	cin>>num;

	nd = (Node<T> **)malloc(sizeof(Node<T> *)*num);
	for(int i=0; i<num; i++)
		nd[i] = NULL;

	for(int i=0; i<num; i++)
	{
		cout<<"Please input num of neighbors of "<<i<<": ";
		cin>>count;

		if(count == 0)
			continue;

		cout<<"Please input the list of neighbors of "<<i<<": ";
		for(int j=0; j<count; j++)
		{
			cin>>tmp;
			Node<T> *n = new Node<T>();
			n->idx = tmp;
			insert(n, i);
		}
	}
}

template <typename T>
void GraphList<T>::debug()
{
	for(int i=0; i<num; i++)
	{
		cout<<"Node "<<i<<": ";
		Node<T> *tmp = nd[i];
		while(tmp != NULL)
		{
			cout<<tmp->idx<<" ";
			tmp = tmp->next;
		}
		cout<<endl;
	}
}

template <typename T>
void GraphList<T>::bfs()
{
	cout<<"BFS: ";

	int visited[num];
	for(int i=0; i<num; i++)
		visited[i] = 0;

	queue<int> q;
	q.push(0);
	visited[0] = 1;
	cout<<0<<" ";

	while(!q.empty())
	{
		int idx = q.front();
		q.pop();

		// for each neighbor of node tmp
		// push it into queue
		Node<T> *tmp = nd[idx];
		while(tmp != NULL)
		{
			if(visited[tmp->idx] == 0)
			{
				visited[tmp->idx] = 1;
				q.push(tmp->idx);
				cout<<tmp->idx<<" ";
			}
			tmp = tmp->next;		
		}
	}

	cout<<endl;
}

template <typename T>
void GraphList<T>::dfs_recv(int idx, int *visited)
{
	visited[idx] = 1;
	
	cout<<idx<<" ";

	// for each neighbor of the node
	Node<T> *tmp = nd[idx];
	while(tmp != NULL)
	{
		if(visited[tmp->idx] == 0)
			dfs_recv(tmp->idx, visited);
		tmp = tmp->next;
	}
}

template <typename T>
void GraphList<T>::dfs()
{
	cout<<"DFS: ";

	int *visited = (int *)malloc(sizeof(int)*num);	
	for(int i=0; i<num; i++)
		visited[i] = 0;

	dfs_recv(0, visited);

	free(visited);
	
	cout<<endl;
}

template <typename T>
void GraphList<T>::topology_sort()
{
	int indegree[num];
	int visited[num];
	queue<int> q;

	for(int i=0; i<num; i++)
	{
		indegree[i] = 0;
		visited[i] = 0;
	}

	for(int i=0; i<num; i++)
	{
		Node<T> *tmp = nd[i];
		while(tmp != NULL)
		{
			indegree[tmp->idx]++;
			tmp = tmp->next;
		}
	}

	stack<int> s;
	for(int i=0; i<num; i++)
	{
		if(indegree[i] == 0)
		{
			visited[i] = 1;
			s.push(i);
		}
	}

	while(!s.empty())
	{
		int i = s.top();
		s.pop();

		// output result
		//cout<<i<<endl;
		q.push(i);

		Node<T> *tmp = nd[i];
		while(tmp != NULL)
		{
			if(visited[tmp->idx] == 1)
			{
				cout<<"Loop detected in graph"<<endl;
				return;
			}

			indegree[tmp->idx]--;
			if(indegree[tmp->idx] == 0)
			{
				visited[tmp->idx] = 1;
				s.push(tmp->idx);
			}
			tmp = tmp->next;
		}
	}

	int tot = 0;
	while(!q.empty())
	{
		cout<<q.front()<<" ";
		q.pop();
		tot++;
	}
	cout<<endl;

	if(tot != num)
		cout<<"Loop Detected!"<<endl;
}

int main(int argc, char **argv)
{
	GraphList<int> g;
	g.init();
	g.debug();
	//g.bfs();
	//g.dfs();
	g.topology_sort();
	return 0;
}
