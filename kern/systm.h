#ifndef _SYSTM_H_
#define _SYSTM_H_

/* system level */
extern int system_level;
/* current process priority */
extern prio_t curprio;
/* highest waiting priority */
extern prio_t highprio;
/* physical memory */
extern int physmem;
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
extern struct sysent sysent[];

extern int nsysent;

/* system tick frequency */
extern int hz;
extern int tick;

#endif