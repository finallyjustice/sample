#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *parent;
	struct node_t *left;
	struct node_t *right;
}node;

void insert_tree_node(node **root, node *n)
{
	n->left = NULL;
	n->right = NULL;

	if(*root == NULL)
	{
		*root = n;
		n->parent = NULL;
		return;
	}

	node *cur = *root;
	node *tmp;
	while(cur)
	{
		tmp = cur;
		if(n->val <= cur->val)
			cur = cur->left;
		else
			cur = cur->right;
	}

	n->parent = tmp;
	if(n->val <= tmp->val)
		tmp->left = n;
	else
		tmp->right = n;
}

node *search_tree(node *root, int val)
{
	node *cur = root;
	node *tmp = NULL;
	while(cur!=NULL && cur->val!=val)
	{
		if(val <= cur->val)
			cur = cur->left;
		else
			cur = cur->right;
	}
	return cur;
}

node* find_min(node *root)
{
	if(root == NULL) return NULL;
	node *tmp = root;
	while(tmp->left)
		tmp = tmp->left;
	return tmp;
}

node* find_max(node *root)
{
	if(root == NULL) return NULL;
	node *tmp = root;
	while(tmp->right)
		tmp = tmp->right;
	return tmp;
}

node* find_successor(node *root, int val)
{
	if(root == NULL) return;
	node *n = search_tree(root, val);

	if(n->right)
		return find_min(n->right);

	node *cur = n;
	node *pre = cur->parent;

	while(pre!=NULL && pre->left!=cur)
	{
		cur = pre;
		pre = pre->parent;
	}

	return pre;
}

int is_descendant(node *root, node *n)
{
	if(root == NULL)
		return 0;
	if(root->val == n->val)
		return 1;
	return	is_descendant(root->left, n) | is_descendant(root->right, n); 
}

node* find_lca(node *root, node *n1, node *n2)
{
	if(root == NULL) return NULL;
	int ol1 = is_descendant(root->left, n1); 
	int ol2 = is_descendant(root->left, n2);

	if(ol1==1 && ol2==1)
	{
		return find_lca(root->left, n1, n2);	
	}
	else if(ol1==0 && ol2==0)
	{
		return find_lca(root->right, n1, n2);
	}
	else
	{
		return root;
	}
}

void pre_order_walk(node *root)
{
	if(root == NULL) return;
	printf("Value: %d\n", root->val);
	pre_order_walk(root->left);
	pre_order_walk(root->right);
}

void in_order_walk(node *root)
{
	if(root == NULL) return;
	in_order_walk(root->left);
	printf("Value: %d\n", root->val);
	in_order_walk(root->right);
}

void post_order_walk(node *root)
{
	if(root == NULL) return;
	post_order_walk(root->left);
	post_order_walk(root->right);
	printf("Value: %d\n", root->val);
}

void dfs_tree(node *root)
{
	if(root == NULL) return;
	printf("Value: %d\n", root->val);
	dfs_tree(root->left);
	dfs_tree(root->right);
}

void bfs_tree(node *root)
{
	if(root == NULL) return;
}

int tree_height(node *root)
{
	if(root == NULL) return -1;
	int hl = tree_height(root->left);
	int hr = tree_height(root->right);
	int max = hl >= hr ? hl : hr;
	return max+1;
}

int main(int argc, char **argv)
{
	node *root = NULL;
	node *n;
	
	n = (node *)malloc(sizeof(node));
	n->val = 5;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 7;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 10;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 13;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 1;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 11;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 2;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 6;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 8;
	insert_tree_node(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 9;
	insert_tree_node(&root, n);
}


