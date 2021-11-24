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

not_used:

undefined_instruction:
	stmdb sp!,{r0-r12,lr}
	mrs r0, spsr
	mrs r1, cpsr
	stmdb sp!, {r0-r1}
	mov r0, sp
	bl undefined_instruction_handler
	ldmia sp!, {r0-r1}
	msr spsr_cxfs, r0
	msr cpsr_cxfs, r1
	ldmia sp!,{r0-r12,pc}^

software_interrupt:
	stmdb sp!,{r0-r12,lr}
	mrs r0, spsr
	mrs r1, cpsr
	stmdb sp!, {r0-r1}
	mov r0, sp
	bl software_interrupt_handler
	ldmia sp!, {r0-r1}
	msr spsr_cxfs, r0
	msr cpsr_cxfs, r1
	ldmia sp!,{r0-r12,pc}^

prefetch_abort:
    adds lr, lr, #4
	stmdb sp!,{r0-r12,lr}
	mrs r0, spsr
	mrs r1, cpsr
	stmdb sp!, {r0-r1}
	mov r0, sp
	bl prefetch_abort_handler
	ldmia sp!, {r0-r1}
	msr spsr_cxfs, r0
	msr cpsr_cxfs, r1
	ldmia sp!,{r0-r12,pc}^
	
data_abort:
	stmdb sp!,{r0-r12,lr}
	mrs r0, spsr
	mrs r1, cpsr
	stmdb sp!, {r0-r1}
	mov r0, sp
	bl data_abort_handler
	ldmia sp!, {r0-r1}
	msr spsr_cxfs, r0
	msr cpsr_cxfs, r1
	ldmia sp!,{r0-r12,pc}^

irq:
	stmdb sp!,{r0-r12,lr}
	mrs r0, spsr
	mrs r1, cpsr
	stmdb sp!, {r0-r1}
	mov r0, sp
	bl irq_handler
	ldmia sp!, {r0-r1}
	msr spsr_cxfs, r0
	msr cpsr_cxfs, r1
	ldmia sp!,{r0-r12,pc}^

fiq:
	sub lr, #8
	stmdb sp!,{r0-r12,lr}
	mrs r0, spsr
	mrs r1, cpsr
	stmdb sp!, {r0-r1}
	mov r0, sp
	bl fiq_handler
	ldmia sp!, {r0-r1}
	msr spsr_cxfs, r0
	msr cpsr_cxfs, r1
	ldmia sp!,{r0-r12,pc}^