#ifndef KERN_IPC_H
#define KERN_IPC_H

#define IPC_STAT 1
#define IPC_SET  2
#define IPC_RMID 3

/* General ipc key and mode informations, since users and groups are not
 * supported, they won't be present here. */
typedef struct ipc *ipc;
struct ipc {
	mode_t mode;
	key_t key;
};

/* Message queue attribute structure, one to one message queue. */
typedef struct msg_queue_attr *msg_queue_attr;
struct msg_queue_attr {
	struct ipc msg_ipc;
	msg first;
	msg last;
	uint32_t total_bytes;
	uint32_t total_msgs;
	/* The maximal size of messages in queue. */
	uint32_t max_bytes;
	pid_t last_spid; /* last send pid */
	pid_t last_rpid; /* last receive pid */
	tm_t stime; /* last send time */
	tm_t rtime; /* last receive time */
	tm_t ctime; /* last control time */
};

/* Message, contains messages sent or received by processes. */
typedef struct msg *msg;
struct msg {
	msg next;
	char text[1];
};

typedef struct sem_queue_attr *sem_queue_attr;
struct sem_queue_attr {
	struct ipc sem_ipc;
	sem first;
	uint16_t total_sems;
	tm_t otime; /* last operation time */
	tm_t ctime; /* last change time */
};

typedef struct sem *sem;
struct sem {
	pid_t lopid; /* last operation pid */
	uint16_t val; /* semaphore value >= 0 */
	uint16_t zcount; /* processes awaiting val == 0 */
	uint16_t ncount; /* processes awaiting val > curval */
};

typedef struct sem_buf *sem_buf;
struct sem_buf {
	uint16_t num;
	int16_t op;
	mode_t flag;
};

union sem_un {
	int val; /* SETVAL */
	sem_queue_attr attr; /* IPC_STAT or IPC_SET */
	uint16_t *array; /* GETALL or SETALL */
};

/* sem queue cmd arguments */
#define GETVAL  4
#define SETVAL  5
#define GETPID  6
#define GETNCNT 7
#define GETZCNT 8
#define GETALL  9
#define SETALL  10

typedef struct shm_queue_attr *shm_queue_attr;
struct shm_queue_attr {
	struct ipc shm_ipc;
	size_t size; /* size of segment */
	pid_t lopid; /* last operation pid */
	pid_t cpid; /* creator pid */
	uint16_t attach; /* current attaches */
	tm_t atime; /* last attach time */
	tm_t dtime; /* last detach time */
	tm_t ctime; /* last control time */
};

/* shm queue cmd arguments */
#define SHM_LOCK   4
#define SHM_UNLOCK 5

/* Send a message to a message queue. */
extern int msg_send(int msg_id, const void *ptr, size_t size, mode_t flag);
/* Receive a message from a message queue. */
extern int msg_recv(int msg_id, void *ptr, size_t size, mode_t flag);
/* Open an existing message queue or create a new one. */
extern int msg_init(key_t key, mode_t flag);
/* Different commands to a specified message queue. */
extern int msg_ctrl(int msg_id, int cmd, msg_queue_attr attr);

/* Performs an array of operations on a set of semaphores. */
extern int sem_op(int sem_id, sem_buf buf, size_t nops);
/* If count == 0, we are referring to an existing sem, or create a new one. */
extern int sem_init(key_t key, int count, mode_t flag);
/* Different commands to a specified semaphore. count lies between 0 and N-1. */
extern int sem_ctrl(int sem_id, int count, int cmd, union semun args);

/* Shared memory attach function. */
extern void *shm_at(int shm_id, const void *addr, mode_t flag);
/* Shared memory detach function. */
extern int shm_dt(const void *addr);
/* Get a shared memory identifier. */
extern int shm_init(key_t key, size_t size, mode_t flag);
/* Different commands to a specified area of shared memory. */
extern int shm_ctrl(int shm_id, int cmd, shm_queue_attr attr);

#endif
