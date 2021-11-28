#include <arch/bsp/kprintf.h>
#include <arch/bsp/bcm2836.h>
#include <config.h>
#include <stddef.h>
#include <stdint.h>
#include <arch/bsp/uart.h>
void init_timer(){
    asm_write(C1,TIMER_INTERVAL); // set the timer value
    asm_write(IRQ_ENABLE_IRQ1,IRQ_ENABLE_IRQ1|M1); // enable timer interrupt
	// enable a second timer
	asm_write(C3,BUSY_WAIT_COUNTER); // set the timer value
    asm_write(IRQ_ENABLE_IRQ1,IRQ_ENABLE_IRQ1|M3); // enable timer interrupt
}
