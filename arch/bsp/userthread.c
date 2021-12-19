#include <arch/bsp/userthread.h>
void main1(void * x){
    char c = *((char *)x);
    for(int i = 0;i < 10;i++){
        kprintf("%c",c);
        for(int j =0;i < 10 * 500000;j++)
            kprintf("\0");
    }
    exit();
}

void main2(){
    for(int i = 0;i < 10;i++){
        kprintf("%c",'A');
        for(int j =0;j < 10 * 500000;j++)
            kprintf("\0");
    }
    kprintf("\n");
    exit();
}