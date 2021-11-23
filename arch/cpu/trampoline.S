.global _initStacks
_initStacks:    
/*setup the stack for IRQ 2kb 800 hex*/
    LDR R0, =0x20800
    MSR SP_irq, R0

/*setup the stack for FIQ 2kb 800 hex*/
    LDR R1, =0x21600
    MSR SP_fiq, R1

/*setup the stack for Prefetch Abort 2kb 800 hex*/
    LDR R2, =0x22400
    MSR SP_abt, R2

/*setup the stack for Undefined 2kb 800 hex*/
    LDR R3, =0x23200
    MSR SP_und, R3

/* setup stack for User/System 2kb or 800 hex*/
    LDR R4, =0x24000
    MSR SP_usr, R4

/* IVT Address */
    LDR R0,= _ivt
    MCR p15,0,r0,c12,c0,0

/* enter User mode */
    MSR CPSR, 0xD1

bl _start_kernel




.globl _ivt
.balign 64
_ivt:
    b reset
    ldr pc, _undefined_instruction
    ldr pc, _software_interrupt
    ldr pc, _prefetch_abort
    ldr pc, _data_abort
    ldr pc, _irq
    ldr pc, _fiq
    _undefined_instruction: .word undefined_instruction
    _software_interrupt: .word software_interrupt
    _prefetch_abort: .word prefetch_abort
    _data_abort: .word data_abort
    _irq: .word irq
    _fiq: .word fiq
    _reset: .word reset    