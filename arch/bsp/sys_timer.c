#include <arch/bsp/kprintf.h>
//#include <arch/bsp/bcm2836.h>
#include <config.h>
#include <stddef.h>
#include <stdint.h>




/**************/
/* Interrupts */
/**************/
/* Section 7 */
			/*7e00b000 */
#define	IO_BASE	 0x3f000000
#define IRQ_BASE (IO_BASE+0xb000)
#define IRQ_BASIC_PENDING	(IRQ_BASE+0x200)
#define IRQ_PENDING1		(IRQ_BASE+0x204)
#define IRQ_PENDING2		(IRQ_BASE+0x208)
#define IRQ_FIQ_CONTROL		(IRQ_BASE+0x20c)
#define IRQ_ENABLE_IRQ1		(IRQ_BASE+0x210)
#define IRQ_ENABLE_IRQ2		(IRQ_BASE+0x214)
#define IRQ_ENABLE_BASIC_IRQ	(IRQ_BASE+0x218)
#define IRQ_ENABLE_BASIC_IRQ_ACCESS_ERROR0	(1<<7)
#define IRQ_ENABLE_BASIC_IRQ_ACCESS_ERROR1	(1<<6)
#define IRQ_ENABLE_BASIC_IRQ_GPU1_HALTED	(1<<5)
#define IRQ_ENABLE_BASIC_IRQ_GPU0_HALTED	(1<<4)
#define IRQ_ENABLE_BASIC_IRQ_ARM_DOORBELL1	(1<<3)
#define IRQ_ENABLE_BASIC_IRQ_ARM_DOORBELL0	(1<<2)
#define IRQ_ENABLE_BASIC_IRQ_ARM_MAILBOX	(1<<1)
#define IRQ_ENABLE_BASIC_IRQ_ARM_TIMER		(1<<0)
#define IRQ_DISABLE_IRQ1	(IRQ_BASE+0x21c)
#define IRQ_DISABLE_IRQ2	(IRQ_BASE+0x220)
#define IRQ_DISABLE_BASIC_IRQ	(IRQ_BASE+0x224)

// System Timer Contorl/Status
#define TIMER_BASE	(IO_BASE+0b000)
#define CS (TIMER_BASE+0x00)
#define M0 (1 << 0) // System Timer Match 0
#define M1 (1 << 1) // System Timer Match 1
#define M2 (1 << 2) // System Timer Match 2
#define M3 (1 << 3) // System Timer Match 3
// System Timer Counter Lower 32 bits
#define CLO (TIMER_BASE+0x04)
// System Timer Counter Higher 32 bits
#define CHI (TIMER_O_BASEASE+0x14)
// System Timer Compare 0
#define C0 (TIMER_BASE+0xc)
// System Timer Compare 1
#define C1 (TIMER_BASE+0x10)
// System Timer Compare 2
#define C2 (TIMER_BASE+0x14)
// System Timer Compare 3
#define C3 (TIMER_BASE+0x18)

static inline void mmio_write(uint32_t addr, uint32_t data) {
	uint32_t *ptr = (uint32_t *)addr;
	// just excuting a store command in assembly
	asm volatile("str %[data], [%[addr]]" :
		: [addr]"r"(ptr), [data]"r"(data));
}
static inline uint32_t mmio_read(uint32_t addr) {
	uint32_t *ptr = (uint32_t *)addr;
	uint32_t data;
	// just excuting a load command in assembly
	asm volatile("ldr %[data], [%[addr]]" :
		[data]"=r"(data) : [addr]"r"(ptr));
	return data;
}

void init_timer(){
    mmio_write(IRQ_DISABLE_IRQ1,0xFFFFFFFF);
    mmio_write(IRQ_ENABLE_IRQ1,IRQ_ENABLE_IRQ1|M1); // enable timer interrupt
    kprintf("IRE1 0x%08x\n",mmio_read(IRQ_ENABLE_IRQ1));
    mmio_write(CS,CS|M3);
    kprintf("CS 0x%08x\n",mmio_read(CS));
    mmio_write(C1,TIMER_INTERVAL);
    
}
