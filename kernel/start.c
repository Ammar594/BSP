#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#include <config.h>
#include <arch/bsp/trampoline.h>

volatile unsigned int counter = 0;

void increment_counter() {
	counter++;
}


void start_kernel(){
	uart_init();
	unsigned long *bad;
	kprintf("Starting Kernel\n");
	while(1){
		kprintf("waiting for input....\n");
		char c = uart_getc();
		switch (c)
		{
		case 's':
			__asm__ volatile("SVC 0xFFFFFF");
			break;
		case 'p':
			__asm__ volatile("BKPT 0xFFFF");
			break;
		case 'd':
		    bad = (unsigned long *)0x09000000;
			bad = (unsigned long *)0x1234567;
			break;
		case 'u':
			__asm__ volatile(".globl TEST\n"
							 "TEST:\n"
    						  ".word 0xFFFFFFFF\n"
    						   "bx lr");
			break;			
		default:
			break;
		}
	}
}