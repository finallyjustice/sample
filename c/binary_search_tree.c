#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *left;
	struct node_t *right;
}node;

void insert_tree(node *root, node *n)
{
	n->next = NULL;
	node *tmp = root;
	node *pre = tmp;
	while(tmp)
	{
		pre = tmp;
		if(n->val <= tmp->val)
		{
			tmp = tmp->left;
		}
		else
		{
			tmp = tmp->right;
		}
	}

	if(n->val <= pre->val)
	{
		pre->left = n;	
	}
	else
	{
		pre->right = n;
	}
}

void pre_order_walk(node *root)
{

}

void in_order_walk(node *root)
{

}

void post_order_walk(node *root)
{
	
}

node* find_minimum(node *root)
{

}

node *find_maximum(node *root)
{

}

int main(int argc, char **argv)
{
	return 0;
}
