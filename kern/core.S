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
.global intr_pendsv

/* PendSV interrupt register address. */
.equ ARCH_PENDSV, 0xe000ed22
/* Set PendSV to lowest priority to ensure we call it in Thread mode
 * and from main stack. */
.equ PENDSV_PRIO, 0xff
/* PendSV ISR trigger. */
.equ PENDSV_TRIG,  0x10000000

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
intr_pendsv:
	cpsid i
	mrs r0, psp

	stmfd r0!, {r4-r11, r14}
	movw r5, #:lower16:curproc
	movt r5, #:upper16:curproc

	ldr r6, [r5]
	str r0, [r6]

	mov r4, lr
	movw r0, #:lower16:curprio
	movt r0, #:upper16:curprio

	movw r1, #:lower16:wait_prio
	movt r1, #:upper16:wait_prio

	ldrb r2, [r1]
	strb r2, [r0]

	movw r1, #:lower16:wait_proc
	movt r1, #:upper16:wait_proc

	ldr r2, [r1]
	str r2, [r5]
	orr lr, r4, #0x04
	ldr r0, [r2]
	ldmfd r0!, {r4-r11, r14}
	msr psp, r0
	cpsie i
	bx lr

.thumb_func
switch_ready:


.end
