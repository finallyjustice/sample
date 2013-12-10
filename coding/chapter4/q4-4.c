/** File:       q4-4.c
 ** Author:     Dongli Zhang
 ** Contact:    dongli.zhang0129@gmail.com
 **
 ** Copyright (C) Dongli Zhang 2013
 **
 ** This program is free software;  you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY;  without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 ** the GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program;  if not, write to the Free Software 
 ** Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*  Q4.4. Create linked list of all nodes at each depth in a BST.
 */

/* usage: gcc q2-7.c -o q2-7 */

#include <stdio.h>
#include <stdlib.h>

// Data Structure of Tree
typedef struct node
{
	int val;
	struct node *pn;
	struct node *ln;
	struct node *rn;
}node_t;

// Data Structure of Queue
typedef struct qnode
{
	node_t *nd;
	struct qnode *next;
}qnode_t;

typedef struct queue
{
	qnode_t *head;
	qnode_t *tail;
}queue_t;

queue_t* init_queue()
{
	queue_t *q = (queue_t *)malloc(sizeof(queue_t));
	q->head = NULL;
	q->tail = NULL;
	return q;
}

void enqueue(queue_t *q, node_t *n)
{
	// make the qnode first
	qnode_t *qn = (qnode_t *)malloc(sizeof(qnode_t));
	qn->nd = n;
	qn->next = NULL;

	//if queue is empty
	if(q->head == NULL)
	{
		q->head = qn;
		q->tail = qn;
		return;
	}

	q->tail->next = qn;
	q->tail = qn;
}

node_t* dequeue(queue_t *q)
{
	if(q->head == q->tail)
	{
		node_t *ret = q->head->nd;
		free(q->head);
		q->head = NULL;
		q->tail = NULL;
		return ret;
	}

	qnode_t *qret = q->head;
	node_t *ret= qret->nd;
	q->head = q->head->next;
	free(qret);
	return ret;
}

int is_empty_queue(queue_t *q)
{
	if(q->head == NULL)
		return 1;
	else
		return 0;
}

// End of Queue Data Structure

node_t* bst_search(node_t *root, int val)
{
	if(root == NULL)
		return NULL;

	if(val == root->val)
		return root;

	if(root->ln && val<=root->val)
		return bst_search(root->ln, val);
	
	if(root->rn && val>root->val)
		return bst_search(root->rn, val);

	return NULL;
}

void bst_insert_node(node_t **root, node_t *n)
{
	n->ln = NULL;
	n->rn = NULL;

	//if bst is empty
	if(*root == NULL)
	{
		*root = n;
		n->pn = NULL;
		return;
	}

	//if val less than or equal to root
	if(n->val <= (*root)->val)
	{
		if((*root)->ln == NULL)
		{
			(*root)->ln = n;
			n->pn = (*root);
		}
		else
		{
			bst_insert_node(&((*root)->ln), n);
		}
	}
	else
	{
		if((*root)->rn == NULL)
		{
			(*root)->rn = n;
			n->pn = (*root);
		}
		else
		{
			bst_insert_node(&((*root)->rn), n);
		}
	}
}

void bst_insert_val(node_t **root, int val)
{

	node_t *n = (node_t *)malloc(sizeof(node_t)); 
	n->val = val;
	n->pn = NULL;
	n->ln = NULL;
	n->rn = NULL;
	bst_insert_node(root, n);
}

void bst_pre_order(node_t *root)
{
	if(root == NULL) return;
	printf("%d\n", root->val);
	bst_pre_order(root->ln);
	bst_pre_order(root->rn);
}

void bst_in_order(node_t *root)
{
	if(root == NULL) return;
	bst_in_order(root->ln);
	printf("%d\n", root->val);
	bst_in_order(root->rn);
}

void bst_aft_order(node_t *root)
{
	if(root == NULL) return;
	bst_aft_order(root->ln);
	bst_aft_order(root->rn);
	printf("%d\n", root->val);
}

node_t* bst_min(node_t *root)
{
	node_t *tmp = root;
	while(tmp && tmp->ln)
		tmp = tmp->ln;
	return tmp;
}

node_t* bst_max(node_t *root)
{
	node_t *tmp = root;
	while(tmp && tmp->rn)
		tmp = tmp->rn;
	return tmp;
}

node_t* bst_successor(node_t *n)
{
	if(n == NULL) 
		return NULL;
	if(n->rn) 
		return bst_min(n->rn);

	node_t *p = n->pn;
	while(p && n && n==p->rn)
	{
		n = p;
		p = n->pn;
	}

	return p;
}

node_t* bst_predecessor(node_t *n)
{
	if(n == NULL)
		return NULL;
	if(n->ln)
		return bst_max(n->ln);

	node_t *p = n->pn;
	while(p && n && n==p->ln)
	{
		n = p;
		p = n->pn;
	}

	return p;
}

// find the least common ancester of two nodes - Binary Search Tree Version
node_t* bst_lca(node_t *root, node_t *n1, node_t *n2)
{	
	if(root == NULL)
		return NULL;

	if(n1==root || n2==root)
		return root;

	if(n1->val<=root->val && n2->val<=root->val)
		return bst_lca(root->ln, n1, n2);
	else if(n1->val>root->val && n2->val>root->val)
		return bst_lca(root->rn, n1, n2);
	else
		return root;
}

// find the least common ancester of two nodes - Binary Tree Version (Not BST!)
int cover(node_t *root, node_t *n)
{
	if(root == NULL) 
		return 0;
	if(n == root) 
		return 1;
	return cover(root->ln, n) || cover(root->rn, n);
}

node_t *tree_lca(node_t *root, node_t *n1, node_t *n2)
{
	if(root == NULL)
		return NULL;

	if(n1==root || n2==root)
		return root;

	int n1_is_ln = cover(root->ln, n1);
	int n2_is_ln = cover(root->ln, n2);

	if(n1_is_ln==1 && n2_is_ln==1)			// Both on left side
		return tree_lca(root->ln, n1, n2);
	else if(n1_is_ln==0 && n2_is_ln==0)		// Both on right side
		return tree_lca(root->rn, n1, n2);	
	else									// Not on same side
		return root;
}

void bst_dfs(node_t *root)
{
	if(root == NULL)
		return;

	printf("%d\n", root->val);
	bst_dfs(root->ln);
	bst_dfs(root->rn);
}

void bst_bfs(node_t *root)
{
	if(root == NULL)
		return;

	queue_t *q = init_queue();
	enqueue(q, root);
	while(is_empty_queue(q) == 0)
	{
		node_t *tmp = dequeue(q);
		printf("Val: %d\n", tmp->val);
		if(tmp->ln)
			enqueue(q, tmp->ln);
		if(tmp->rn)
			enqueue(q, tmp->rn);
	}
}

// Define Linked List
typedef struct lnode
{
	node_t *nd;
	struct lnode *next;
}lnode_t;

#define MAX_NODE 20

void insert_list(lnode_t **list, node_t *n)
{
	lnode_t *nn = (lnode_t *)malloc(sizeof(lnode_t));
	nn->nd = n;
	nn->next = NULL;
	lnode_t *tmp = *list;
	if(tmp == NULL) 
	{
		*list = nn;
		return;
	}
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = nn;
}

void print_list(lnode_t *list)
{
	while(list)
	{
		printf("%d ", list->nd->val);
		list = list->next;
	}
	printf("\n");
}

void print_bst_layer(node_t *root)
{
	// define linked list
	lnode_t* ll[MAX_NODE];
	int c;
	for(c=0; c<MAX_NODE; c++)
		ll[c] = NULL;
	
	queue_t* q[2];
	q[0] = init_queue();
	q[1] = init_queue();

	enqueue(q[0], root);
	c = 0;
	while(is_empty_queue(q[0]) == 0)
	{
		node_t *n = dequeue(q[0]);
		insert_list(&(ll[c]), n);
		if(n->ln)
			enqueue(q[1], n->ln);
		if(n->rn)
			enqueue(q[1], n->rn);

		if(is_empty_queue(q[0]) == 1)
		{
			// Swap two queues
			queue_t *qt = q[0];
			q[0] = q[1];
			q[1] = qt;
			c++;
		}
	}

	int i;
	for(i=0; i<c; i++)
		print_list(ll[i]);
}

int main(int argc, char **argv)
{
	node_t *root = NULL;

	bst_insert_val(&root, 5);
	bst_insert_val(&root, 4);
	bst_insert_val(&root, 7);
	bst_insert_val(&root, 1);
	bst_insert_val(&root, 6);
	bst_insert_val(&root, 10);
	bst_insert_val(&root, 3);
	bst_insert_val(&root, 8);
	bst_insert_val(&root, 13);
	bst_insert_val(&root, 2);
	bst_insert_val(&root, 9);
	bst_insert_val(&root, 11);

	print_bst_layer(root);

	return 1;
}
