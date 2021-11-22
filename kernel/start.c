#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#include <config.h>
#include <arch/bsp/trampoline.h>

volatile unsigned int counter = 0;

void increment_counter() {
	counter++;
}

void start_kernel(){
	//initStacks();
	// initializing UART
	uart_init();
	test_kprintf();
}