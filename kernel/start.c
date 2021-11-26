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
	kprintf("Starting Kernel\n");
	while(1){
		kprintf("waiting for input....\n");
		char c = uart_getc();
		switch (c)
		{
		case 's':
			__asm__ volatile("SWI 0xFFFFF");
			break;
		case 'p':
			__asm__ volatile("B 0xFFFFFFFF");
			break;
		case 'a':
		   asm volatile("ldr r3,[fp, #-24]");
		   asm volatile("ldrb r3,[r3]");
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