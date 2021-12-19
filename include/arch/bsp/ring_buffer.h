#ifndef RING_BUFFER_H
#define RING_BUFFER_H
#include<config.h>
typedef struct ring_buffer
{
    int head;
    int insert_index;
    int tail;
    int size;
    char data[UART_INPUT_BUFFER_SIZE];
}ring_buffer;

void ring_buffer_init(ring_buffer * buffer);
void add_element(ring_buffer * buffer, char charachter);
void remove_element(ring_buffer * buffer);
char peek_element(ring_buffer * buffer);

#endif