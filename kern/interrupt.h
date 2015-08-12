#ifndef KERN_INTERRUPT_H
#define KERN_INTERRUPT_H

/* nesting level of interrupt */
extern int interrupt_counter;

/* NOTE: Here we have to use an 'ugly' name because we want to override
 * the handlers defined to be default in startup file. */
void SysTick_Handler(void);
void PendSV_Handler(void);
void HardFault_Handler(void);

int intr_nest_enter(void);
int intr_nest_leave(void);

int interrupt_init(void);

#endif
