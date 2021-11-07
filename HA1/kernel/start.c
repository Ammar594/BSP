#include <arch/bsp/kprintf.h>
#include <arch/bsp/uart.h>
#include <config.h>

volatile unsigned int counter = 0;

void increment_counter() {
	counter++;
}

void start_kernel(){
	// initializing UART
	uart_init();
	test_kprintf();
}