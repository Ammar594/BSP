#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#include <config.h>
#include <arch/bsp/trampoline.h>
#include <arch/bsp/sys_timer.h>

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
			
			break;				
		default:
			break;
		}
	}
}