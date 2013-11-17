#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
}node;

void insert_list_front(node **head, node *n)
{
    node *tmp = *head;
    n->next = tmp;
    *head = n;
}

void reverse_list(node **head)
{
    node *tmp = *head;
    node *new_head = NULL;
    node *new_node;
    while(tmp)
    {
        new_node = tmp;
        tmp = tmp->next;
        insert_list_front(&new_head, new_node);
    }
    
    *head = new_head;
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
    n->val = 1;
    insert_list_front(&head, n);
    
    
    n = (node *)malloc(sizeof(node));
    n->val = 2;
    insert_list_front(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 3;
    insert_list_front(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 4;
    insert_list_front(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 5;
    insert_list_front(&head, n);

	reverse_list(&head);
	traverse_list(head);
}
