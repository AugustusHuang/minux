#include "param.h"
#include "systm.h"
#include "process.h"
#include "type.h"
#include "memory.h"

static process process_alloc(uint32_t ssize);
static void process_free(process proc);
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

int process_clk()
{
	LSR();

	for (;;) {
		/* clock. */
	}

	return ENONE;
}

int process_init()
{
	/* Firstly, we make the idle process. */
	proc_idle.sp = 0; /* TODO */
	proc_idle.name = "idle";
	proc_idle.pid = 0;
	proc_idle.prev = NULL;
	proc_idle.next = NULL;
	proc_idle.stack_begin = 0; /* TODO */
	proc_idle.stack_size = IDLE_STACK_SIZE;
	proc_idle.text = &process_idle;
	proc_idle.time = 0; /* Never give up. */
	proc_idle.prio = PRIO_IDLE;
	proc_idle.state = PROC_RUN;
	nprocs = 1;

	/* Then the clk process. */
	proc_clk.sp = 0; /* TODO */
	proc_clk.name = "clk";
	proc_clk.pid = 1;
	proc_clk.prev = &proc_idle;
	proc_idle.next = &proc_clk;
	proc_clk.stack_begin = 0; /* TODO */
	proc_clk.stack_size = CLK_STACK_SIZE;
	proc_clk.text = &process_clk;
	proc_clk.time = 0; /* Never give up. */
	proc_clk.prio = PRIO_CLK; /* should be higher than idle's */
	proc_clk.state = PROC_WAIT;
	nprocs++;

	curproc = &proc_idle;

	prio_enqueue(proc_idle.pid);
	prio_enqueue(proc_clk.pid);

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

	n = (prio_node) memory_alloc(m, sizeof(struct prio_node));
	
	if (n != NULL) {
		for (proc = proc_list; proc != NULL; proc = proc->next) {
			if (proc->pid == pid) {
				n->proc = proc;
				n->next = NULL;
				/* FIXME: consider when there's only one element */
				pqueue[proc->prio].tail->next = n;
				pqueue[proc->prio].tail = n;
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
		memory_free(pqueue[prio].head);
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
	mapent mem, mem2;
	process new_proc;
	uint32_t *stack;
	LSR();

#if (STACK_GROWTH == 1)
	{
		INTR_DISABLE();
		new_proc = (process) memory_alloc(mem, sizeof(struct process));
		
		if (new_proc != NULL) {
			new_proc->stack_begin = (uint32_t *) memory_alloc(mem2, stack_size);

			if (new_proc->stack_begin == NULL) {
				/* Allocation failed ... */
				memory_free(mem);
				new_proc = NULL;
			}
		}
	}
#else
	{
		INTR_DISABLE();
		stack = (uint32_t *) memory_alloc(mem2, stack_size);

		if (stack != NULL) {
			new_proc = memory_alloc(mem, sizeof(struct process));

			if (new_proc != NULL)
				new_proc->stack_begin = stack;
			else
				/* Allocation failed ... */
				memory_free(mem);
		} else
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
		if (m->addr <= proc && ((char *)m->addr + m->size) >= proc)
			memory_free(m);

	for (m = map_list; m != NULL; m = m->next)
		if (m->addr <= proc->stack_begin && m->size >= proc->stack_size)
			memory_free(m);

	INTR_ENABLE();
}

static void pnode_free(prio_node node)
{
	/* Free its memory entry. */
	mapent m;
	LSR();

	INTR_DISABLE();
	for (m = map_list; m != NULL; m = m->next)
		if (m->addr <= node && ((char *)m->addr + m->size) >= node)
			memory_free(m);

	INTR_ENABLE();
}
