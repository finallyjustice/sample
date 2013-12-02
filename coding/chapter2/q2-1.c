/** File:        	q2-1.c
 ** Author:			Dongli Zhang
 ** Contact:		dongli.zhang0129@gmail.com
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

/*  Q2.1. Write code to remove duplicates from an unsorted linked list 
 *  FOLLOW UP
 *  How would you solve this problem if a temporary buffer is not allowed?  
 */

/* usage: gcc q2-1.c -o q2-1 */

#include <stdio.h>
#include <string.h>
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

/* solution with two pointer */
void detect_dup_tp(node_t *head)
{
	node_t *fst = head;
	node_t *sec;

	while(fst)
	{
		sec = head;
		while(sec)
		{
			if(fst!=sec && fst->val==sec->val)
			{
				printf("Duplicate Value: %d\n", fst->val);
				break;
			}
			sec = sec->next;
		}
		fst = fst->next;
	}
}

int main(int argc, char **argv)
{
	node_t *n;
	node_t *head = NULL;

	n = (node_t *)malloc(sizeof(node_t));
	n->val = 1;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 5;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 10;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 7;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 1;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 1;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 5;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 9;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 19;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 18;
	insert_list(&head, n);
	
	n = (node_t *)malloc(sizeof(node_t));
	n->val = 10;
	insert_list(&head, n);

	traverse_list(head);

	printf("Solution with two pointers:\n");
	detect_dup_tp(head);

	return 1;
}


