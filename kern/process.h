#ifndef KERN_PROCESS_H
#define KERN_PROCESS_H

/* Process double link:
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
 * ---------    ---------           ---------
 * */
typedef struct process *process;
struct process {
	uint32_t sp;
	string name;
	pid_t pid;
	process prev;
	process next; /* ranked by pid */
	uint32_t *stack_begin;
	uint32_t stack_size;
	void *text;
	tm_t time;
	prio_t prio;
	uint8_t state;
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
 * | -+---------->| node(PRIO_MAX) |
 * ----           ------------------
 */
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

/* return pid */
pid_t process_create(string name, prio_t prio, uint32_t ssize);
void process_delete(pid_t pid);

void process_prio_change(pid_t pid, prio_t new_prio);

/* return register value */
uint32_t process_get_reg(pid_t pid, reg_t reg);
void process_set_reg(pid_t pid, reg_t reg, uint32_t value);

void process_sleep(pid_t pid, tm_t time);
void process_resume(pid_t pid);

/* idle and clk process routine */
void process_idle(void);
void process_clk(void);

/* initialization */
void process_init(void);

/* prio_queue manipulations */
void prio_enqueue(pid_t pid);
pid_t prio_dequeue(prio_t prio);
void prio_head2tail(prio_t prio);

void prio_init(void);

/* current running process */
extern process curproc;
/* process double-linked list */
extern process proc_list;
/* idle process static structure, will have pid = 0, lowest priority */
extern struct process proc_idle;
/* clk process static structure, will have pid = 1, high priority */
extern struct process proc_clk;
/* current running processes numbers */
extern uint32_t nprocs;
/* current priority queue */
extern struct prio_queue pqueue[PRIO_MAX + 1];

#endif
