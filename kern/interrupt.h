#ifndef _INTERRUPT_H_
#define _INTERRUPT_H_

/* nesting level of interrupt */
extern int interrupt_counter;

#define NINTR 32 /* FIXME */

void intr_systick(void);
void intr_pendsv(void);

void intr_nest_enter(void);
void intr_nest_leave(void);

void interrupt_init(void);

#endif
