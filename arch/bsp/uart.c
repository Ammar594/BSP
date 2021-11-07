#include <stddef.h>
#include <stdint.h>
#include <arch/bsp/bcm2836.h>

static inline void delay(int32_t count) {
	asm volatile("__delay_%=: subs %[count], %[count], #1; "
			"bne __delay_%=\n"
		: [count]"+r"(count) /* outputs */
		: /* inputs */
		: "cc" /* clobbers */);
}

static inline void asm_write(uint32_t addr, uint32_t data) {
	uint32_t *ptr = (uint32_t *)addr;
	// just excuting a store command in assembly
	asm volatile("str %[data], [%[addr]]" :
		: [addr]"r"(ptr), [data]"r"(data));
}

static inline uint32_t asm_read(uint32_t addr) {
	uint32_t *ptr = (uint32_t *)addr;
	uint32_t data;
	// just excuting a load command in assembly
	asm volatile("ldr %[data], [%[addr]]" :
		[data]"=r"(data) : [addr]"r"(ptr));
	return data;
}


void uart_init(void) {

	uint32_t old;

	/* Disable UART */
	asm_write(UART0_CR, 0x0);

	asm_write(UART0_LCRH_FEN, 0x0);

	



	/* Setup GPIO pins 14 and 15 */

	/* Set GPIO14 and GPIO15 to be pl011 TX/RX which is ALT0	*/
	/* ALT0 is binary 100 (0x4)					*/
	// old=asm_read(GPIO_GPFSEL1);
	// old &= ~(0x7 << 12);
	// old |= (4<<12);

	// old &= ~(0x7 << 15);
	// old |= (4<<15);
	// asm_write(GPIO_GPFSEL1,old);

	/* Disable the pull up/down on pins 14 and 15 */
	/* See the Peripheral Manual for more info */
	/* Configure to disable pull up/down and delay for 150 cycles */
	// asm_write(GPIO_GPPUD, GPIO_GPPUD_DISABLE);
	// delay(150);

	/* Pass the disable clock to GPIO pins 14 and 15 and delay*/
	// asm_write(GPIO_GPPUDCLK0, (1 << 14) | (1 << 15));
	// delay(150);

	/* Write 0 to GPPUDCLK0 to make it take effect */
	// asm_write(GPIO_GPPUDCLK0, 0x0);

	/* Mask all interrupts. */
	// asm_write(UART0_IMSC, 0);

	/* Clear pending interrupts. */
	// asm_write(UART0_ICR, 0x7FF);

	/* Set integer & fractional part of baud rate. */
	/* Divider = UART_CLOCK/(16 * Baud)            */
	/* Integer part register = integer part of Divider */
	/* Fraction part register = (Fractional part * 64) + 0.5 */
	/* UART_CLOCK = 48MHz (old firmware it was 3MHz); Baud = 115200. */
// YOUR CODE HERE
	/* Set up the Line Control Register */
	/* Enable FIFO */
	/* Set length to 8 bit */
	/* Defaults for other bit are No parity, 1 stop bit */
	//asm_write(UART0_LCRH, UART0_LCRH_FEN | UART0_LCRH_WLEN_8BIT);

	/* Enable UART0, receive, and transmit */
	// enable transfer
	asm_write(UART0_CR_TXE, 0x1);
	// enable recieve
	asm_write(UART0_CR_RXE, 0x1);
	/* Enable UART */
	asm_write(UART0_CR, 0x1);
}

void uart_putc(unsigned char byte) {

	/* Check Flags Register */
	/* And wait until FIFO not full */
	while ( asm_read(UART0_FR) & UART0_FR_TXFF ) {
	}
	/* Write our data byte out to the data register */
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

/* write a series of bytes to the serial port */
void uart_write(const unsigned char* buffer, int size) {
	for ( int i = 0; i < size; i++ ) {
		uart_putc(buffer[i]);
	}
}

