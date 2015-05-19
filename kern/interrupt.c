#include "param.h"
#include "systm.h"
#include "process.h"
#include "interrupt.h"
#include "type.h"

void intr_systick()
{
	LSR();

	INTR_DISABLE();
	intr_nest_enter();
	INTR_ENABLE();

	/* TODO: systick routine */

	intr_nest_leave();
}

void intr_nest_enter()
{
	if (interrupt_counter >= INTR_NEST_MAX)
		return;

	interrupt_counter++;
}

void intr_nest_leave()
{
	LSR();

	INTR_DISABLE();
	if (interrupt_counter == 0) {
		INTR_ENABLE();
		return;
	}

	interrupt_counter--;

	if (interrupt_counter == 0) {
		INTR_ENABLE();
		return;
	}

	context_switch_i();

	INTR_ENABLE();
}

void interrupt_init()
{
	interrupt_counter = 0;
}
