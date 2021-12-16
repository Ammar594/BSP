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

int thread_create(void (*func)(void *), const void * args,unsigned int args_size){
    for (int i = 0; i < 32; i++){ // iterate through tcbs 
        if(tcbs[i].state == FINISHED){ // if free thread holder ...
            tcbs[i].state = READY;
            tcbs[i].regs[15] = (unsigned int)func; // setting jump address -> programm counter
            memcpy((void *)(sp_offset + (i * 1000)),args,args_size); // copy arguemnts to stack
            tcbs[i].regs[13]= sp_offset + (i * 1000) - args_size; // setting stack pointer
            return tcbs[i].thread_ID;
        }
    }
    return -1;
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

void idle_thread(){
    while(1){
    }
}

void start_thread(){
    // setup register
    unsigned int * t = tcbs[0].regs;
    asm volatile("LDR R1, [%0]" ::"r"(*t));
    asm volatile("LDR R2, [%0]" ::"r"(*(t+4)));
    asm volatile("LDR R3, [%0]" ::"r"(*(t+8)));
    //asm volatile("LDR R4, [%0]" ::"r"(*(t+12)));
    //asm volatile("LDR R5, [%0]" ::"r"(*(t+16)));
    // asm volatile("LDR R6, [%0]" ::"r"(*(t+20)));
    // asm volatile("LDR R7, [%0]" ::"r"(*(t+24)));
    // asm volatile("LDR R8, [%0]" ::"r"(*(t+28)));
    // asm volatile("LDR R9, [%0]" ::"r"(*(t+32)));
    // asm volatile("LDR R10, [%0]" ::"r"(*(t+36)));
    // asm volatile("LDR R11, [%0]" ::"r"(*(t+40)));
    //asm volatile("LDR R12, [%0]" ::"r"(*(t+44)));

    // asm volatile("LDR R2, [%0]" ::"r"((unsigned int)tcbs[0].regs[2]));
    // asm volatile("LDR R3, [%0]" ::"r"((unsigned int)tcbs[0].regs[3]));
    // asm volatile("LDR R4, [%0]" ::"r"((unsigned int)tcbs[0].regs[4]));
    // asm volatile("LDR R5, [%0]" ::"r"((unsigned int)tcbs[0].regs[5]));
    // asm volatile("LDR R6, [%0]" ::"r"((unsigned int)tcbs[0].regs[6]));
    // asm volatile("LDR R7, [%0]" ::"r"((unsigned int)tcbs[0].regs[7]));
    // asm volatile("LDR R8, [%0]" ::"r"((unsigned int)tcbs[0].regs[8]));
    // asm volatile("LDR R9, [%0]" ::"r"((unsigned int)tcbs[0].regs[9]));
    // asm volatile("LDR R10, [%0]" ::"r"((unsigned int)tcbs[0].regs[10]));
    // asm volatile("LDR R11, [%0]" ::"r"((unsigned int)tcbs[0].regs[11]));
    // asm volatile("LDR R12, [%0]" ::"r"((unsigned int)tcbs[0].regs[12]));
    //setup S
    // asm volatile("LDR R0, [%0]"::"r"(tcbs[0].regs[13]));
    // asm volatile("MSR SP_usr, R0");
    // //setup LR
    // asm volatile("LDR R0, [%0]"::"r"(tcbs[0].regs[14]));
    // asm volatile("MSR LR_usr, R0");
    // //switch to user mode
    
    // asm volatile("MOV R0, #0x10");
    // asm volatile("MSR CPSR_cxfs, R0");
    //setup R0
    //asm volatile("LDR R0, [%0]" ::"r"());
    //jump to thread code
    asm volatile("LDR LR, [%0]"::"r"(&idle_thread));
    asm volatile("MOV PC, LR");
}