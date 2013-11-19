#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
	int val;
	struct node_t *next;
}node;

void insert_list_val(node **head, int val)
{
	node *n = (node *)malloc(sizeof(node));
	n->val = val;
	n->next = *head;
	*head = n;
}

void insert_list_node(node **head, node *n)
{
	n->next = *head;
	*head = n;
}

node* reverse_list(node *head)
{
	node *new_head = NULL;
	node *new;
	node *tmp = head;

	while(tmp)
	{
		new = tmp;
		tmp = tmp->next;
		insert_list_node(&new_head, new);
	}

	return new_head;
}

node* add_list(node *h1, node *h2)
{
	if(h1==NULL || h2==NULL)
		return NULL;

	node *sum = NULL;
	int carry = 0;
	int ret;
	node *r1 = reverse_list(h1);
	node *r2 = reverse_list(h2);
	while(r1 && r2)
	{
		ret = r1->val + r2->val + carry;
		carry = ret / 10;
		ret = ret % 10;
		insert_list_val(&sum, ret);
		r1 = r1->next;
		r2 = r2->next;
	}

	while(r1)
	{
		ret = r1->val+carry;
		carry = ret / 10;
		ret = ret % 10;
		insert_list_val(&sum, ret);
		r1 = r1->next;
	}

	while(r2)
	{
		ret = r2->val+carry;
		carry = ret / 10;
		ret = ret % 10;
		insert_list_val(&sum, ret);
		r2 = r2->next;
	}

	if(carry != 0)
		insert_list_val(&sum, carry);

	return sum;
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
	node *h1 = NULL;
	node *h2 = NULL;
	
	insert_list_val(&h1, 4);
	insert_list_val(&h1, 3);
	insert_list_val(&h1, 9);
	insert_list_val(&h1, 9);
	insert_list_val(&h2, 8);
	insert_list_val(&h2, 8);
	insert_list_val(&h2, 8);
	
	printf("NUM 1:\n");
	traverse_list(h1);
	printf("NUM 2:\n");
	traverse_list(h2);

	node *sum = add_list(h1, h2);
	printf("SUM:\n");
	traverse_list(sum);

	return 0;		
}
