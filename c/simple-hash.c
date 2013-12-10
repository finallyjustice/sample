#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 10

typedef struct node
{
	int val;
	struct node *next;
}node_t;

typedef struct hash
{
	int size;
	node_t **list;
}hash_t;

hash_t* init_hash(int size)
{
	hash_t *h = (hash_t *)malloc(sizeof(hash_t));
	h->size = size;
	h->list = (node_t **)malloc(sizeof(node_t*)*size);
	int c;
	for(c=0; c<size; c++)
		h->list[c] = NULL;

	return h;
}

void insert_list(node_t **list, int key)
{
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->val = key;
	n->next = *list;
	*list = n;
}

void delete_list(node_t **list, int key)
{
	node_t *tmp = *list;
	if(tmp->val == key)
	{
		*list = (*list)->next;
		free(tmp);
		return;
	}
	while(tmp->next)
	{
		if(tmp->next->val == key)
		{
			node_t *del = tmp->next;
			tmp->next = tmp->next->next;
			free(del);
			return;
		}
		tmp = tmp->next;
	}
}

void hash_put(hash_t *h, int key)
{
	int idx = key % h->size;
	insert_list(&(h->list[idx]), key);
}

int hash_get(hash_t *h, int key)
{
	int idx = key % h->size;
	node_t *tmp = h->list[idx];
	while(tmp)
	{
		if(key == tmp->val)
			return 1;
		tmp = tmp->next;
	}
	return 0;
}

void hash_remove(hash_t *h, int key)
{
	int idx = key % h->size;
	delete_list(&(h->list[idx]), key);
}

void hash_traverse(hash_t *h)
{
	int c;
	for(c=0; c<h->size; c++)
	{
		node_t *tmp = h->list[c];
		printf("Key %d: ", c);
		while(tmp)
		{
			printf("%d ", tmp->val);
			tmp = tmp->next;
		}
		printf("\n");
	}
	printf("\n");
}

int main(int argc, char **argv)
{
	hash_t *h = init_hash(5);
	hash_put(h, 1);
	hash_put(h, 11);
	hash_put(h, 5);
	hash_put(h, 6);
	hash_put(h, 7);
	hash_put(h, 8);
	hash_put(h, 21);
	hash_put(h, 33);
	hash_put(h, 103);
	hash_put(h, 9);

	hash_traverse(h);
	
	hash_remove(h, 6);
	hash_remove(h, 9);
	
	hash_traverse(h);
	
	hash_put(h, 9);
	hash_traverse(h);

	hash_remove(h, 7);
	hash_remove(h, 9);
	hash_traverse(h);

	printf("1 : %d\n", hash_get(h, 1));	
	printf("11: %d\n", hash_get(h, 11));	
	printf("7 : %d\n", hash_get(h, 7));	
	printf("6 : %d\n", hash_get(h, 6));	
	printf("9 : %d\n", hash_get(h, 9));	
	printf("0 : %d\n", hash_get(h, 0));	
}
