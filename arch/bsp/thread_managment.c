#include <arch/bsp/thread_managment.h>
#include <arch/bsp/uart.h>
#include <stdint.h>
#include <arch/bsp/userthread.h>
#define sp_offset 0xEFFFF0

struct tcb tcbs[32]; // 32 threads possible
struct tcb *current_thread;

int thread_create(void (*func)(void *), const void * args,unsigned int args_size){
    for (int i = 0; i <= 31; i++){ // iterate through tcbs 
        if(tcbs[i].state == FINISHED){ // if free thread holder ...
            tcbs[i].state = READY;
            tcbs[i].pc = (uint32_t)func; // setting jump address -> programm counter
            unsigned int temp;
            asm volatile("push {r0-r12}");
            asm volatile("mov %0, sp":"=r"(temp));
            asm volatile("mov sp, %0"::"r"(tcbs[i].sp));
            for(unsigned int j=0;j<args_size;j++){
                asm volatile("push {%0}"::"r"(args));
                args++;
            }
            asm volatile("push {%0}"::"r"(args));
            asm volatile("mov %0, sp":"=r"(tcbs[i].sp));
            asm volatile("mov sp, %0"::"r"(temp));
            asm volatile("pop {r0-r12}");
            return tcbs[i].tid;
        }
    }
    return -1;
}

int thread_create1(void (*func)()){
    for (int i = 0; i < 32; i++){ // iterate through tcbs 
        if(tcbs[i].state == FINISHED){ // if free thread holder ...
            tcbs[i].state = READY;
            tcbs[i].pc = (uint32_t)func; // setting jump address -> programm counter
            tcbs[i].sp= (uint32_t)sp_offset - (i * 1000); // setting stack pointer
            return tcbs[i].tid;
        }
    }
    return -1;
}

void init_tcbs(){
    for(int i = 0;i<32;i++){
        tcbs[i].state = FINISHED; // initialize as finished -> free to create new thread
        tcbs[i].tid = i;
        tcbs[i].sp =(uint32_t )sp_offset - (i * 1000);
        tcbs[i].lr = 0;
    }
}

void idle_thread(void){
    kprintf("idle thread ...\n");
    while(1){
        kprintf("idle threa ...\n");
        for(int j =0;j < 5000000;j++)
            kprintf("\0");
    }
}

void exit(){
    switch_thread(1); // switch to next thread
    start_thread();
}

void store_regs(struct tmp * temp){
   for(int i = 0;i<=12;i++){
       tcbs[current_thread->tid].regs[i] = temp->regs[i]; 
   }
   tcbs[current_thread->tid].pc = temp->pc;
   tcbs[current_thread->tid].lr = temp->lr;
   tcbs[current_thread->tid].sp = temp->sp;
}

void start_idle_thread(){ // initilaize idle_thread
    tcbs[31].pc = (uint32_t )&idle_thread;
    tcbs[31].tid = 31;
    tcbs[31].state = RUNNING;
    current_thread = &tcbs[31];
    asm volatile("MSR CPSR, 0x10"); 
    start_thread();
}
void start_thread(){
    asm volatile("mov sp, %0"::"r"(current_thread->sp):); // change stack pointer to current thread
    asm volatile("push {%0}"::"r"(current_thread->pc):);
    asm volatile("push {%0}"::"r"(current_thread->lr):);
    asm volatile("push {%0}"::"r"(current_thread->regs[0]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[1]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[2]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[3]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[4]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[5]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[6]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[7]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[8]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[9]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[10]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[11]):);
    asm volatile("push {%0}"::"r"(current_thread->regs[12]):);
    
    asm volatile("pop {r12}\n"
                 "pop {r11}\n"
                 "pop {r10}\n"
                 "pop {r9}\n"
                 "pop {r8}\n"
                 "pop {r7}\n"
                 "pop {r6}\n"
                 "pop {r5}\n"
                 "pop {r4}\n"
                 "pop {r3}\n"
                 "pop {r2}\n"
                 "pop {r1}\n"
                 "pop {r0}\n"
                 "pop {lr}\n"
                 "add r0, sp, #4\n"
                 "pop {pc}\n"
                );
}

void switch_thread(int toggle){
    for(int i = current_thread->tid;i<32;i++){
        if(tcbs[i].state == READY || tcbs[i].state == WAITING){
            if(toggle){
                 current_thread -> state = FINISHED;
            }
            else
                current_thread -> state = WAITING;
            current_thread = &tcbs[i];
            break;
        }
    }
    for(int i = 0;i<current_thread->tid;i++){
        if(tcbs[i].state == READY || tcbs[i].state == WAITING){
            if(toggle){
                 current_thread -> state = FINISHED;
            }
            else
                current_thread -> state = WAITING;
            current_thread = &tcbs[i];
            break;
        }
    }
}