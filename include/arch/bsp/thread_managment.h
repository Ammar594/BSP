#ifndef THREAD_MANAGMENT_H 
#define THREAD_MANAGMENT_H
enum thread_state{ // thread state 
    READY,
    RUNNING,
    WAITING,
    FINISHED
};
struct tcb {
thread_state;   
int thread_ID;    
struct tcb *rq_prev;
struct tcb *rq_next;
};
struct tcb tcbs[32]; // 32 threads possible
struct tcb *runqueue;
void thread_create(void (*func)(void *), const void * args,unsigned int args_size);
#endif