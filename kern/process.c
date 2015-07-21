#include "param.h"
#include "systm.h"
#include "process.h"
#include "type.h"
#include "memory.h"
#include "errno.h"

static process process_alloc(uint32_t ssize);
static void process_free(process proc);
static prio_node pnode_alloc();
static void pnode_free(prio_node node);

int process_create(string name, prio_t prio, uint32_t ssize)
{
	process new_proc, last_proc;
	pid_t id;
	LSR();
	
	INTR_DISABLE();
	new_proc = process_alloc(ssize);
	if (new_proc != NULL) {
		new_proc->sp = new_proc->stack_begin;
		new_proc->name = name;

		for (last_proc = proc_list; last_proc->next != NULL;
				last_proc = last_proc->next) {
			/* Now last_proc point to the last process */
		}
		if ((id = last_proc->pid + 1) > PID_MAX) {
			process_free(new_proc);
			INTR_ENABLE();
			return ESRCH;
		}

		new_proc->pid = id;
		new_proc->prev = last_proc;
		last_proc->next = new_proc;
		new_proc->next = NULL;
		new_proc->stack_size = ssize;
		new_proc->text = ; /* FIXME */
		new_proc->time = ; /* FIXME */

		if (prio > PRIO_MAX) {
			INTR_ENABLE();
			return EPERM;
		}

		new_proc->prio = prio;
		new_proc->state = PROC_WAIT; /* Ready to run when created. */

		INTR_ENABLE();
		return ENONE;
	} else {
		INTR_ENABLE();
		return ENOMEM;
	}
}

int process_delete(pid_t pid)
{
	process proc;
	LSR();

	INTR_DISABLE();
	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			proc->prev->next = proc->next;
			proc->next->prev = proc->prev;
			process_free(proc);
			INTR_ENABLE();
			return ENONE;
		}
	}

	INTR_ENABLE();
	return ESRCH;
}

int process_prio_change(pid_t pid, prio_t new_prio)
{
	process proc;
	LSR();

	INTR_DISABLE();
	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	if (new_prio > PRIO_MAX) {
		INTR_ENABLE();
		return EPERM;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			proc->prio = new_prio;
			INTR_ENABLE();
			return ENONE;
		}
	}

	INTR_ENABLE();
	return ESRCH;
}

int process_get_reg(pid_t pid, reg_t reg, uint32_t *ptr)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	if (reg > REG_MAX) {
		INTR_ENABLE();
		return EINVAL;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			/* TODO: Fetch the register content and return. */
			INTR_ENABLE();
			return ENONE;
		}
	}

	INTR_ENABLE();
	/* TODO: Where should we store the process-related registers? */
	return ESRCH;
}

int process_set_reg(pid_t pid, reg_t reg, uint32_t value)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	if (reg > REG_MAX) {
		INTR_ENABLE();
		return EINVAL;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			/* TODO: Set the register content. */
			INTR_ENABLE();
			return ENONE;
		}
	}

	INTR_ENABLE();
	return ESRCH;
}

int process_sleep(pid_t pid, tm_t time)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			/* TODO: Let's judge whether the process we wanna put to sleep
			 * is the current running process or not. */
			if (proc->state == PROC_RUN) {
			} else if (proc->state == PROC_WAIT) {
			} else {
				/* Do nothing since it's already sleeping. */
				return ENONE;
			}
		}
	}

	INTR_ENABLE();
	return ESRCH;
}

/* FIXME: If we wanna have process_resume as the reverse routine of 
 * process_sleep, where should we store the original state? */
int process_resume(pid_t pid)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
		}
	}

	INTR_ENABLE();
	return ESRCH;
}

int process_idle()
{
	LSR();

	for (;;) { /* do nothing */ }

	/* Never here. */
	return ENONE;
}

int process_tick()
{
	LSR();

	for (;;) {
		/* tick. */
	}

	return ENONE;
}

int process_init()
{
	/* Firstly, we make the idle process. */
	mapent map1, map2;
	if (errno = memory_alloc(map1, IDLE_STACK_SIZE))
		return errno;
	if (errno = memory_alloc(map2, TICK_STACK_SIZE))
		return errno;
	/* sp will point to the very beginning of the stack. */
	proc_idle.sp = map1->addr;
	proc_idle.name = "idle";
	proc_idle.pid = 0;
	proc_idle.prev = NULL;
	proc_idle.next = NULL;
	proc_idle.stack_begin = map1->addr;
	proc_idle.stack_size = IDLE_STACK_SIZE;
	proc_idle.text = &process_idle;
	proc_idle.time = 0; /* Never give up. */
	proc_idle.prio = PRIO_IDLE;
	proc_idle.state = PROC_RUN;
	nprocs = 1;

	/* Then the tick process. */
	tick = 0;
	proc_tick.sp = map2->addr;
	proc_tick.name = "tick";
	proc_tick.pid = 1;
	proc_tick.prev = &proc_idle;
	proc_idle.next = &proc_tick;
	proc_tick.stack_begin = map2->addr;
	proc_tick.stack_size = TICK_STACK_SIZE;
	proc_tick.text = &process_tick;
	proc_tick.time = 0; /* Never give up. */
	proc_tick.prio = PRIO_TICK; /* should be higher than idle's */
	proc_tick.state = PROC_WAIT;
	nprocs++;

	curproc = &proc_idle;

	errno = prio_init();
	if (errno != 0)
		panic("prio_init");

	prio_enqueue(proc_idle.pid);
	prio_enqueue(proc_tick.pid);

	return ENONE;
}

int prio_enqueue(pid_t pid)
{
	prio_node n;
	process proc;
	mapent m;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		INTR_ENABLE();
		return ESRCH;
	}

	n = pnode_alloc();
	
	if (n != NULL) {
		for (proc = proc_list; proc != NULL; proc = proc->next) {
			if (proc->pid == pid) {
				n->proc = proc;
				n->next = NULL;
				if (pqueue[proc->prio].head == NULL) {
					/* Prio queue of this level is empty */
					pqueue[proc->prio].head = n;
					pqueue[proc->prio].tail = n;
				} else {
					/* Current prio queue is not empty. */
					pqueue[proc->prio].tail->next = n;
					pqueue[proc->prio].tail = n;
				}
				INTR_ENABLE();
				return ENONE;
			}
		}

		INTR_ENABLE();
		return ESRCH;
	} else {
		INTR_ENABLE();
		return ENOMEM;
	}
}

int prio_dequeue(prio_t prio)
{
	process proc;
	LSR();

	INTR_DISABLE();
	if (prio > PRIO_MAX) {
		INTR_ENABLE();
		return EPERM;
	}

	if (pqueue[prio].head != NULL) {
		proc = pqueue[prio].head->proc;
		pqueue[prio].head = pqueue[prio].head->next;
		pnode_free(pqueue[prio].head);
		INTR_ENABLE();
		return ENONE;
	} else {
		INTR_ENABLE();
		return ESRCH;
	}
}

int prio_head2tail(prio_t prio)
{
	LSR();

	INTR_DISABLE();
	if (prio > PRIO_MAX) {
		INTR_ENABLE();
		return EPERM;
	}

	if (pqueue[prio].head != NULL) {
		/* Prio queue of this level is not empty. */
		if (pqueue[prio].head == pqueue[prio].tail) {
			/* do nothing */
			INTR_ENABLE();
			return ENONE;
		} else {
			pqueue[prio].tail->next = pqueue[prio].head;
			pqueue[prio].head = pqueue[prio].head->next;
			pqueue[prio].tail = pqueue[prio].tail->next;
			INTR_ENABLE();
			return ENONE;
		}
	} else {
		INTR_ENABLE();
		return ESRCH;
	}
}

/* Initialize the priority queue. */
int prio_init()
{
	int i;

	for (i = 0; i <= PRIO_MAX; i++) {
		pqueue[i].head = NULL;
		pqueue[i].tail = NULL;
	}

	return ENONE;
}

static process process_alloc(uint32_t stack_size)
{
	int error;
	mapent mem, mem2;
	process new_proc;
	LSR();

#if (STACK_GROWTH == 1)
	{
		INTR_DISABLE();
		error = memory_alloc(mem, sizeof(struct process));
		
		if (!error) {
			/* Process struct allocation succeed. */
			new_proc = (process)mem->addr;
			error = memory_alloc(mem2, stack_size);

			if (error) {
				/* Stack allocation failed. */
				memory_free(mem);
				new_proc = NULL;
			}

			/* Stack allocation succeed. */
			new_proc->stack_start = mem2->addr;
		}

		/* Process struct allocation failed. */
		new_proc = NULL;
	}
#else
	{
		INTR_DISABLE();
		error = memory_alloc(mem2, stack_size);

		if (!error) {
			/* Stack allocation succeed. */
			error = memory_alloc(mem, sizeof(struct process));

			if (!error) {
				/* Process struct allocation succeed. */
				new_proc = (process)mem->addr;
				new_proc->stack_start = mem2->addr;
			}
			else
				/* Process struct allocation failed. */
				memory_free(mem2);
		} else
			/* Stack allocation failed. */
			new_proc = NULL;
	}
#endif

	INTR_ENABLE();
	return new_proc;
}

static void process_free(process proc)
{
	/* Free its memory entry. */
	mapent m;
	LSR();

	/* If a map entry has proc between addr and addr + size, then free it.
	 * The process stack will be manipulated the same way. */
	INTR_DISABLE();
	for (m = map_list; m != NULL; m = m->next)
		if ((uintptr_t)m->addr <= (uintptr_t)proc &&
				((uintptr_t)((char *)m->addr + m->size)) >= (uintptr_t)proc)
			memory_free(m);

	for (m = map_list; m != NULL; m = m->next)
		if ((uintptr_t)m->addr <= (uintptr_t)proc->stack_begin &&
				m->size >= proc->stack_size)
			memory_free(m);

	INTR_ENABLE();
}

static prio_node pnode_alloc()
{
	int error;
	mapent m;
	prio_node pnode;
	LSR();

	INTR_DISABLE();
	error = memory_alloc(m, sizeof(struct prio_node));
	if (!error) {
		/* Allocation succeed. */
		pnode = (prio_node)m->addr;
	} else
		pnode = NULL;
	INTR_ENABLE();
	return pnode;
}

static void pnode_free(prio_node node)
{
	/* Free its memory entry. */
	mapent m;
	LSR();

	INTR_DISABLE();
	for (m = map_list; m != NULL; m = m->next)
		if ((uintptr_t)m->addr <= (uintptr_t)node &&
				((uintptr_t)((char *)m->addr + m->size)) >= (uintptr_t)node)
			memory_free(m);

	INTR_ENABLE();
}
