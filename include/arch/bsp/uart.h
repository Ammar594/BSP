#include<stdint.h>
#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_putc(unsigned char byte);
void uart_write(const unsigned char* buffer, int size);
unsigned char uart_getc(void);
void asm_write(uint32_t addr, uint32_t data);
uint32_t asm_read(uint32_t addr);
unsigned char uart_getc_interrupt();

#endif
