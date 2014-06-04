#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

struct student
{
	int id;
	char name[30];
	struct list_head list;
	unsigned long score;
};

int main(int argc, char **argv)
{
	LIST_HEAD(head);
	
	struct student *s1 = (struct student *)malloc(sizeof(struct student));
	struct student *s2 = (struct student *)malloc(sizeof(struct student));
	struct student *s3 = (struct student *)malloc(sizeof(struct student));
	struct student *s4 = (struct student *)malloc(sizeof(struct student));

	// information for student 1
	s1->id = 1001;
	sprintf(s1->name, "name1");
	s1->score = 91;
	
	// information for student 1
	s2->id = 1002;
	sprintf(s2->name, "name2");
	s2->score = 92;
	
	// information for student 1
	s3->id = 1003;
	sprintf(s3->name, "name3");
	s3->score = 93;
	
	// information for student 1
	s4->id = 1004;
	sprintf(s4->name, "name4");
	s4->score = 94;

	list_add_tail(&(s1->list), &head);
	list_add_tail(&(s2->list), &head);
	list_add_tail(&(s3->list), &head);
	list_add_tail(&(s4->list), &head);

	struct student *s;
	list_for_each_entry(s, &head, list)
	{
		printf("id(%d), name(%s), score(%lu)\n", 
				s->id, s->name, s->score);
	}

	free(s1);
	free(s2);
	free(s3);
	free(s4);

	return 0;
}
