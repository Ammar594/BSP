#include <arch/bsp/thread_managment.h>
#include <arch/bsp/uart.h>
#define sp_offset 0x26000

void memcpy(void *dest, const void *src, unsigned int size) {
        char *d=dest;
        const char *s=src;
        
        for(unsigned int i = 0;i<size;i++) {
            *d=*s;
            d--;
		    s++;
        }
}

struct tcb tcbs[32]; // 32 threads possible
struct tcb *current_thread;

void thread_create(void (*func)(void *), const void * args,unsigned int args_size){
    for (int i = 0; i < 32; i++){ // iterate through tcbs 
        if(tcbs[i].state == FINISHED){ // if free thread holder ...
            tcbs[i].state = READY;
            tcbs[i].regs[15] = (unsigned int )&func; // setting jump address -> programm counter
            memcpy((void *)(sp_offset + (i * 1000)),args,args_size); // copy arguemnts to stack
            tcbs[i].regs[13]= sp_offset + (i * 1000) - args_size; // setting stack pointer 
            break;
        }
    }
}

void init_tcbs(){
    for(int i = 0;i<32;i++){
        tcbs[i].state = FINISHED; // initialize as finished -> free to create new thread
        tcbs[i].thread_ID = i + 1;
        for (int j = 0; j < 16; j++)
        {
            tcbs[i].regs[j]=0x0;
        }
        if(i == 31) 
            tcbs[i].rq_next = &tcbs[0];
        else
            tcbs[i].rq_next = &tcbs[i+1];
        if(i == 0) 
            tcbs[i].rq_prev = &tcbs[31];
        else
            tcbs[i].rq_prev = &tcbs[i-1];    
    }
}

void save_regs(){
}

void thread_switch(){
}

void idle_thread(){
    while(1){
    }
}
