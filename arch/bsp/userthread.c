#include <arch/bsp/userthread.h>
void main(void * x){
    for(int i = 0;i < 10;i++){
        kprintf("%c",*((char *)x));
    }
}