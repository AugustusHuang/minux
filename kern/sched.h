#ifndef KERN_SCHED_H
#define KERN_SCHED_H

/* preempt counter */
extern int preempt_counter;

void scheduler_init(void);
void preempt_enable(void);
void preempt_disable(void);

void round_robin(void);
void round_robin_giveup(void);

#endif
