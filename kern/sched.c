#include "param.h"
#include "systm.h"
#include "process.h"
#include "sched.h"
#include "errno.h"

void scheduler()
{
	LSR();

	if (preempt_counter > 0)
		return;

	INTR_DISABLE();

	highprio = process_get_highest_prio()
	if (curprio <= highprio) {
		if (curproc == ) {
			INTR_ENABLE();
			return;
		}

		context_switch();
		INTR_ENABLE();
	}

	/* Since no process has higher priority than current one, remain running. */
	INTR_ENABLE();
	return;
}

void preempt_enable()
{
	LSR();
	preempt_counter++;
}

void preempt_disable()
{
	LSR();
	preempt_counter--;
}

void round_robin()
{
}

void round_robin_giveup()
{
}
