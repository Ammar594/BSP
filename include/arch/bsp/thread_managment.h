#ifndef THREAD_MANAGMENT_H 
#define THREAD_MANAGMENT_H
#include <arch/bsp/kprintf.h>
enum thread_state{ // thread state 
    READY,
    RUNNING,
    WAITING,
    FINISHED
};

struct tcb {
    enum thread_state state;   
    int thread_ID;
    unsigned int stack_offset;
    unsigned int regs[16];    
    struct tcb *rq_prev;
    struct tcb *rq_next;
};

void init_tcbs(); // init thread with zeroes

void idle_thread();

void thread_switch();
void start_thread();
int thread_create(void (*func)(void *), const void * args,unsigned int args_size);
#endif