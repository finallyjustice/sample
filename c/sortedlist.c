#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
}node;

node* init_list(int val)
{
    node *list = (node *)malloc(sizeof(node));
    list->val = val;
    list->next = NULL;
}

void insert_list(node **list, int val)
{
    node *tmp = *list;
    node *n = (node *)malloc(sizeof(node));
    n->val = val;
  
	if(*list == NULL)
	{
		n->next = NULL;
		*list = n;
		return;
	}

	if(val <= tmp->val)
	{
		n->next = tmp;
		*list = n;
		return;
	}

    while(tmp && tmp->next && val>tmp->next->val)
    {
        tmp = tmp->next;
    }
    
    n->next = tmp->next;
    tmp->next = n;
}

void traverse_list(node *list)
{
    node *tmp = list;
    while(tmp)
    {
        printf("Value: %d\n", tmp->val);
        tmp = tmp->next;
    }
}

int main(int arrgc, char **argv)
{
	node *head = init_list(5);
	insert_list(&head, 4);
	insert_list(&head, 6);
	insert_list(&head, 3);
	insert_list(&head, 7);
	insert_list(&head, 2);
	insert_list(&head, 8);
    insert_list(&head, 1);
	traverse_list(head);
}
