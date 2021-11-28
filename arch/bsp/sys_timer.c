#include <arch/bsp/kprintf.h>
#include <arch/bsp/bcm2836.h>
#include <config.h>
#include <stddef.h>
#include <stdint.h>



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

void init_timer(){
    asm_write(C3,TIMER_INTERVAL); // set the timer value
    asm_write(IRQ_ENABLE_IRQ1,IRQ_ENABLE_IRQ1|M3); // enable timer interrupt
}
