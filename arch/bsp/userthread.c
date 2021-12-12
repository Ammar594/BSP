#include <arch/bsp/userthread.h>
int main(void * x){
    for(int i = 0;i < 10;i++){
        kprintf("%c",x);
    }
    return 0;
}