/** File:           q2-4.c
 ** Author:         Dongli Zhang
 ** Contact:        dongli.zhang0129@gmail.com
 **
 ** Copyright (C) Dongli Zhang 2013
 **
 ** This program is free software;  you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY;  without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 ** the GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program;  if not, write to the Free Software 
 ** Foundation, 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */


/*  Write code to partition a linked list around a value x 
 *  such that all nodes less than x come before all nodes
 *  greater or equal to x
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct node
{
	int val;
	struct node *next;
}node_t;

void insert_list(node_t **head, node_t *n)
{
	n->next = *head;
	*head = n;
}

void traverse_list(node_t *head)
{
	node_t *tmp = head;
	while(tmp)
	{
		printf("Value: %d\n", tmp->val);
		tmp = tmp->next;
	}
}

void partition(node_t **head, int x)
{
	node_t *px = *head;
	node_t *h = px;
	node_t *t = px;

	node_t *tmp;
	node_t *cur;
	tmp = (*head)->next;
	while(tmp)
	{
		cur = tmp;
		tmp = tmp->next;
		if(cur->val < x)
		{
			//add tmp before x
			cur->next = h;
			h = cur;
		}
		else
		{
			//add tmp after x
			t->next = cur;
			cur->next = NULL;
			t = cur;
		}
	}

	*head = h;
}

int main(int argc, char **argv)
{
	node_t *n;
	node_t *head = NULL;
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 5;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 10;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 2;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 9;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 8;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 3;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 4;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 11;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 0;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 13;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 1;
	insert_list(&head, n);

	printf("Before Partition:\n");
	traverse_list(head);

	printf("After Partition:\n");
	partition(&head, 5);
	traverse_list(head);
	
	return 1;
}
