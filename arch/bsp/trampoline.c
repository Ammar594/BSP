#include <arch/bsp/trampoline.h>
void initStacks(){
/*setup the stack for IRQ*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n"
                 "orr r0, r0, #0x000000D2\n" // mode change 11010010
                 "msr cpsr, r0\n" // mode -> IRQ
                 "ldr r13, =0x21000\n" // initualize SP
                );
/*setup the stack for FIQ*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n" // test could be only 16 bit
                 "orr r0, r0, #0x000000D1\n" // test
                 "msr cpsr, r0\n"
                 "ldr r13, =0x22000"
                );
/* go back to supervisor mode*/
__asm__ volatile("mrs r0, cpsr\n"
                 "and r0, r0, #0xFFFFFF00\n"
                 "orr r0, r0, #0x000000D3\n"
                 "msr cpsr, r0"
                );                                                            
}



       