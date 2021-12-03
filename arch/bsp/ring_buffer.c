#include <config.h>
#include <arch/bsp/ring_buffer.h>
void ring_buffer_init(ring_buffer * buffer){
    buffer->head = 0;
    buffer->insert_index = 0;
    buffer->tail = 0;
    buffer->size = 0;
}

void add_element(ring_buffer * buffer, char charachter){
    if(buffer->size < 1){
        buffer->data[buffer->insert_index++] = charachter;
    }
    else{
        buffer->data[buffer->insert_index++] = charachter;
        buffer->head++;
    }
    buffer->size++;
}

void remove_element(ring_buffer * buffer){
    if(buffer->size > 0){
        buffer->head--;
        buffer->size--;
        buffer->insert_index--;
    }
}

char peek_element(ring_buffer * buffer){
    return buffer->data[buffer->head];
} 