#include <iostream>
#include <cstdlib>
#include <queue>
#include <stack>

using namespace std;

template <typename T>
struct node
{
	struct node *ln;
	struct node *rn;
	struct node *pn;
	T val;
};

template <typename T>
class MyBST 
{
private:
	struct node<T> *root;

private:
	void pre_walk_recv(struct node<T> *r);
	void in_walk_recv(struct node<T> *r);
	void post_walk_recv(struct node<T> *r);	
	struct node<T>* minimum(struct node<T> *r);
	struct node<T>* maximum(struct node<T> *r);
	struct node<T>* find(T val);
	struct node<T>* predecessor(struct node<T> *n);
	struct node<T>* successor(struct node<T> *n);

public:
	MyBST();

	void bfs();
	void bfs_layer();
	void pre_walk();
	void in_walk();
	void post_walk();	
	void pre_walk_iter();
	void in_walk_iter();
	void post_walk_iter();
	void insert(T val);
	T find_min();
	T find_max();
	void remove(T val);
};

template <typename T>
MyBST<T>::MyBST()
{
	root = NULL;
}

template <typename T>
void MyBST<T>::bfs()
{
	if(root == NULL)
		return;

	queue<struct node<T> *> q;
	q.push(root);

	while(!q.empty())
	{
		struct node<T> *tmp = q.front();
		cout<<tmp->val<<" ";
		if(tmp->ln != NULL)
			q.push(tmp->ln);
		if(tmp->rn != NULL)
			q.push(tmp->rn);
		q.pop();
	}

	cout<<endl;
}

template <typename T>
void MyBST<T>::bfs_layer()
{
	queue<struct node<T> *> q;
	queue<int> ql;

	int c = 1;

	q.push(root);
	ql.push(c);

	while(!q.empty())
	{
		struct node<T> *tmp = q.front();
		int level = ql.front();

		if(level > c)
		{
			c++;
			cout<<endl;
		}

		cout<<tmp->val<<" ";

		if(tmp->ln != NULL)
		{
			q.push(tmp->ln);
			ql.push(level+1);
		}
		if(tmp->rn != NULL)
		{
			q.push(tmp->rn);
			ql.push(level+1);
		}
		q.pop();
		ql.pop();
	}

	cout<<endl;
}

template <typename T> 
void MyBST<T>::pre_walk_recv(struct node<T> *r)
{
	if(r == NULL)
		return;
	cout<<r->val<<" ";
	pre_walk_recv(r->ln);
	pre_walk_recv(r->rn);
}

template <typename T> 
void MyBST<T>::in_walk_recv(struct node<T> *r)
{
	if(r == NULL)
		return;
	in_walk_recv(r->ln);
	cout<<r->val<<" ";
	in_walk_recv(r->rn);

}

template <typename T> 
void MyBST<T>::post_walk_recv(struct node<T> *r)
{
	if(r == NULL)
		return;
	post_walk_recv(r->ln);
	post_walk_recv(r->rn);
	cout<<r->val<<" ";
}

template <typename T>
void MyBST<T>::pre_walk()
{
	pre_walk_recv(root);
	cout<<endl;
}

template <typename T>
void MyBST<T>::in_walk()
{
	in_walk_recv(root);
	cout<<endl;
}

template <typename T>
void MyBST<T>::post_walk()
{
	post_walk_recv(root);
	cout<<endl;
}

template <typename T>
void MyBST<T>::pre_walk_iter()
{
	stack<struct node<T> *> s;
	s.push(root);

	while(!s.empty())
	{
		struct node<T> *n = s.top();
		s.pop();
		cout<<n->val<<" ";
		if(n->rn != NULL)
			s.push(n->rn);
		if(n->ln != NULL)
			s.push(n->ln);

	}

	cout<<endl;
}

template <typename T>
void MyBST<T>::in_walk_iter()
{
	stack<struct node<T> *> s;

	struct node<T> *tmp = root;
	while(tmp != NULL)
	{
		s.push(tmp);
		tmp = tmp->ln;
	}

	while(!s.empty())
	{
		struct node<T> *n = s.top();
		s.pop();

		cout<<n->val<<" ";

		tmp = n->rn;
		while(tmp)
		{
			s.push(tmp);
			tmp = tmp->ln;
		}
	}

	cout<<endl;
}

template <typename T>
void MyBST<T>::post_walk_iter()
{
	if(root == NULL)
		return;

	stack<struct node<T> *> s;
	stack<T> sv;
	s.push(root);

	while(!s.empty())
	{
		struct node<T> *n = s.top();
		s.pop();

		sv.push(n->val);

		if(n->ln != NULL)
			s.push(n->ln);
		if(n->rn != NULL)
			s.push(n->rn);
	}

	while(!sv.empty())
	{
		cout<<sv.top()<<" ";
		sv.pop();
	}

	cout<<endl;
}

template <typename T>
void MyBST<T>::insert(T val)
{	
	struct node<T> *n = (struct node<T> *)malloc(sizeof(struct node<T>));
	n->ln = NULL;
	n->rn = NULL;
	n->val = val;
	
	if(root == NULL)
	{
		root = n;
		n->pn = NULL;
		return;
	}

	struct node<T> *tmp = root;

	while(tmp != NULL)
	{
		if(val <= tmp->val)
		{
			if(tmp->ln == NULL)
			{
				tmp->ln = n;
				n->pn = tmp;
				return;
			}
			else
			{
				tmp = tmp->ln;
			}
		}
		else
		{
			if(tmp->rn == NULL)
			{
				tmp->rn = n;
				n->pn = tmp;
				return;
			}
			else
			{
				tmp = tmp->rn;
			}
		}
	}
}

template <typename T>
struct node<T>* MyBST<T>::minimum(struct node<T> *r)
{
	struct node<T> *tmp = r;
	while(tmp->ln != NULL)
		tmp = tmp->ln;
	return tmp;
}

template <typename T>
struct node<T>* MyBST<T>::maximum(struct node<T> *r)
{
	struct node<T> *tmp = r;
	while(tmp->rn != NULL)
		tmp = tmp->rn;
	return tmp;
}

template <typename T>
struct node<T>* MyBST<T>::find(T val)
{
	struct node<T> *tmp = root;
	while(tmp)
	{
		if(val == tmp->val)
			return tmp;

		if(val <= tmp->val)
			tmp = tmp->ln;
		else
			tmp = tmp->rn;
	}

	return NULL;
}

template <typename T>
struct node<T>* MyBST<T>::predecessor(struct node<T> *n)
{
	// find the pointer of node
	struct node<T> *tmp = n;

	if(tmp->ln != NULL)
		return maximum(tmp->ln);

	struct node<T> *p = tmp->pn;
	while(p!=NULL && p->ln==tmp)
	{
		tmp = p;
		p = tmp->pn;
	}

	return p;
}

template <typename T>
struct node<T>* MyBST<T>::successor(struct node<T> *n)
{
	// find the pointer of node
	struct node<T> *tmp = n;

	if(tmp->rn != NULL)
		return minimum(tmp->rn);

	struct node<T> *p = tmp->pn;
	while(p!=NULL && p->rn==tmp)
	{
		tmp = p;
		p = tmp->pn;
	}

	return p;
}

template <typename T>
T MyBST<T>::find_min()
{
	return minimum(root)->val;
}

template <typename T>
T MyBST<T>::find_max()
{
	return maximum(root)->val;	
}

template <typename T>
void MyBST<T>::remove(T val)
{
	// tree is NULL
	if(root == NULL)
		return;

	struct node<T> *n = find(val);

	// both children are NULL
	struct node<T> *p = n->pn;
	if(n->ln==NULL && n->rn==NULL)
	{
		// if n is root
		if(n == root)
		{
			root = NULL;
		}
		else
		{
			if(p->ln == n)
				p->ln = NULL;
			if(p->rn == n)
				p->rn = NULL;
		}

		free(n);
		return;
	}

	// left child is NULL
	if(n->ln!=NULL && n->rn==NULL)
	{
		// if n is root of bst
		if(n == root)
		{
			root = n->ln;
		}
		else
		{
			if(p->ln == n)
				p->ln = n->ln;
			if(p->rn == n)
				p->rn = n->ln;
		}
		
		n->ln->pn = p;
		free(n);
		return;
	}

	// right child is NULL
	if(n->ln==NULL && n->rn!=NULL)
	{
		// if n is root of bst
		if(n == root)
		{
			root = n->rn;
		}
		else
		{
			if(p->ln == n)
				p->ln = n->rn;
			if(p->rn == n)
				p->rn = n->rn;
		}

		n->rn->pn = p;
		free(n);
		return;
	}

	// both children are NOT NULL
	if(n->ln!=NULL && n->rn!=NULL)
	{
		struct node<T> *succ = successor(n);
		// the successor of node n is always NULL
		n->val = succ->val;

		if(succ == succ->pn->ln)
			succ->pn->ln = succ->rn;
		else
			succ->pn->rn = succ->rn;

		if(succ->rn != NULL)
			succ->rn->pn = succ->pn;
		free(succ);
		return;
	}	
}

int main(int argc, char **argv)
{
	MyBST<int> mb;
	
	mb.insert(10);
	mb.insert(5);
	mb.insert(17);
	mb.insert(4);
	mb.insert(8);
	mb.insert(22);
	mb.insert(6);
	mb.insert(9);
	mb.insert(20);
	mb.insert(7);
	mb.insert(15);
	mb.insert(16);

	mb.pre_walk();
	mb.in_walk();
	mb.post_walk();

	cout<<endl;

	mb.pre_walk_iter();
	mb.in_walk_iter();
	mb.post_walk_iter();

	return 0;
}





