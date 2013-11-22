#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *next;
}node;

void insert_list(node **head, node *n)
{
	n->next = *head;
	*head = n;
}

void traverse_list(node *head)
{
	node *tmp = head;
	while(tmp)
	{
		printf("Val: %d\n", tmp->val);
		tmp = tmp->next;
	}
}

node* find_intersection(node *h1, node *h2)
{
	int c1 = 0;
	int c2 = 0;
	node *tmp = h1;
	while(tmp)
	{
		c1++;
		tmp = tmp->next;
	}
	tmp = h2;
	while(tmp)
	{
		c2++;
		tmp = tmp->next;
	}

	if(c1 == c2) return NULL;

	node *mh1;
	node *mh2;
	int mc;
	int dist;
	if(c1 >= c2)
	{
		mh1 = h1;
		mh2 = h2;
		mc = c1;
		dist = c1-c2;
	}
	else
	{
		mh1 = h2;
		mh2 = h1;
		mc = c2;
		dist = c2-c1;
	}

	while(dist)
	{
		mh1 = mh1->next;
		dist--;
	}

	while(mh1 != mh2)
	{
		mh1 = mh1->next;
		mh2 = mh2->next;
	}

	return mh1;
}

int main(int argc, char **argv)
{
	node *h1 = NULL;
	node *h2 = NULL;
	node *cm = NULL;
	node *n;
	
	n = (node *)malloc(sizeof(node));
	n->val = 1;
	insert_list(&cm, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 2;
	insert_list(&cm, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_list(&cm, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 30;
	insert_list(&cm, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 15;
	insert_list(&cm, n);
	
	h1 = cm;
	h2 = cm;
	
	n = (node *)malloc(sizeof(node));
	n->val = 9;
	insert_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 6;
	insert_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 10;
	insert_list(&h2, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 100;
	insert_list(&h2, n);

	printf("List1:\n");
	traverse_list(h1);
	printf("List2:\n");
	traverse_list(h2);

	node *com = find_intersection(h1, h2);
	printf("Commom:\n");
	traverse_list(com);

	return 0;
}
