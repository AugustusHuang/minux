#ifndef _IPC_H_
#define _IPC_H_

typedef struct lock_proto *lock_proto;
struct lock_proto {
	string name;
	uint32_t flag;
	uint32_t data;
};

typedef struct mutex *mutex;
struct mutex {
	struct lock_proto lock;
	volatile uintptr_t mtx; /* FIXME: Maybe another data type? */
};

typedef struct mqueue_attr *mqueue_attr;
struct mqueue_attr {
	uint32_t flag;
	uint32_t maximum;
	uint32_t msgsize;
	uint32_t curmsgs;
};

#endif
