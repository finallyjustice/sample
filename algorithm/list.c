#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int val;
	struct node *next;
} node_t;

void list_print(node_t *head)
{
	node_t *tmp = head;
	while(tmp)
	{
		printf("%d ", tmp->val);
		tmp = tmp->next;
	}
	printf("\n");
}

void list_insert_head_val(node_t **head, int val)
{
	node_t *n = (node_t *)malloc(sizeof(int));
	n->val = val;

	if(*head == NULL)
		n->next = NULL;
	else
		n->next = *head;
	*head = n;
}

void list_insert_tail_val(node_t **head, int val)
{
	node_t *n = (node_t *)malloc(sizeof(int));
	n->val = val;
	n->next = NULL;

	if(*head == NULL)
	{
		*head = n;
	}
	else
	{
		node_t *tmp = *head;
		while(tmp->next)
			tmp = tmp->next;
		tmp->next = n;
	}
}

node_t* reverse_k_node(node_t *head, int k)
{
	if(head == NULL)
		return NULL;

	int i = 0;
	node_t *cur = head;
	node_t *last = head;
	node_t *nh = NULL;
	
	while(i<k && cur)
	{
		node_t *n = cur;
		cur = cur->next;
		
		if(nh == NULL)
			n->next = NULL;
		else
			n->next = nh;
		nh = n;

		i++;
	}

	head = cur;
	last->next = reverse_k_node(head, k);

	return nh;
}

int main(int argc, char **argv)
{
	node_t *head = NULL;

	list_insert_head_val(&head, 1);
	list_insert_head_val(&head, 2);
	list_insert_head_val(&head, 3);
	list_insert_head_val(&head, 4);
	list_insert_head_val(&head, 5);

	list_insert_tail_val(&head, 6);
	list_insert_tail_val(&head, 7);
	list_insert_tail_val(&head, 8);
	list_insert_tail_val(&head, 9);
	list_insert_tail_val(&head, 10);

	list_print(head);

	node_t *nh = reverse_k_node(head, 3);

	list_print(nh);
	return 0;
}
