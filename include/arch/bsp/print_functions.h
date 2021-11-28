#ifndef PRINT_FUNCTIONS_H
#define PRINT_FUNCTIONS_H

struct registers
{   char flags_svc[11], flags_abt[11], flags_fiq[11], flags_irq[11], flags_und[11];
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

void print_regs(struct registers * regs);
void print_registers(unsigned * regs);
void register_reader(unsigned * regs);
void status_register_flags( unsigned PSR, char * flags);
void status_registers( unsigned PSR, int bool);
void print_IFSR_status();
void print_DFSR_status();
void register_specific(char mode);

#endif