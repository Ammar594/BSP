#ifndef THREAD_MANAGMENT_H 
#define THREAD_MANAGMENT_H
#include <arch/bsp/kprintf.h>
#include <stdint.h>
enum thread_state{ // thread state 
    READY,
    RUNNING,
    WAITING,
    FINISHED
};

struct tcb {
    enum thread_state state;   
    int tid;
    uint32_t regs[13]; // R0-R12
    uint32_t sp; // SP
    uint32_t lr; // LR
    uint32_t pc;
    uint32_t SPSR;    // SPSR-CPSR
};

struct tmp{
    uint32_t sp;
    uint32_t lr;
    uint32_t pc;
    uint32_t regs[13];
};

void start_thread();
void store_regs();
void init_tcbs(); // init thread with zeroes
void start_idle_thread();
void idle_thread();
void exit();
void thread_switch();
void switch_thread();
int thread_create(void (*func)(void *), const void * args,unsigned int args_size);
int thread_create1(void (*func)(void *));
#endif