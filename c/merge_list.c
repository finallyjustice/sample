#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *next;
}node;

void insert_sorted_list(node **head, node *n)
{
	node *tmp = *head;
	if(tmp==NULL || n->val<=tmp->val)
	{
		n->next = *head;
		*head = n;
		return;
	}

	while(tmp->next && tmp->next->val<n->val)
	{
		tmp = tmp->next;
	}

	n->next = tmp->next;
	tmp->next = n;
}

void insert_end(node **head, node **tail, node *n)
{
	n->next = NULL;
	if(*head == NULL)
	{
		*head = n;
		*tail = n;
		return;
	}

	(*tail)->next = n;
	*tail = n;
}

node* merge_list(node *h1, node *h2)
{
	node *t1 = h1;
	node *t2 = h2;
	node *tmp;
	node *nl = NULL;
	node *tail = NULL;

	while(t1 || t2)
	{
		if(t2==NULL || t1->val<=t2->val)
		{
			tmp = t1;
			t1 = t1->next;
			insert_end(&nl, &tail, tmp);	
		}
		
		if(t1==NULL || t2->val<t1->val)
		{
			tmp = t2;
			t2 = t2->next;
			insert_end(&nl, &tail, tmp);	
		}
	}

	return nl;
}

void traverse_list(node *head)
{
	node *tmp = head;
	while(tmp)
	{
		printf("Value : %d\n", tmp->val);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	node *h1 = NULL;
	node *h2 = NULL;
	node *n;

	n = (node *)malloc(sizeof(node));
	n->val = 6;
	insert_sorted_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 5;
	insert_sorted_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 7;
	insert_sorted_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_sorted_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_sorted_list(&h1, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 1;
	insert_sorted_list(&h2, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 5;
	insert_sorted_list(&h2, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 9;
	insert_sorted_list(&h2, n);

	printf("H1:\n");
	traverse_list(h1);
	printf("H2:\n");
	traverse_list(h2);

	node *nl = merge_list(h1, h2);
	printf("Merged:\n");
	traverse_list(nl);
}
