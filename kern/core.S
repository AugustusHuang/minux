/* Assembly routines for ARM-Cortex-M3/4. */

#include "arch.h"
#include "interrupt.h"

	.global interrupt_enable
	.global interrupt_disable
	.global fiq_enable
	.global fiq_disable
	.global lsr_save
	.global lsr_load
	.global interrupt_wait
	.global exception_wait
	.global context_switch
	.global interrupt_pendsv
	.global switch_ready

	/* PendSV interrupt register address */
	.equ ARCH_PENDSV, 0xE000ED22
	/* Set PendSV to lowest priority to ensure we call it in Thread mode
	 * and from main stack. */
	.equ PENDSV_PRIO, 0xFF
	/* PendSV ISR trigger */
	.equ PENDSV_TRIG, 0x10000000


	.text
	.align 2
	.thumb
	.syntax unified

	.thumb_func
interrupt_enable:
	cpsie i
	bx lr

	.thumb_func
interrupt_disable:
	cpsid i
	bx lr

	.thumb_func
fiq_enable:
	cpsie f
	bx lr

	.thumb_func
fiq_disable:
	cpsid f
	bx lr

	.thumb_func
lsr_save:
	mrs r0, primask
	cpsid i
	bx lr

	.thumb_func
lsr_load:
	msr primask, r0
	bx lr

	.thumb_func
interrupt_wait:
	wfi
	bx lr

	.thumb_func
exception_wait:
	wfe
	bx lr

	.thumb_func
context_switch:
	ldr r0, =ARCH_ICSR
	ldr r1, =PENDSV_TRIG
	str r1, [r0]
	bx lr

	.thumb_func
interrupt_pendsv:
	cpsid i
	/* Assign process stack pointer to R0. */
	mrs r0, psp

	/* Store R4-R11 and LR to [R0], on the process stack. */
	stmfd r0!, {r4-r11, lr}
	/* R5 is unaffected, R5 <- curproc */
	movw r5, #:lower16:curproc
	movt r5, #:upper16:curproc

	/* R6 <- *curproc and R0 <- current_sp since the first slot is sp.
	 * FIXME: Do we need this? */
	ldr r6, [r5]
	str r0, [r6]

	/* Save LR. */
	mov r4, lr
	/* R0 <- curprio and R1 <- wait_prio.
	 * FIXME: Define curprio and wait_prio! */
	movw r0, #:lower16:curprio
	movt r0, #:upper16:curprio

	movw r1, #:lower16:wait_prio
	movt r1, #:upper16:wait_prio

	/* Load current priority with the waiting priority.
	 * Since prio_t is unsigned char. */
	ldrb r2, [r1]
	strb r2, [r0]

	/* R1 <- wait_proc. */
	movw r1, #:lower16:wait_proc
	movt r1, #:upper16:wait_proc

	/* Switch wait_proc and curproc. */
	ldr r2, [r1]
	str r2, [r5]
	/* And align return address with 4. */
	orr lr, r4, #0x04
	/* Get the new process's stack as process stack. */
	ldr r0, [r2]
	/* Load back R4-R11 and LR. */
	ldmfd r0!, {r4-r11, lr}
	/* And give back the new process stack. */
	msr psp, r0
	/* Enable interrupt content now, atomic action ended. */
	cpsie i
	bx lr

	.thumb_func
switch_ready:
	cpsid i
	/* Get ready to set PendSV priority lowest. */
	movw r0, #:lower16:ARCH_PENDSV
	movt r0, #:upper16:ARCH_PENDSV

	movw r1, #:lower16:PENDSV_PRIO
	movt r1, #:upper16:PENDSV_PRIO
	str r1, [r0]

	/* Then switch to swap stack, which is the main stack. */
	movw r0, #:lower16:_swap_addr
	movt r0, #:upper16:_swap_addr
	ldr r1, [r0]

	/* Change to main stack. */
	msr msp, r1

	movw r0, #:lower16:curprio
	movt r0, #:upper16:curprio
	movw r1, #:lower16:wait_prio
	movt r1, #:upper16:wait_prio

	ldrb r2, [r1]
	strb r2, [r0]

	/* R0 is occupied, so use R1, and begin process switch. */
	movw r5, #:lower16:curproc
	movt r5, #:upper16:curproc
	movw r1, #:lower16:wait_proc
	movt r1, #:upper16:wait_proc

	ldr r2, [r1]
	str r2, [r5]

	/* Get the sp. */
	ldr r0, [r2]
	msr psp, r0

	mrs r0, control
	orr r0, r0, #0x02
	msr control, r0

	/* From P.429 in ARMv7-M_ARM:
	 * An ISB barrier instruction is required to ensure a control register
	 * write access takes effect before the next instruction is executed. */
	isb
	ldmfd sp!, {r4-r11, lr}
	ldmfd sp!, {r0-r3}
	/* NOTE: these two LR are different. */
	ldmfd sp!, {r12, lr}
	/* R1 and R2. */
	ldmfd sp!, {r1, r2}

	/* We are done. */
	cpsie i
	bx lr
	
	.end
