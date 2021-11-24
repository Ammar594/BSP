#include <arch/bsp/trampoline.h>
#include <arch/bsp/kprintf.h>

struct registers
{
    unsigned LR_svc;
    unsigned LR_abt;
    unsigned LR_fiq;
    unsigned LR_irq;
    unsigned LR_und;
    unsigned LR_usr;
    unsigned SP_svc;
    unsigned SP_abt;
    unsigned SP_fiq;
    unsigned SP_irq;
    unsigned SP_und;
    unsigned SP_usr;
    unsigned SPSR_svc;
    unsigned SPSR_abt;
    unsigned SPSR_fiq;
    unsigned SPSR_irq;
    unsigned SPSR_und;
};


void print_registers(  unsigned * regs){
    kprintf(">>> Registerschnappschuss (aktueller Modus) <<<\n");
    kprintf("R0:  0x%08x  R8:  0x%08x\n"
            "R1:  0x%08x  R9:  0x%08x\n"
            "R2:  0x%08x  R10: 0x%08x\n"
            "R3:  0x%08x  R11: 0x%08x\n"
            "R4:  0x%08x  R12: 0x%08x\n"
            "R5:  0x%08x  SP:  0x%08x\n"
            "R6:  0x%08x  LR:  0x%08x\n"
            "R7:  0x%08x  PC:  0x%08x\n",
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


void register_reader( unsigned * regs){
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

void status_register_flags( unsigned PSR, char * flags){
    if(((PSR >> 31) & 0x00000001) == 0x1) flags[0] = 'N';
    else flags[0] = '_';
    if(((PSR >> 30) & 0x00000001) == 0x1) flags[1] = 'Z';
    else flags[1] = '_';
    if(((PSR >> 29) & 0x00000001) == 0x1) flags[2] = 'C';
    else flags[2] = '_';
    if(((PSR >> 28) & 0x00000001) == 0x1) flags[3] = 'V';
    else flags[3] = '_';
    flags[4] = ' ';
    if(((PSR >> 9) & 0x00000001) == 0x1) flags[5] = 'E';
    else flags[5] = '_';
    if(((PSR >> 7) & 0x00000001) == 0x1) flags[6] = 'I';
    else flags[6] = '_';
    if(((PSR >> 6) & 0x00000001) == 0x1) flags[7] = 'F';
    else flags[7] = '_';
    if(((PSR >> 5) & 0x00000001) == 0x1) flags[8] = 'T';
    else flags[8] = '_';
    flags[9] = '\0';
}

void status_registers( unsigned PSR, int bool){
    if(bool) kprintf("CPSR: ");
    else kprintf("SPSR: ");
    char flags[10];
    status_register_flags(PSR,flags);
    kprintf("%s",flags);
    if((PSR & 0x0000001F) == 0x10) kprintf(" User");
    else if((PSR & 0x0000001F) == 0x11) kprintf(" FIQ");
    else if((PSR & 0x0000001F) == 0x12) kprintf(" IRQ");
    else if((PSR & 0x0000001F) == 0x13) kprintf(" Supervisor");
    else if((PSR & 0x0000001F) == 0x17) kprintf(" Abort");
    else if((PSR & 0x0000001F) == 0x1C) kprintf(" Undefined");
    else if((PSR & 0x0000001F) == 0x1F) kprintf(" System");
    kprintf("        (0x%08x)\n",PSR);
}

void print_IFSR_status(){
    unsigned IFSR;
    unsigned IFAR;
     // reading IFSR and IFAR registers
    __asm__ volatile("MRC p15, 0, %0, c5, c0, 1":"=r"(IFSR));
    __asm__ volatile("MRC p15, 0, %0, c5, c0, 1":"=r"(IFAR));
    IFSR = IFSR & 0x1F; // mask the status bits and set the other bits to 0
    if(IFSR == 0b00000) kprintf("No function, reset value\n");
    else if(IFSR == 0b00001) kprintf("Fehler: No function\n");
    else if(IFSR == 0b00010) kprintf("Fehler: Debug event fault\n");
    else if(IFSR == 0b00011) kprintf("Fehler: Access Flag fault on Section\n");
    else if(IFSR == 0b00100) kprintf("Fehler: No function\n");
    else if(IFSR == 0b00101) kprintf("Fehler: Translation fault on Section\n");
    else if(IFSR == 0b00110) kprintf("Fehler: Access Flag fault on Page\n");
    else if(IFSR == 0b00111) kprintf("Fehler: Translation fault on Page\n");
    else if(IFSR == 0b01000) kprintf("Fehler: Precise External Abort\n");
    else if(IFSR == 0b01001) kprintf("Fehler: Domain fault on Section\n");
    else if(IFSR == 0b01010) kprintf("Fehler: No function\n");
    else if(IFSR == 0b01011) kprintf("Fehler: Domain fault on Page\n");
    else if(IFSR == 0b01100) kprintf("Fehler: External abort on Section\n");
    else if(IFSR == 0b01101) kprintf("Fehler: Permission fault on Section\n");
    else if(IFSR == 0b01110) kprintf("Fehler: External abort on Page\n");
    else if(IFSR == 0b01111) kprintf("Fehler: Permission fault on Page\n");
    else if(IFSR >= 0b10000) kprintf("Fehler: No function\n");
    kprintf("Fehler: an der Adresse: 0x%08x \n",IFAR);
}

void register_specific(){
    kprintf(">>> Aktuelle modusspezifische Register <<<\n");
    struct registers regs;
    char flags_svc[10], flags_abt[10], flags_fiq[10], flags_irq[10], flags_und[10];
    
    __asm__ volatile("MRS %0, LR_svc":"=r"(regs.LR_svc));
    __asm__ volatile("MRS %0, LR_abt":"=r"(regs.LR_abt));
    __asm__ volatile("MRS %0, LR_fiq":"=r"(regs.LR_fiq));
    __asm__ volatile("MRS %0, LR_irq":"=r"(regs.LR_irq));
    //__asm__ volatile("MRS %0, LR_und":"=r"(regs.LR_und));
    regs.LR_und = 0;
    __asm__ volatile("MRS %0, LR_usr":"=r"(regs.LR_usr));
    __asm__ volatile("MRS %0, SP_abt":"=r"(regs.SP_abt));
    __asm__ volatile("MRS %0, SP_fiq":"=r"(regs.SP_fiq));
    __asm__ volatile("MRS %0, SP_irq":"=r"(regs.SP_irq));
    //__asm__ volatile("MRS %0, SP_und":"=r"(regs.SP_und));
    regs.SP_und = 0;
    __asm__ volatile("MRS %0, SP_svc":"=r"(regs.SP_svc));
    __asm__ volatile("MRS %0, SP_usr":"=r"(regs.SP_usr));
    __asm__ volatile("MRS %0, SPSR_svc":"=r"(regs.SPSR_svc));
    __asm__ volatile("MRS %0, SPSR_abt":"=r"(regs.SPSR_abt));
    __asm__ volatile("MRS %0, SPSR_fiq":"=r"(regs.SPSR_fiq));
    __asm__ volatile("MRS %0, SPSR_irq":"=r"(regs.SPSR_irq));
    //__asm__ volatile("MRS %0, SPSR_und":"=r"(regs.SPSR_und));
    regs.SPSR_und = 0;

    status_register_flags(regs.SPSR_svc,flags_svc);
    status_register_flags(regs.SPSR_abt,flags_abt);
    status_register_flags(regs.SPSR_fiq,flags_fiq);
    status_register_flags(regs.SPSR_irq,flags_irq);
    status_register_flags(regs.SPSR_und,flags_und);

    kprintf("             LR             SP             SPSR\n");
    kprintf("User/System: 0x%08x     0x%08x\n",regs.LR_usr, regs.SP_usr);
    kprintf("Supervisor:  0x%08x     0x%08x     %s   (0x%08x)\n",regs.LR_svc,regs.SP_svc,flags_svc,regs.SPSR_svc);
    kprintf("Abort:       0x%08x     0x%08x     %s   (0x%08x)\n",regs.LR_abt,regs.SP_abt,flags_abt,regs.SPSR_abt);
    kprintf("FIQ:         0x%08x     0x%08x     %s   (0x%08x)\n",regs.LR_fiq,regs.SP_fiq,flags_fiq,regs.SPSR_fiq);
    kprintf("IRQ:         0x%08x     0x%08x     %s   (0x%08x)\n",regs.LR_irq,regs.SP_irq,flags_irq,regs.SPSR_irq);
    kprintf("Undefined:   0x%08x     0x%08x     %s   (0x%08x)\n",regs.LR_und,regs.SP_und,flags_und,regs.SPSR_und);
}


void irq_handler(){
        // store registers!
}

void fiq_handler(){
    // store registers!
}

void undefined_instruction_handler(){
    // store registers!
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    __asm__ volatile("MRS %0, CPSR": "=r"(CPSR));
    __asm__ volatile("MRS %0, SPSR": "=r"(SPSR));
    __asm__ volatile("MOV %0, LR":"=r"(LR));
    kprintf("###########################################################################\n");
    kprintf("Software Interrupt aka Supervisor Call an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific();
    kprintf("System angehalten\n");
    while(1);
}

void software_interrupt_handler(){ // Supervisor Call
    // store registers!
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    __asm__ volatile("MRS %0, CPSR": "=r"(CPSR));
    __asm__ volatile("MRS %0, SPSR": "=r"(SPSR));
    __asm__ volatile("MOV %0, LR":"=r"(LR));
    kprintf("###########################################################################\n");
    kprintf("Software Interrupt aka Supervisor Call an Adresse 0x%08x\n",LR);
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific();
    kprintf("System angehalten\n");
    //while(1);
}

void data_abort_handler(){
    kprintf("this is a data abort exception\n");
}

void prefetch_abort_handler(){
      unsigned LR;
      unsigned regs[16];
      unsigned CPSR, SPSR;
    __asm__ volatile("MRS %0, CPSR": "=r"(CPSR));
    __asm__ volatile("MRS %0, SPSR": "=r"(SPSR));
    __asm__ volatile("MOV %0, LR":"=r"(LR));
    LR = LR - 4;
    kprintf("###########################################################################\n");
    kprintf("Prefetch Abort an Adresse 0x%08x\n",LR);
    print_IFSR_status();
    register_reader(regs);
    print_registers(regs);
    kprintf(">>> Aktulle Statusregister (SPSR des aktullen Modus) <<<\n");
    status_registers(CPSR,1);
    status_registers(SPSR,0);
    register_specific();
    kprintf("System angehalten\n");
    while(1);
}

void reset(){
    kprintf("this a rest!");
}
