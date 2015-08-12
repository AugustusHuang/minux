#ifndef KERN_SYSTM_H
#define KERN_SYSTM_H

/* system level
 * TODO: Everytime we switch the level, call a trigger function and it will
 * change this variable. */
extern int system_level;
/* current process priority */
extern prio_t curprio;
/* highest waiting priority */
extern prio_t wait_prio;
/* system note */
extern char note[];
/* system panic string */
extern char panicstr[];
/* system version string */
extern char version[];
/* system call table */
typedef struct sysent *sysent;
struct sysent {
	int narg; /* number of arguments */
	int (*syscall)(); /* function */
};

extern int nsysent;

/* system tick frequency */
extern int hz;
/* system ticks */
extern int ticks;
/* system current time */
extern tm_t curtime;
/* 3 ipc attributes linked lists */
extern msg_queue_attr mqueue_attr;
extern sem_queue_attr semqueue_attr;
extern shm_queue_attr shmqueue_attr;

extern void panic(const string str);

#endif
