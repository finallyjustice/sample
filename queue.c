#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
}node;

typedef struct queue_t
{
    node *head;
    node *tail;
    int num;    
}queue; 

queue* init_queue()
{
    queue *q = (queue *)malloc(sizeof(queue));
    q->head = NULL;
    q->tail = NULL;
    q->num = 0;
}

int is_empty_queue(queue *q)
{
    return q->num<=0;
}

void enqueue(queue *q, int val)
{
    node *n = (node *)malloc(sizeof(node));
    n->val = val;
    n->next = NULL;
    
    q->num++;
    
    if(q->num == 1)
    {
        q->head = n;
        q->tail = n;
        return;
    }
    
    q->tail->next = n;
    q->tail = n;
}

int dequeue(queue *q)
{
    int ret = q->head->val;
    node *tmp = q->head;
    q->head = q->head->next;
    
    q->num--;
    if(q->num == 0)
    {
        q->tail = NULL;
    }    
    
    free(tmp);
	return ret;
}

int front_queue(queue *q)
{
    return q->head->val;
}

int end_queue(queue *q)
{
    return q->tail->val;
}

int main(int argc, char **argv)
{
	queue *q = init_queue();
	enqueue(q, 1);
	enqueue(q, 2);
	enqueue(q, 3);
	printf("head: %d. tail: %d\n", front_queue(q), end_queue(q));
	printf("dequeue: %d\n", dequeue(q));
	printf("dequeue: %d\n", dequeue(q));
	printf("dequeue: %d\n", dequeue(q));
	enqueue(q, 4);
	enqueue(q, 5);
	printf("dequeue: %d\n", dequeue(q));
	printf("dequeue: %d\n", dequeue(q));
    return 0;
}
