#ifndef _SCHED_H_
#define _SCHED_H_

/* preempt counter */
extern int preempt_counter;

void scheduler(void);
void preempt_enable(void);
void preempt_disable(void);

void round_robin(void);
void round_robin_giveup(void);

#endif
