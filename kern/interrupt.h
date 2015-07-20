#ifndef KERN_INTERRUPT_H
#define KERN_INTERRUPT_H

/* nesting level of interrupt */
extern int interrupt_counter;

int intr_systick(void);
int intr_pendsv(void);

int intr_nest_enter(void);
int intr_nest_leave(void);

int interrupt_init(void);

#endif
