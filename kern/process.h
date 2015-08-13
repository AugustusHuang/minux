/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Huang Xuxing
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software")
 * to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * process.h
 * Declarations of process module data structures and routines,
 * global variables are declared in order to fast fetch current running
 * process and current highest ready process.
 */
				  
#ifndef KERN_PROCESS_H
#define KERN_PROCESS_H

/* Process double link:
 * In order to fast fetch swapped in process's stack pointer, make it the
 * first slot in the process structure, so (int32_t)[R0] will be sp_current
 * if R0 stores the address of the process structure swapped in.
 * ---------    ---------           ---------
 * | proc1 |    | proc2 |           | procn |
 * ---------    ---------           ---------
 * |  sp1  |    |  sp2  |           |  spn  |
 * ---------    ---------           ---------
 * | other |    | other |           | other |
 * | slots |    | slots |           | slots |
 * ---------    ---------           ---------
 * | prev  |<---+- prev |<---...<---+- prev |
 * ---------    ---------           ---------
 * | next -+--->| next -+--->...--->| next  |
 * ---------    ---------           ---------
 * | other |    | other |           | other |
 * | slots |    | slots |           | slots |
 * ---------    ---------           ---------
 * | prioa |    | priob |           | prioz |
 * ---------    ---------           ---------
 * |  RUN  |    | WAIT  |           | SLEEP |
 * ---------    ---------           --------- */

typedef struct process *process;
struct process {
	int32_t sp; /* updated when switched out */
	char name[CONFIG_PROCESS_NAME_LENGTH];
	pid_t pid;
	process prev;
	process next; /* ranked by pid */
	int32_t stack_begin;
	uint32_t stack_size;
	/* pointer to function */
	void (*func)();
	/* How long since last switch (automatically) or sleep (manually),
	 * when switched in to run, accumulate it, state is RUN,
	 * when switched out, clear it to 0, state is WAIT,
	 * when made to sleep, set to the total sleep time and count down to 0,
	 * state is SLEEP,
	 * when resumed or reach 0, change state to WAIT and reset it to 0. */
	tm_t time;
	/* Priority ranged from 0 to CONFIG_MAX_PRIO. */
	prio_t prio;
	/* State can be one of RUN, WAIT and SLEEP. */
	int state;
	/* Slot used to multiple return. */
	int retval;
};

/* Priority queue: nodes are single linked list.
 * ----           ----------------------------------
 * | -+---------->| node01 | node02 | node03 | ... |
 * ----           ----------------------------------
 * | -+---------->| node11 | node12 |
 * ----           -------------------
 * ....
 * ----           -----------------------------
 * | -+---------->| node(PRIO_MAX - 1)1 | ... |
 * ----           -----------------------------
 * | -+---------->| node(PRIO_MAX)1 |
 * ----           ------------------- */

typedef struct prio_queue *prio_queue;
struct prio_queue {
	prio_node head;
	prio_node tail;
};

typedef struct prio_node *prio_node;
struct prio_node {
	process proc;
	prio_node next;
};

/* FIXME: the last argument maybe superfluous if we allocate all functions
 * in .text section and of course, the process itself will be there. */
int process_create(char *name, prio_t prio, uint32_t ssize, int (*func)());
int process_delete(pid_t pid);

int process_prio_change(pid_t pid, prio_t new_prio);

/* return register value will be stored in ptr */
int process_get_reg(pid_t pid, reg_t reg, int32_t *ptr);
int process_set_reg(pid_t pid, reg_t reg, int32_t value);

int process_sleep(pid_t pid, tm_t time);
int process_resume(pid_t pid);

/* idle and tick process routine */
int process_idle(void);
int process_tick(void);

/* initialization */
int process_init(void);

/* prio_queue manipulations */
int prio_enqueue(pid_t pid);
int prio_dequeue(prio_t prio);
int prio_head2tail(prio_t prio);

int prio_init(void);

/* All the global variables below will lie in the .bss area. */
/* current running process */
extern process curproc;
/* current waiting process */
extern process wait_proc;
/* process double-linked list */
extern process proc_list;
/* Idle process static structure, will have pid = 0, lowest priority. */
extern struct process proc_idle;
/* Tick process static structure, will have pid = 1, high priority. */
extern struct process proc_tick;
/* Mine process static structure, will have pid = 2 if enabled, low priority. */
#ifdef CONFIG_PROC_MINE
extern struct process proc_mine;
#endif

/* current processes numbers */
extern uint32_t nprocs;

/* current priority queue */
extern struct prio_queue pqueue[CONFIG_MAX_PRIO + 1];

#endif
