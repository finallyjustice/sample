#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <stack>
#include <queue>

using namespace std;

template <typename T>
struct node {
	struct node *ln; 
	struct node *rn; 
	struct node *pn; 
	T val;
};

template <typename T>
class MyBST {
private:
	struct node<T> *root;

private:
	void pre_walk_recv(struct node<T> *root);
	void in_walk_recv(struct node<T> *root);
	void post_walk_recv(struct node<T> *root);
	struct node<T>* minimum_internal(struct node<T> *root);
	struct node<T>* maximum_internal(struct node<T> *root);

public:
	MyBST();
	void pre_walk();
	void in_walk();
	void post_walk();
	void pre_walk_iter();
	void in_walk_iter();
	void post_walk_iter();
	void dfs_walk();
	void dfs_order_walk();
	void insert(T val);
	int minimum();
	int maximum();
	struct node<T>* search(int val);
	struct node<T>* predecessor(struct node<T> *n);
	struct node<T>* successor(struct node<T> *n);
	void remove(struct node<T> *n);
};

template <typename T>
void MyBST<T>::pre_walk_recv(struct node<T> *root)
{
	if(root == NULL)
		return;
	printf("%d ", root->val);
	pre_walk_recv(root->ln);
	pre_walk_recv(root->rn);
}

template <typename T>
void MyBST<T>::in_walk_recv(struct node<T> *root)
{
	if(root == NULL)
		return;
	in_walk_recv(root->ln);
	printf("%d ", root->val);
	in_walk_recv(root->rn);
}
	
template <typename T>
void MyBST<T>::post_walk_recv(struct node<T> *root)
{
	if(root == NULL)
		return;
	post_walk_recv(root->ln);
	post_walk_recv(root->rn);
	printf("%d ", root->val);
}

template <typename T>
MyBST<T>::MyBST()
{
	root = NULL;
}

template <typename T>
void MyBST<T>::pre_walk()
{
	pre_walk_recv(root);
	printf("\n");
}

template <typename T>
void MyBST<T>::in_walk()
{
	in_walk_recv(root);
	printf("\n");
}

template <typename T>
void MyBST<T>::post_walk()
{
	post_walk_recv(root);
	printf("\n");
}

template <typename T>
void MyBST<T>::insert(T val)
{
	struct node<T> *n = (struct node<T> *)malloc(sizeof(struct node<T>));
	n->ln = NULL;
	n->rn = NULL;
	n->pn = NULL;
	n->val = val;

	if(root == NULL) {
		root = n;
		return;
	}

	struct node<T> *tmp = root;
	while(tmp != NULL) {
		if(n->val <= tmp->val) {
			if(tmp->ln == NULL) {
				tmp->ln = n;
				n->pn = tmp;
				return;
			}
			else {
				tmp = tmp->ln;
			}
		}
		else {
			if(tmp->rn == NULL) {
				tmp->rn = n;
				n->pn = tmp;
				return;
			}
			else {
				tmp = tmp->rn;
			}
		}
	}
}

template <typename T>
struct node<T>* MyBST<T>::minimum_internal(struct node<T> *root)
{
	struct node<T> *tmp = root;
	while(tmp->ln != NULL)
		tmp = tmp->ln;
	return tmp;
}

template <typename T>
struct node<T>* MyBST<T>::maximum_internal(struct node<T> *root)
{
	struct node<T> *tmp = root;
	while(tmp->rn != NULL)
		tmp = tmp->rn;
	return tmp;
}

template <typename T>
int MyBST<T>::minimum()
{
	return minimum_internal(root)->val;
}

template <typename T>
int MyBST<T>::maximum()
{
	return maximum_internal(root)->val;
}

template <typename T>
struct node<T>* MyBST<T>::search(int val)
{
	struct node<T> *tmp = root;
	while(tmp != NULL) {
		if(tmp->val == val)
			break;
		if(val < tmp->val)
			tmp = tmp->ln;
		else
			tmp = tmp->rn;
	}
	return tmp;
}

template <typename T>
struct node<T>* MyBST<T>::predecessor(struct node<T> *n)
{
	if(n->ln != NULL)
		return maximum_internal(n->ln); 

	struct node<T> *pred = n->pn;
	while(pred!=NULL && pred->ln==n) {
		n = pred;
		pred = pred->pn;
	}

	return pred;
}
	
template <typename T>
struct node<T>* MyBST<T>::successor(struct node<T> *n)
{
	if(n->rn != NULL)
		return minimum_internal(n->rn);

	struct node<T> *pred = n->pn;
	while(pred!=NULL && pred->rn==n) {
		n  = pred;
		pred = pred->pn;
	}

	return pred;
}

template <typename T>
void MyBST<T>::remove(struct node<T> *n)
{
	struct node<T> *tmp;

	// if one of children is NULL
	if(n->ln==NULL || n->rn==NULL) {
		if(n->ln == NULL)
			tmp = n->rn;
		else
			tmp = n->ln;

		if(n != root) {
			struct node<T> *pn = n->pn;
			if(pn->ln == n)
				pn->ln = tmp;
			else
				pn->rn = tmp;
			if(tmp != NULL)
				tmp->pn = pn;
		} else {
			root = tmp;
			if(tmp != NULL)
				root->pn = NULL;
		}
		free(n);
		return;
	}

	// if both children are not NULL
	tmp = minimum_internal(n->rn);
	n->val = tmp->val;
	if(tmp == tmp->pn->ln)
		tmp->pn->ln = tmp->rn;
	else
		tmp->pn->rn = tmp->rn;
	if(tmp->rn != NULL)
		tmp->rn->pn = tmp->pn;
	free(tmp);

	return;
}

template <typename T>
void MyBST<T>::pre_walk_iter()
{
	struct node<T> *tmp = root;
	stack< struct node<T>* > stk;	

	while(1) {
		while(tmp != NULL) {
			printf("%d ", tmp->val);
			if(tmp->rn != NULL)
				stk.push(tmp);
			tmp = tmp->ln;
		}

		if(!stk.empty()) {
			tmp = stk.top()->rn;
			stk.pop();
		} else {
			break;
		}
	}

	printf("\n");
}

template <typename T>
void MyBST<T>::in_walk_iter()
{
	struct node<T>* tmp = root;
	stack< struct node<T>* > stk;

	while(1) {
		while(tmp != NULL) {
			stk.push(tmp);
			tmp = tmp->ln;
		}

		if(!stk.empty()) {
			printf("%d ", stk.top()->val);
			tmp = stk.top()->rn;
			stk.pop();
		} else {
			break;
		}
	}

	printf("\n");
}

template <typename T>
void MyBST<T>::post_walk_iter()
{
	struct node<T> *tmp = root;
	stack< struct node<T>* > stk;
	stack<T> ot;

	while(1) {
		while(tmp != NULL) {
			ot.push(tmp->val);
			stk.push(tmp);
			tmp = tmp->rn;
		}

		if(!stk.empty()) {
			tmp = stk.top()->ln;
			stk.pop();
		} else {
			break;
		}
	}

	while(!ot.empty()) {
		printf("%d ", ot.top());
		ot.pop();
	}
	printf("\n");
}

template <typename T>
void MyBST<T>::dfs_walk()
{
	struct node<T> *tmp = root;
	queue< struct node<T>* > q;
	q.push(tmp);

	while(!q.empty()) {
		tmp = q.front();
		q.pop();
		printf("%d ", tmp->val);
		if(tmp->ln != NULL)
			q.push(tmp->ln);
		if(tmp->rn != NULL)
			q.push(tmp->rn);
	}

	printf("\n");
}

template <typename T>
void MyBST<T>::dfs_order_walk()
{
	struct node<T> *tmp = root;
	queue< struct node<T>* > q1;
	queue<int> q2;
	q1.push(tmp);
	q2.push(0);
	int cd = 0;

	while(!q1.empty()) {
		tmp = q1.front();
		if(q2.front() > cd) {
			printf("\n");
			cd++;
		}
		q1.pop();
		q2.pop();
		printf("%d ", tmp->val);
		if(tmp->ln != NULL) {
			q1.push(tmp->ln);
			q2.push(cd+1);
		}
		if(tmp->rn != NULL) {
			q1.push(tmp->rn);
			q2.push(cd+1);
		}
	}
	
	printf("\n");
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

	printf("RECV:\n");
	mb.pre_walk();
	mb.in_walk();
	mb.post_walk();
	printf("ITER:\n");
	mb.pre_walk_iter();
	mb.in_walk_iter();
	mb.post_walk_iter();
	printf("DFS:\n");
	mb.dfs_walk();
	printf("ORDER:\n");
	mb.dfs_order_walk();

	printf("minimum: %d\n", mb.minimum());
	printf("maximum: %d\n", mb.maximum());

	int target = 4;
	struct node<int> *tmp = mb.search(target);
	printf("search for %d is %d\n", target, tmp->val);
	struct node<int> *pred = mb.predecessor(tmp);
	struct node<int> *succ = mb.successor(tmp);
	printf("pred: %d\n", pred==NULL?-999:pred->val);
	printf("succ: %d\n", succ==NULL?-999:succ->val);

	mb.remove(tmp);
	
	//target = 16;
	//tmp = mb.search(target);
	//printf("search for %d is %d\n", target, tmp->val);
	//
	//mb.remove(tmp);

	mb.pre_walk();
	mb.in_walk();
	mb.post_walk();

	return 0;
}
