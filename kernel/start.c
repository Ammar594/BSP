#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#include <config.h>
#include <arch/bsp/trampoline.h>
#include <arch/bsp/sys_timer.h>
#include<arch/bsp/handlers.h>
#include<arch/bsp/bcm2836.h>
#include<arch/bsp/regcheck.h>
#include<arch/bsp/start.h>
void start_kernel(){
	uart_init();
	init_timer();
	kprintf("Starting Kernel....\n");
	while(1){
		kprintf("waiting for input....\n");
		char c = uart_getc();
		switch (c)
		{
		case 's':
			__asm__ volatile("SWI 0xFFFFF"); // Supervisor Call
			break;
		case 'p':
			__asm__ volatile("B 0xFFFFFFFF"); // Prefetch Abort 
			break;
		case 'a':
		   asm volatile("ldr r3,[fp, #-24]"); // Data Abort
		   asm volatile("ldrb r3,[r3]");
			break;
		case 'u':
			__asm__ volatile(".globl TEST\n" // Undefined Exception
							 "TEST:\n"
    						 ".word 0xFFFFFFFF\n"
    						 "bx lr");
			break;
		case 'd':
			d = 1;
			break;
		case 'e':
				 // start the timer
				asm_write(IRQ_ENABLE_IRQ2,IRQ_ENABLE_IRQ2|1<<25);
				asm_write(UART0_IMSC,UART0_IMSC|UART0_IMSC_RX);
				ring_buffer_init(&buffer);
				while(1){
				}	
		case 'c':
			register_checker();
		default:
			break;
		}
	}
}