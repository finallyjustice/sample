#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    void *data;
    struct node_t *next;
}node;

int compare_int(void *data1, void *data2)
{
    int v1 = *(int *)data1;
    int v2 = *(int *)data2;
    
    if(v1 > v2) return 1;
    else if(v1 == v2) return 0;
    else return -1;
}

void print_int(void *data)
{
	printf("Value: %d\n", *(int *)data);
}

node* init_list(void *data, size_t size)
{
    node *n = (node *)malloc(sizeof(node));
    n->data = (void *)malloc(size);
    memcpy(n->data, data, size);
    n->next = NULL;
    return n;
}

void insert_list(node **list, void *data, size_t size)
{
    node *n = (node *)malloc(sizeof(node));
    n->data = (void *)malloc(size);
    memcpy(n->data, data, size);
    n->next = *list;
    *list = n;
}

void traverse_list(node *list, void (*f)(void *))
{
    node *tmp = list;
    while(tmp)
    {
        (*f)(tmp->data);
        tmp = tmp->next;
    }
}

node* search_list(node *list, void *data, int (*f)(void *d1, void *d2))
{
    node *tmp = list;
    while(tmp)
    {
        if((*f)(tmp->data, data) == 0)
        {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void delete_list(node **list, node *n)
{
    node *tmp = *list;
    if(tmp == NULL) return;
	if(tmp == n)
	{
		*list = tmp->next;
		goto clean;
	}
    while(tmp->next != n)
    {
        tmp = tmp->next;
    }
    tmp->next = tmp->next->next;

clean:
    free(n);
}

int main(int argc, char **argv)
{
    int value;
	value = 10;	node *head = init_list(&value, sizeof(int));
	value = 9;	insert_list(&head, &value, sizeof(int));
	value = 8;	insert_list(&head, &value, sizeof(int));
	value = 7;	insert_list(&head, &value, sizeof(int));
	value = 6;	insert_list(&head, &value, sizeof(int));
	value = 5;	insert_list(&head, &value, sizeof(int));
	value = 4;	insert_list(&head, &value, sizeof(int));
	value = 3;	insert_list(&head, &value, sizeof(int));
	traverse_list(head, print_int);

	value = 10;
	node *res = search_list(head, &value, compare_int);
	if(res == NULL)
	{
		printf("No result!\n");
		return 1;
	}
	print_int(res->data);

	delete_list(&head, res);
	printf("After Delete:\n");
	traverse_list(head, print_int);

    return 1;
}
