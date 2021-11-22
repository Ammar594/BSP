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
                 "and r0, r0, #0xFFFFFF00\n" 
                 "orr r0, r0, #0x000000D1\n" 
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
/* return to supervisor mode*/
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

void register_reader(long unsigned * regs){
    __asm__ volatile("mov %0, R0":"=r"(regs[0]));
    __asm__ volatile("mov %0, R1":"=r"(regs[1]));
    __asm__ volatile("mov %0, R2":"=r"(regs[2]));
    __asm__ volatile("mov %0, R3":"=r"(regs[3]));
    __asm__ volatile("mov %0, R4":"=r"(regs[4]));
    __asm__ volatile("mov %0, R5":"=r"(regs[5]));
    __asm__ volatile("mov %0, R6":"=r"(regs[6]));
    __asm__ volatile("mov %0, R7":"=r"(regs[7]));
    __asm__ volatile("mov %0, R8":"=r"(regs[8]));
    __asm__ volatile("mov %0, R9":"=r"(regs[9]));
    __asm__ volatile("mov %0, R10":"=r"(regs[10]));
    __asm__ volatile("mov %0, R11":"=r"(regs[11]));
    __asm__ volatile("mov %0, R12":"=r"(regs[12]));
    __asm__ volatile("mov %0, R13":"=r"(regs[13]));
    __asm__ volatile("mov %0, R14":"=r"(regs[14]));
    __asm__ volatile("mov %0, R15":"=r"(regs[15]));
}

void print_registers(long unsigned * regs){
    kprintf(">>> Registerschnappschuss (aktueller Modus) <<<\n");
    kprintf("R0:  0x%08x R8:  0x%08x\n"
            "R1:  0x%08x R9:  0x%08x\n"
            "R2:  0x%08x R10: 0x%08x\n"
            "R3:  0x%08x R11: 0x%08x\n"
            "R4:  0x%08x R12: 0x%08x\n"
            "R5:  0x%08x SP:  0x%08x\n"
            "R6:  0x%08x LR:  0x%08x\n"
            "R7:  0x%08x PC:  0x%08x\n",
            regs[0],regs[8],
            regs[1],regs[9],
            regs[2],regs[10],
            regs[3],regs[11],
            regs[4],regs[12],
            regs[5],regs[13],
            regs[6],regs[14],
            regs[7],regs[15]
            );
}

void software_interrupt(){ // Supervisor Call
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
    long unsigned LR;
    long unsigned regs[16];
    __asm__ volatile("mov %0, LR":"=r"(LR));
    LR = LR - 4;
    kprintf("###########################################################################\n");
    kprintf("Software Interrupt aka Supervisor Call an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
}

void prefetch_abort(){
    // store registers!
    __asm__ volatile("STMDB SP, {R0-R12,LR}");
    kprintf("###########################################################################");
    //kprintf("Data Abort an Adresse: %8p", )













    __asm__ volatile("LDMDB SP, {R0-R12,PC}^\n"
                     //"ADD LR, LR, #0x4\n"
                     //"MOV PC, LR"
                     //"mrs r12, spsr\n"    
                     //"msr cpsr, r12\n"
                     //"add lr,lr,#0x4\n"
                     //"mov pc, lr"
                    );                            
}

void data_abort(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
}

void reset(){
    kprintf("this a rest!");
}








       