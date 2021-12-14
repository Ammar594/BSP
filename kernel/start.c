#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#include <config.h>
#include <arch/bsp/trampoline.h>
#include <arch/bsp/sys_timer.h>
#include<arch/bsp/handlers.h>
#include<arch/bsp/bcm2836.h>
#include<arch/bsp/regcheck.h>
#include<arch/bsp/start.h>
#include<arch/bsp/thread_managment.h>
void start_kernel(){
	uart_init();
	init_timer();
	asm_write(IRQ_ENABLE_IRQ2,IRQ_ENABLE_IRQ2|1<<25);
	asm_write(UART0_IMSC,UART0_IMSC|UART0_IMSC_RX);
	kprintf("Starting Kernel....\n");
	kprintf("Intilizing threads...\n");
	init_tcbs();
	kprintf("Entering idle thread...\n");
	idle_thread();
}