#ifndef UART_H
#define UART_H

//void send_byte(char);
//char receive_byte(void);
void uart_init(void);
void uart_putc(unsigned char byte);
unsigned char uart_getc(void);
void uart_write(const unsigned char* buffer, int size);

#endif
