#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
}node;

void reverse_list(node **head)
{
    node *first = *head;
    if(first->next == NULL) return;
    node *sub = first->next;
    reverse_list(&sub);
    first->next->next = first;
    first->next = NULL;
    *head = sub;
}

void insert_list(node **head, node *n)
{
    node *tmp = *head;
    n->next = tmp;
    *head = n;
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
    node *head = NULL;
    node *n;
    
    n = (node *)malloc(sizeof(node));
    n->val = 1;
    insert_list(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 2;
    insert_list(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 3;
    insert_list(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 4;
    insert_list(&head, n);
    
    n = (node *)malloc(sizeof(node));
    n->val = 5;
    insert_list(&head, n);
   
	reverse_list(&head);
    traverse_list(head);
}
