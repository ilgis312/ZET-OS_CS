#ifndef __THREADS_H__
#define __THREADS_H__

#include <list.h>


enum thread_state {
	THREAD_ACTIVE,
	THREAD_BLOCKED,
	THREAD_FINISHED,
	THREAD_DEAD
};


struct thread {
	struct list_head ll;
	uintptr_t stack_phys;
	int stack_order;
	enum thread_state state;
	void *context;
	int retval;
};


struct thread *__thread_create(int stack_order, int (*fptr)(void *), void *arg);
struct thread *thread_create(int (*fptr)(void *), void *arg);

void thread_start(struct thread *thread);
struct thread *thread_current(void);

void thread_exit(int ret);
void thread_join(struct thread *thread, int *ret);
void thread_destroy(struct thread *thread);

void schedule(void);
void scheduler_tick(void);
void scheduler_idle(void);
void scheduler_setup(void);

#endif /*__THREADS_H__*/