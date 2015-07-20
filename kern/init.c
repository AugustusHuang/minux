#include "param.h"
#include "systm.h"
#include "errno.h"
#include "process.h"
#include "memory.h"
#include "sched.h"
#include "interrupt.h"
#include "type.h"
#include "ipc.h"
#include "config.h"

/* Only a prototype ... the complete one should be in the app code. */
int main()
{
	/* Default arguments settings ... */
	note = "";
	version = VERSION_CONFIG;
	errno = 0; /* by default set it to 0 */
	preempt_counter = 0;
	interrupt_counter = 0;
	curproc = (process) 0;
	curprio = (prio_t) 0;
	system_level = SYS_THREAD | SYS_PRIVILEGED;
	curtime = ; /* FIXME */

	/* Modules initializations ... */
	errno = process_init(); /* Initiate the idle and clock process. */
	if (errno != 0)
		panic("process_init");

	errno = memory_init(); /* Initiate the memory blocks. */
	if (errno != 0)
		panic("memory_init");

	errno = interrupt_init(); /* Initiate the interrupt service routines. */
	if (errno != 0)
		panic("interrupt_init");

	/* User defined processes and data structures initiated here ... */


	/* Once all defined, start to run the scheduler, and it will contain
	 * an infinite loop! */
	scheduler();

	/* Won't reach here ... */
	return 0;
}
