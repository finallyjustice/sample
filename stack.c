#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node_t
{
    int val;
    struct node_t *next;
}node;

typedef struct stack_t
{
    node *top;
    int num;
}stack;

stack* init_stack()
{
    stack *s = (stack *)malloc(sizeof(stack));
    s->top = NULL;
    s->num = 0;
}

void push_stack(stack *s, int val)
{
    node *n = (node *)malloc(sizeof(node));
    n->val = val;
    n->next = s->top;
    s->top = n;
	s->num++;
}

int pop_stack(stack *s)
{
	if(s->num == 0)
	{
		printf("Stack is emptry\n");
		return -1;
	}

    int ret = s->top->val;
    node *tmp = s->top;
    s->top = s->top->next;
	s->num--;
    free(tmp);
    return ret;
}

int top_stack(stack *s)
{
    return s->top->val;
}

int is_empty_stack(stack *s)
{
	return s->num<=0;
}

int main(int argc, char **argv)
{
    stack *s = init_stack();
	printf("If emptry: %d\n", is_empty_stack(s));
    push_stack(s, 10);    printf("pushed 10\n");
    push_stack(s, 9);    printf("pushed 9\n");
    push_stack(s, 8);    printf("pushed 8\n");
    push_stack(s, 7);    printf("pushed 7\n");
    printf("poped: %d\n", pop_stack(s));    
    printf("top: %d\n", top_stack(s));
    push_stack(s, 6);    printf("pushed 6\n");
    push_stack(s, 5);    printf("pushed 5\n");
    printf("top: %d\n", top_stack(s));
	printf("current stack size: %d\n", s->num);
	printf("If empty: %d\n", is_empty_stack(s));
    return 0;
}
