#include "param.h"
#include "systm.h"
#include "process.h"
#include "type.h"

static process process_alloc(uint32_t ssize);
static void process_free(process proc);

pid_t process_create(string name, prio_t prio, uint32_t ssize)
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
			errno = EPROCLIM;
			process_free(new_proc);
			INTR_ENABLE();
			return (pid_t) 0;
		}

		new_proc->pid = id;
		new_proc->prev = last_proc;
		last_proc->next = new_proc;
		new_proc->next = NULL;
		new_proc->stack_size = ssize;
		new_proc->text = ; /* FIXME */
		new_proc->time = ; /* FIXME */

		if (prio > PRIO_MAX) {
			errno = EPERM;
			INTR_ENABLE();
			return (pid_t) 0;
		}

		new_proc->prio = prio;
		new_proc->state = PROC_WAIT; /* Ready to run when created. */

		INTR_ENABLE();
		return (pid_t) new_proc->pid;
	} else {
		errno = ENOMEM;
		INTR_ENABLE();
		/* 0 means something went wrong since idle will be present till end. */
		return (pid_t) 0;
	}
}

void process_delete(pid_t pid)
{
	process proc;
	LSR();

	INTR_DISABLE();
	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		return;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			proc->prev->next = proc->next;
			proc->next->prev = proc->prev;
			process_free(proc);
			INTR_ENABLE();
			return;
		}
	}

	errno = ESRCH;
	INTR_ENABLE();
	return;
}

void process_prio_change(pid_t pid, prio_t new_prio)
{
	process proc;
	LSR();

	INTR_DISABLE();
	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		return;
	}

	if (new_prio > PRIO_MAX) {
		errno = EPERM;
		INTR_ENABLE();
		return;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			proc->prio = new_prio;
			INTR_ENABLE();
			return;
		}
	}

	errno = ESRCH;
	INTR_ENABLE();
	return;
}

uint32_t process_get_reg(pid_t pid, reg_t reg)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		/* TODO: How to tell apart 0 from 'real-0'? */
		return 0;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			/* TODO: Fetch the register content and return. */
			INTR_ENABLE();
			return ;
		}
	}

	errno = ESRCH;
	INTR_ENABLE();
	/* TODO: Where should we store the process-related registers? */
	return 0;
}

void process_set_reg(pid_t pid, reg_t reg, uint32_t value)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		return;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			/* TODO: Set the register content. */
			INTR_ENABLE();
			return;
		}
	}

	errno = ESRCH;
	INTR_ENABLE();
	return;
}

void process_sleep(pid_t pid, tm_t time)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		return;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
			/* TODO: Let's judge whether the process we wanna put to sleep
			 * is the current running process or not. */
			if (proc->state == PROC_RUN) {
			} else if (proc->state == PROC_WAIT) {
			} else {
				/* Do nothing since it's already sleeping. */
				return;
			}
		}
	}

	errno = ESRCH;
	INTR_ENABLE();
	return;
}

/* FIXME: If we wanna have process_resume as the reverse routine of 
 * process_sleep, where should we store the original state? */
void process_resume(pid_t pid)
{
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		return;
	}

	for (proc = proc_list; proc != NULL; proc = proc->next) {
		if (proc->pid == pid) {
		}
	}

	errno = ESRCH;
	INTR_ENABLE();
	return;
}

void process_idle()
{
	LSR();

	for (;;) { /* do nothing */ }
}

void process_clk()
{
}

void process_init()
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
}

void prio_enqueue(pid_t pid)
{
	prio_node n;
	process proc;
	LSR();

	INTR_DISABLE();

	if (pid > PID_MAX) {
		errno = EPROCLIM;
		INTR_ENABLE();
		return;
	}

	n = (prio_node) memory_alloc(sizeof(struct prio_node));
	
	if (n != NULL) {
		for (proc = proc_list; proc != NULL; proc = proc->next) {
			if (proc->pid == pid) {
				n->proc = proc;
				n->next = NULL;
				/* FIXME: consider when there's only one element */
				pqueue[proc->prio].tail->next = n;
				pqueue[proc->prio].tail = n;
				INTR_ENABLE();
				return;
			}
		}

		errno = ESRCH;
		INTR_ENABLE();
		return;
	} else {
		errno = ENOMEM;
		INTR_ENABLE();
		return;
	}
}

pid_t prio_dequeue(prio_t prio)
{
	process proc;
	LSR();

	INTR_DISABLE();
	if (prio > PRIO_MAX) {
		errno = EPERM;
		INTR_ENABLE();
		return 0;
	}

	if (pqueue[prio].head != NULL) {
		proc = pqueue[prio].head->proc;
		pqueue[prio].head = pqueue[prio].head->next;
		memory_free(pqueue[prio].head);
		INTR_ENABLE();
		return proc->pid;
	} else {
		errno = ESRCH;
		INTR_ENABLE();
		return 0;
	}
}

void prio_head2tail(prio_t prio)
{
	LSR();

	INTR_DISABLE();
	if (prio > PRIO_MAX) {
		errno = EPERM;
		INTR_ENABLE();
		return;
	}

	if (pqueue[prio].head != NULL) {
		if (pqueue[prio].head == pqueue[prio].tail) {
			/* do nothing */
			INTR_ENABLE();
			return;
		} else {
			pqueue[prio].tail->next = pqueue[prio].head;
			pqueue[prio].head = pqueue[prio].head->next;
			pqueue[prio].tail = pqueue[prio].tail->next;
			INTR_ENABLE();
			return;
		}
	} else {
		errno = ESRCH;
		INTR_ENABLE();
		return;
	}
}

/* Initialize the priority queue. */
void prio_init()
{
	int i;

	for (i = 0; i <= PRIO_MAX; i++) {
		pqueue[i].head = NULL;
		pqueue[i].tail = NULL;
	}
}

static process process_alloc(uint32_t ssize)
{
	process new_proc;
	uint32_t *stack;
	LSR();

#if (STACK_GROWTH == 1)
	{
		INTR_DISABLE();
		new_proc = (process) memory_alloc(sizeof(struct process));
		
		if (new_proc != NULL) {
			new_proc->stack_begin = (uint32_t *) memory_alloc(ssize);

			if (new_proc->stack_begin == NULL) {
				/* Allocation failed ... */
				memory_free(new_proc);
				new_proc = NULL;
			}
		}
	}
#else
	{
		INTR_DISABLE();
		stack = (uint32_t *) memory_alloc(ssize);

		if (stack != NULL) {
			new_proc = memory_alloc(sizeof(struct process));

			if (new_proc != NULL)
				new_proc->stack_begin = stack;
			else
				/* Allocation failed ... */
				memory_free(stack);
		} else
			new_proc = NULL;
	}
#endif

	INTR_ENABLE();
	return new_proc;
}

static void process_free(process proc)
{
	/* TODO */
}
