#ifndef __TPOOL_H__
#define __TPOOL_H__

#include <pthread.h>

typedef struct tpool_job
{
	void*			 (*routine)(void *);
	void			 *arg;
	struct tpool_job *next;
}tpool_job_t;

typedef struct tpool
{
	int max_thr;
	pthread_t *tid;
	int *pid;
	tpool_job_t *queue_head;
	tpool_job_t *queue_tail;
	pthread_mutex_t queue_mutex;
	pthread_cond_t queue_ready;
}tpool_t;

int tpool_create(int max_thr);
void * do_thread(void *arg);
int tpool_add_job(void* (*routine)(void *), void *arg);

#endif
