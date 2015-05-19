#ifndef _IPC_H_
#define _IPC_H_

typedef struct ipc_queue *ipc_queue;
struct ipc_queue {
	pid_t master;
	pid_t slave;
	uint8_t mode;
};

#endif
