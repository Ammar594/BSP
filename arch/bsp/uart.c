#include <stddef.h>
#include <stdint.h>
#include<arch/bsp/uart.h>
#include <arch/bsp/bcm2836.h>
unsigned d = 0;
void asm_write(uint32_t addr, uint32_t data) {
	uint32_t *ptr = (uint32_t *)addr;
	// just excuting a store command in assembly
	asm volatile("str %[data], [%[addr]]" :
		: [addr]"r"(ptr), [data]"r"(data));
}

uint32_t asm_read(uint32_t addr) {
	uint32_t *ptr = (uint32_t *)addr;
	uint32_t data;
	// just excuting a load command in assembly
	asm volatile("ldr %[data], [%[addr]]" :
		[data]"=r"(data) : [addr]"r"(ptr));
	return data;
}

void uart_init(void) {
	/* Disable UART */
	// asm_write(UART0_CR, 0x0);
	/* enable uart interrupt*/
	// asm_write(IRQ_ENABLE_IRQ2,IRQ_ENABLE_IRQ2|1<<25);
	/* Disable FIFO */
	// asm_write(UART0_LCRH,UART0_LCRH|UART0_LCRH_FEN);
	// /* Clear pending interrupts. */
	// asm_write(UART0_ICR, 0x7FF);
	// /* Enable UART0, receive, and transmit */
	// // enable transfer
	// asm_write(UART0_CR,UART0_CR | UART0_CR_TXE);
	// // enable recieve
	// asm_write(UART0_CR,UART0_CR | UART0_CR_RXE);
	// /* Enable UART */
	// asm_write(UART0_CR, 0x1);
}

void uart_putc(unsigned char byte) {
	/* Check Flags Register */
	/* And wait until FIFO not full */
	/* Write our data byte out to the data register */
	while ( asm_read(UART0_FR) & UART0_FR_TXFF ) {
	}
	asm_write(UART0_DR, byte);
}

unsigned char uart_getc(void) {

	/* Check Flags Register */
	/* Wait until Receive FIFO is not empty */
	while ( asm_read(UART0_FR) & UART0_FR_RXFE ) {
	}
	/* Read and return the received data */
	/* Note we are ignoring the top 4 error bits */
	return asm_read(UART0_DR);
}

unsigned char uart_getc_interrupt(void) {
	/* Note we are ignoring the top 4 error bits */
	
	return asm_read(UART0_DR);
}


/* write a series of bytes to the serial port */
void uart_write(const unsigned char* buffer, int size) {
	for ( int i = 0; i < size; i++ ) {
		uart_putc(buffer[i]);
	}
}

