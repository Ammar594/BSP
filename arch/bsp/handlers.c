#include <arch/bsp/trampoline.h>
#include <arch/bsp/kprintf.h>
#include <stdint.h>
#include <arch/bsp/print_functions.h>
#include <config.h>
#include    <arch/bsp/uart.h>
#include <arch/bsp/bcm2836.h>
#include <arch/bsp/handlers.h>
void irq_handler(){
    kprintf("this is an IRQ interrupt\n");
    if(asm_read(IRQ_PENDING2 & 1 << 25) == 0b1){
        kprintf("uart interrupt\n");
    }
    asm_write(CS,CS|M3);
    asm_write(C3,TIMER_INTERVAL + asm_read(CLO));
    if(d){
        unsigned LR;
        unsigned regs[16];
        unsigned CPSR, SPSR;
        asm volatile("MRS %0, CPSR": "=r"(CPSR));
        asm volatile("MRS %0, SPSR": "=r"(SPSR));
        asm volatile("MRS %0, LR_usr":"=r"(LR));
        LR -= 4;
        kprintf("###########################################################################\n");
        kprintf("IRQ interrupt an Adresse 0x%08x\n",LR);
        register_reader(regs);
        print_registers(regs);
        kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
        status_registers(CPSR,1);
        status_registers(SPSR,0);
        register_specific('i');
        d=0;
    }
}
void fiq_handler(){
        kprintf("this is a FIQ interrupt\n");
        unsigned LR;
        unsigned regs[16];
        unsigned CPSR, SPSR;
        asm volatile("MRS %0, CPSR": "=r"(CPSR));
        asm volatile("MRS %0, SPSR": "=r"(SPSR));
        asm volatile("MRS %0, LR_usr":"=r"(LR));
        LR -= 8;
        kprintf("###########################################################################\n");
        kprintf("IRQ interrupt an Adresse 0x%08x\n",LR);
        register_reader(regs);
        print_registers(regs);
        kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
        status_registers(CPSR,1);
        status_registers(SPSR,0);
        register_specific('i');
        while(1);
}

void undefined_instruction_handler(){
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    asm volatile("MRS %0, CPSR": "=r"(CPSR));
    asm volatile("MRS %0, SPSR": "=r"(SPSR));
    asm volatile("MRS %0, LR_usr":"=r"(LR));
    LR -= 4;
    kprintf("###########################################################################\n");
    kprintf("Undefined Instruction Interrupt an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific('u');
    kprintf("System angehalten\n");
    while(1);
}

void software_interrupt_handler(){ // Supervisor Call
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    asm volatile("MRS %0, CPSR": "=r"(CPSR));
    asm volatile("MRS %0, SPSR": "=r"(SPSR));
    asm volatile("MRS %0, LR_usr":"=r"(LR));
    LR -= 4;
    kprintf("###########################################################################\n");
    kprintf("Software Interrupt aka Supervisor Call an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific('s');
    kprintf("System angehalten\n");
    while(1);
}

void data_abort_handler(){
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    asm volatile("MRS %0, CPSR": "=r"(CPSR));
    asm volatile("MRS %0, SPSR": "=r"(SPSR));
    asm volatile("MRS %0, LR_usr":"=r"(LR));
    LR -= 8;
    kprintf("###########################################################################\n");
    kprintf("Data Abort an Adresse 0x%08x\n",LR);
    print_DFSR_status();
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific('a');
    kprintf("System angehalten\n");
    while(1);
}

void prefetch_abort_handler(){
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    asm volatile("MRS %0, CPSR": "=r"(CPSR));
    asm volatile("MRS %0, SPSR": "=r"(SPSR));
    asm volatile("MRS %0, LR_usr":"=r"(LR));
    LR -= 4;
    kprintf("###########################################################################\n");
    kprintf("Prefetch Abort an Adresse 0x%08x\n",LR);
    print_IFSR_status();
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific('p');
    kprintf("System angehalten\n");
    while(1);
}

void reset(){
    kprintf("this a rest!");
}
