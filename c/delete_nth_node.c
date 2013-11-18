#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *next;
}node;

void insert_sorted(node **head, node *n)
{
	node *tmp = *head;

	if(tmp==NULL || n->val<tmp->val)
	{
		n->next = *head;
		*head = n;
		return;
	}

	while(tmp->next && n->val>tmp->next->val)
	{
		tmp = tmp->next;
	}
	n->next = tmp->next;
	tmp->next = n;	
}

node* delete_nth_node(node **head, int n)
{
	node *f = *head;
	node *t = *head;
	int i;

	for(i=0; i<n-1; i++)
	{
		t = t->next;
	}

	while(t->next)
	{
		f = f->next;
		t = t->next;
	}

	return f;
}

void traverse_list(node *head)
{
	node *tmp = head;
	while(tmp)
	{
		printf("Value: %d\n", tmp->val);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	node *n;
	node *head = NULL;
	
	n = (node *)malloc(sizeof(node));
	n->val = 5;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 6;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 10;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 7;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 9;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 1;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 10;
	insert_sorted(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 8;
	insert_sorted(&head, n);
	
	traverse_list(head);

	node *ret = delete_nth_node(&head, 1);

	printf("Result: %d\n", ret->val);
}
