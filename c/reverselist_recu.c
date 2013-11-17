#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
}node;

void insert_list_end(node **head, node *n)
{
    node *tmp = *head;
    
    if(tmp == NULL)
    {
        *head = n;
        n->next = NULL;
        return;
    }
    
    while(tmp->next)
    {
        tmp = tmp->next;
    }
    tmp->next = n;
    n->next = NULL;
}

void reverse_list(node **head)
{
    node *cur = *head;
    if(cur->next == NULL)
    {
        return;
    }
    
    node *sub = cur->next;
    reverse_list(&sub);
    insert_list_end(&sub, cur);
	*head = sub;
}

void traverse_list(node *head)
{
	node *tmp = head;	
	while(tmp)
	{
		printf("value: %d\n", tmp->val);
		tmp = tmp->next;
	}
}

int main(int argc, char **argv)
{
	node *n;
	node *head =NULL;

	n = (node *)malloc(sizeof(node));
	n->val = 1;
	insert_list_end(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 2;
	insert_list_end(&head, n);
	
	n = (node *)malloc(sizeof(node));
	n->val = 3;
	insert_list_end(&head, n);

	n = (node *)malloc(sizeof(node));
	n->val = 4;
	insert_list_end(&head, n);

	n = (node *)malloc(sizeof(node));
	n->val = 5;
	insert_list_end(&head, n);

	reverse_list(&head);
	traverse_list(head);

	return 0;
}
