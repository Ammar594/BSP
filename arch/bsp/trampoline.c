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

void status_registers(long unsigned PSR, int bool){
    if(bool) kprintf("CPSR: ");
    else kprintf("SPSR: ");
    if(((PSR >> 31) & 0x00000001) == 0x1) kprintf("N");
    else kprintf("_");
    if(((PSR >> 30) & 0x00000001) == 0x1) kprintf("Z");
    else kprintf("_");
    if(((PSR >> 29) & 0x00000001) == 0x1) kprintf("C");
    else kprintf("_");
    if(((PSR >> 28) & 0x00000001) == 0x1) kprintf("V");
    else kprintf("_");
    kprintf(" ");
    if(((PSR >> 7) & 0x00000001) == 0x1) kprintf("I");
    else kprintf("_");
    if(((PSR >> 6) & 0x00000001) == 0x1) kprintf("F");
    else kprintf("_");
    if(((PSR >> 5) & 0x00000001) == 0x1) kprintf("T");
    else kprintf("_");
    kprintf("        (0x%08x)\n",PSR);
}

void register_specific(){
    kprintf(">>> Aktuelle modusspezifische Register <<<\n");
    long unsigned LR_svc, LR_abt, LR_fiq, LR_irq, LR_und;
    long unsigned SP_svc, SP_abt, SP_fiq, SP_irq, SP_und ;
    long unsigned SPSR_svc, SPSR_abt, SPSR_fiq, SPSR_irq, SPSR_und;
    __asm__ volatile("MRS %0, LR_svc":"=r"(LR_svc));
    __asm__ volatile("MRS %0, LR_abt":"=r"(LR_abt));
    __asm__ volatile("MRS %0, LR_fiq":"=r"(LR_fiq));
    __asm__ volatile("MRS %0, LR_irq":"=r"(LR_irq));
    __asm__ volatile("MRS %0, LR_und":"=r"(LR_und));
    __asm__ volatile("MRS %0, SP_svc":"=r"(SP_svc));
    __asm__ volatile("MRS %0, SP_abt":"=r"(SP_abt));
    __asm__ volatile("MRS %0, SP_fiq":"=r"(SP_fiq));
    __asm__ volatile("MRS %0, SP_irq":"=r"(SP_irq));
    __asm__ volatile("MRS %0, SP_und":"=r"(SP_und));
    __asm__ volatile("MRS %0, SPSR_svc":"=r"(SPSR_svc));
    __asm__ volatile("MRS %0, SPSR_abt":"=r"(SPSR_abt));
    __asm__ volatile("MRS %0, SPSR_fiq":"=r"(SPSR_fiq));
    __asm__ volatile("MRS %0, SPSR_irq":"=r"(SPSR_irq));
    __asm__ volatile("MRS %0, SPSR_und":"=r"(SPSR_und));

    kprintf("             LR             SP       SPSR\n");
    kprintf("User/System: 0xFFFFFFFF 0xFFFFFFFF 0xFFFFFFFF\n"
            "Supervisor:  0x%08x     0x%08x     %s   (0x%08x)\n"
            "Abort:       0x%08x     0x%08x     %s   (0x%08x)\n"
            "FIQ:         0x%08x     0x%08x     %s   (0x%08x)\n"
            "IRQ:         0x%08x     0x%08x     %s   (0x%08x)\n"
            "Undefined:   0x%08x     0x%08x     %s   (0x%08x)\n",
            LR_svc,SP_svc,"_z_zafa",SPSR_svc,LR_abt,SP_abt,"_z_zafa",SPSR_abt,
            LR_fiq,SP_fiq,"_z_zafa",SPSR_fiq,LR_irq,SP_irq,"_z_zafa",SPSR_irq,
            LR_und,SP_und,"_z_zafa",SPSR_und
            );
}

void software_interrupt(){ // Supervisor Call
    // store registers!
    __asm__ volatile("SUB lr, lr, #4\n"
                     "PUSH {lr}\n"
                     "PUSH {R0-R12}"
                     //"STMDB SP, {R0-R12,LR}^"
                     //"PUSH {R0-R12}"
                     );
    long unsigned LR;
    long unsigned regs[16];
    long unsigned CPSR, SPSR;
    __asm__ volatile("MRS %0, CPSR": "=r"(CPSR));
    __asm__ volatile("MRS %0, SPSR": "=r"(SPSR));
    __asm__ volatile("MOV %0, LR":"=r"(LR));
    LR = LR - 4;
    kprintf("###########################################################################\n");
    kprintf("Software Interrupt aka Supervisor Call an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    //register_specific();
    __asm__ volatile(
                     //"LDMDB SP!, {R0-R12,SP}^"
                     "POP {R0-R12}\n"
                     "LDM SP!,{PC}^"
                     );
}

void prefetch_abort(){
    __asm__ volatile("SUB LR, LR, #4\n"
                     "STMDB SP!, {R0-R12,LR}");
    long unsigned LR;
    long unsigned regs[16];
    long unsigned CPSR, SPSR;
    __asm__ volatile("MRS %0, CPSR": "=r"(CPSR));
    __asm__ volatile("MRS %0, SPSR": "=r"(SPSR));
    __asm__ volatile("MOV %0, LR":"=r"(LR));
    LR = LR - 4;
    kprintf("###########################################################################\n");
    kprintf("Prefetch Abort an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific();
    __asm__ volatile("LDMDB SP!, {R0-R12,SP}^");     
}

void data_abort(){
    // store registers!
    __asm__ volatile("stmdb r13, {r0-r12,lr}");
}

void reset(){
    kprintf("this a rest!");
}








       