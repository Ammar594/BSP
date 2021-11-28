.globl _ivt
.balign 64
_ivt:
    b reset
    LDR pc, _undefined_instruction
    LDR pc, _software_interrupt
    LDR pc, _prefetch_abort
    LDR pc, _data_abort
    LDR pc, _irq
    LDR pc, _fiq
    _undefined_instruction: .word undefined_instruction
    _software_interrupt: .word software_interrupt
    _prefetch_abort: .word prefetch_abort
    _data_abort: .word data_abort
    _irq: .word irq
    _fiq: .word fiq
    _reset: .word reset 

reset:
	bl _start

undefined_instruction:
	stmdb sp!,{r0-r12,lr}
	bl undefined_instruction_handler
	ldmia sp!,{r0-r12,pc}^

software_interrupt:
	stmdb sp!,{r8-r12,lr}
	bl software_interrupt_handler
	ldmia sp!,{r8-r12,pc}^

prefetch_abort:
	stmdb sp!,{r0-r12,lr}
	bl prefetch_abort_handler
	ldmia sp!,{r0-r12,pc}^
	
data_abort:
	stmdb sp!,{r0-r12,lr}
	bl data_abort_handler
	ldmia sp!,{r0-r12,pc}^

irq:
	stmdb sp!,{r0-r12,lr}
	bl irq_handler
	ldmia sp!,{r0-r12,pc}^

fiq:
	sub lr, #8
	stmdb sp!,{r0-r12,lr}
	bl fiq_handler
	ldmia sp!,{r0-r12,pc}^