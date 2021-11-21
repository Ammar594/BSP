#include <arch/bsp/trampoline.h>
#include <arch/bsp/kprintf.h>
void initStacks(){    
/*setup the stack for IRQ*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n"
                 "orr r0, r0, #0x000000D2\n" // mode change 11010010
                 "msr cpsr, r0\n" // mode -> IRQ
                 "ldr r13, =0x201F4\n" // initualize SP
                );
/*setup the stack for FIQ*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n" // test could be only 16 bit
                 "orr r0, r0, #0x000000D1\n" // test
                 "msr cpsr, r0\n"
                 "ldr r13, =0x203E8"
                );
/*setup the stack for Prefetch Abort*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n" 
                 "orr r0, r0, #0x000000D7\n" // mode change 11000010
                 "msr cpsr, r0\n" // mode -> IRQ
                 "ldr r13, =0x207D0\n" // initualize SP
                );
/*setup the stack for Undefined*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n" 
                 "orr r0, r0, #0x000000DB\n" // mode change 11000010
                 "msr cpsr, r0\n" // mode -> IRQ
                 "ldr r13, =0x209C4\n" // initualize SP
                );                    
/* go back to supervisor mode*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n"
                 "orr r0, r0, #0x000000D3\n"
                 "msr cpsr, r0"
                );

__asm__ volatile( "ldr r0,= _ivt\n"
	              "mcr p15,0,r0,c12,c0,0"
	            );                                                                        
}

// _undefined_instruction: .word undefined_instruction
//     _software_interrupt: .word software_interrupt
//     _prefetch_abort: .word prefetch_abort
//     _data_abort: .word data_abort
//     _not_used: .word not_used
//     _irq: .word irq
//     _fiq: .word fiq

void irq(){
        // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
}

void fiq(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r7,lr}");
}

void undefined_instruction(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
}

void software_interrupt(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
}

void prefetch_abort(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
        kprintf("this is a prefetch abort!\n");
        long unsigned psr;
    __asm__ volatile("mrs %0, spsr":"=r" (psr));
        kprintf("spsr: %p\n",psr);
    __asm__ volatile("mov %0, lr":"=r" (psr));
        kprintf("lr: %p\n",psr);    
    __asm__ volatile("mrs %0, cpsr":"=r" (psr));
        kprintf("cpsr: %p\n",psr);    
    __asm__ volatile("ldmdb r13, {r0-r12,lr}\n"
                     "add r1, lr, #0xE8\n"
                     "mrs r0, spsr\n"    
                     "msr cpsr, r0\n"
                     "mov pc, r1"
                    );                            
}

void data_abort(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
}

void reset(){
    kprintf("this a rest!");
}








       