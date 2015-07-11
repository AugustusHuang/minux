#ifndef KERN_INTERRUPT_H
#define KERN_INTERRUPT_H

/* nesting level of interrupt */
extern int interrupt_counter;

#define NINTR 32 /* FIXME */

void intr_systick(void);
void intr_pendsv(void);

void intr_nest_enter(void);
void intr_nest_leave(void);

void interrupt_init(void);

#endif
