#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    int val;
    struct node *next;
}node_t;

void print_list(node_t *list)
{
    node_t *tmp = list;
    while(tmp)
    {
        printf("Val: %d\n", tmp->val);
        tmp = tmp->next;
    }
}

void insert_head(node_t **list, node_t *n)
{
    n->next = *list;
    *list = n;
}

void insert_tail(node_t **list, node_t *n)
{
    node_t *tmp = *list;
    if(*list == NULL)
    {
        *list = n;
        n->next = NULL;
        return;
    }
    
    while(tmp->next)
        tmp = tmp->next;
    n->next = NULL;
    tmp->next = n;
}

void insert_sorted(node_t **list, node_t *n)
{
    node_t *tmp = *list;
    if(*list==NULL || n->val<=tmp->val)
    {
        n->next = *list;
        *list = n;
        return;
    }
    
    while(tmp->next && n->val>tmp->next->val)
        tmp = tmp->next;
    n->next = tmp->next;
    tmp->next = n;
}

node_t* search_list(node_t *list, int val)
{
    node_t *tmp = list;
    node_t *ret;
    while(tmp && tmp->val!=val)
        tmp = tmp->next;
    ret = tmp;
    return ret;   
}

void reverse_list_iter(node_t **list)
{
    node_t *revl = NULL;
    node_t *tmp = *list;
    node_t *n;
    while(tmp)
    {
        n = tmp;
        tmp = tmp->next;
        insert_head(&revl, n);
    }
    *list = revl;
}

void reverse_list_recv(node_t **list)
{
    node_t *tmp = *list;
    node_t *n = tmp->next;
    if(n == NULL)
        return;
    reverse_list_recv(&n);
    *list = n;
    tmp->next->next = tmp;
    tmp->next = NULL;
}

void sort_list(node_t **list)
{
    node_t *srtl = NULL;
    node_t *tmp = *list;
    node_t *n;
    while(tmp)
    {
        n = tmp;
        tmp = tmp->next;
        insert_sorted(&srtl, n);
    }
    *list = srtl;
}

void delete_list(node_t **list, int val)
{
    node_t *tmp = *list;
    if(*list==NULL)
        return;
    if(tmp->val == val)
    {
        *list = tmp->next;
        free(tmp);
        return;
    }
    
    while(tmp->next)
    {
        if(tmp->next->val == val)
        {
            node_t *dn = tmp->next;
            tmp->next = tmp->next->next;
            free(dn);
            return;
        }
        tmp = tmp->next;
    }
}

node_t* merge_list(node_t *l1, node_t *l2)
{
    node_t *t1 = l1;
    node_t *t2 = l2;
    node_t *list = NULL;
    node_t *n;
    while(t1 && t2)
    {
        if(t1->val <= t2->val)
        {
            n = t1;
            t1 = t1->next;
        }
        else
        {
            n = t2;
            t2 = t2->next;
        }
        insert_head(&list, n);
    }
    
    while(t1)
    {
        n = t1;
        t1 = t1->next;
        insert_head(&list, n);
    }
    
    while(t2)
    {
        n = t2;
        t2 = t2->next;
        insert_head(&list, n);
    }
    reverse_list_iter(&list);
    
    return list;
}

node_t*  reverse_k_nodes(node_t *list, int k)
{
	if(list == NULL || k == 0)
		return;

	node_t *tmp = list;
	node_t *head = list;
	node_t *revl = NULL;;

	int count;
	int iter;

	count = 0;
	while(tmp && count < k)
	{
		count++;
		node_t *n = tmp;
		tmp = tmp->next;
		insert_head(&revl, n);
	}

	head->next = reverse_k_nodes(tmp, k);
	return revl;
}

void delete_nth_node(node_t **list, int n)
{
	if(n == 0)
		return;

    node_t *t1 = *list;
    node_t *t2 = *list;
    
    int count = n;
	node_t *pt;
    while(count > 0)
    {
        if(t1 == NULL)
            return;
        t1 = t1->next;
        count--;
    }
    while(t1)
    {
		pt = t2;
        t2 = t2->next;
        t1 = t1->next;
    }
    
	if(t2 == *list)
		*list = t2->next;
	else
		pt->next = pt->next->next;
	free(t2);
}

node_t* add_list(node_t *l1, node_t *l2)
{
	node_t *ret = NULL;
	reverse_list_iter(&l1);
	reverse_list_iter(&l2);
	node_t *t1 = l1;
	node_t *t2 = l2;
	int carry = 0;
	int sum;
	int digit;
	int v1;
	int v2;

	while(t1 || t2)
	{
		v1 = 0;
		v2 = 0;
		if(t1)
		{
			v1 = t1->val;
			t1 = t1->next;
		}

		if(t2)
		{
			v2 = t2->val;
			t2 = t2->next;
		}

		sum = v1 + v2 + carry;
		digit = sum % 10;
		carry = sum / 10;

		node_t *n = (node_t *)malloc(sizeof(node_t));
		n->val = digit;
		insert_head(&ret, n);
	}

	if(carry > 0)
	{
		node_t *n = (node_t *)malloc(sizeof(node_t));
		n->val = carry;
		insert_head(&ret, n);
	}

	return ret;
}

int main(int argc, char **argv)
{
    node_t *l1 = NULL;
    node_t *l2 = NULL;
    node_t *n;
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 0;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 1;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 2;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 3;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 4;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 5;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 6;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 7;
    insert_tail(&l1, n);
    
    n = (node_t *)malloc(sizeof(node_t));
    n->val = 8;
    insert_tail(&l1, n);
    
	n = (node_t *)malloc(sizeof(node_t));
    n->val = 9;
    insert_tail(&l1, n);

    print_list(l1);

	printf("After:\n");
	node_t *ret = reverse_k_nodes(l1, 3);
	print_list(ret);
}
