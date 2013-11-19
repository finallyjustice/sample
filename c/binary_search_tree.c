#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *left;
	struct node_t *right;
}node;

void insert_tree(node **root, node *n)
{
	n->left = NULL;
	n->right = NULL;

	if(*root == NULL)
	{
		*root = n;
		return;
	}

	node *tmp = *root;
	node *pre = tmp;
	while(tmp)
	{
		pre = tmp;
		if(n->val <= tmp->val)	
			tmp = tmp->left;
		else	
			tmp = tmp->right;
	}

	if(n->val <= pre->val)
		pre->left = n;	
	else
		pre->right = n;
}

void pre_order_walk(node *root)
{
	if(root == NULL) return;
	printf("%d\n", root->val);
	pre_order_walk(root->left);
	pre_order_walk(root->right);
}

void in_order_walk(node *root)
{
	if(root == NULL) return;
	in_order_walk(root->left);
	printf("%d\n", root->val);
	in_order_walk(root->right);
}

void post_order_walk(node *root)
{
	if(root == NULL) return;
	post_order_walk(root->left);
	post_order_walk(root->right);
	printf("%d\n", root->val);
}

node* find_minimum(node *root)
{
	node *tmp = root;
	if(tmp == NULL) return NULL;
	while(tmp->left != NULL)
		tmp = tmp->left;
	return tmp;
}

node *find_maximum(node *root)
{
	node *tmp = root;
	if(tmp == NULL) return NULL;
	while(tmp->right != NULL)
		tmp = tmp->right;
	return tmp;
}

node* search_tree(node *root, int val)
{
	node *tmp = root;
	while(tmp && tmp->val!=val)
	{
		if(val <= tmp->val)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
}

void bfs_tree(node *root)
{

}

void dfs_tree(node *root)
{
	if(root == NULL) return;
	printf("%d\n", root->val);
	dfs_tree(root->left);
	dfs_tree(root->right)
}

node* find_successor(node *root)
{
	if(root->right)
		return find_minimum(root->right);


}

int main(int argc, char **argv)
{
	node *n;
	node *root = NULL;

	n = (node *)malloc(sizeof(node));
	n->val = 100;
	insert_tree(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 6;
	insert_tree(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_tree(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 7;
	insert_tree(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 8;
	insert_tree(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 1;
	insert_tree(&root, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 10;
	insert_tree(&root, n);

	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_tree(&root, n);

	in_order_walk(root);

	node *min = find_minimum(root);
	node *max = find_maximum(root);
	printf("Min: %d. Max: %d.\n", min->val, max->val);

	node *searched = search_tree(root, 1);
	printf("Searched: %d\n", searched->val);

	return 0;
}
