#include "param.h"
#include "systm.h"
#include "process.h"
#include "ipc.h"
#include "type.h"

static msg_init()
{
}

static sem_init()
{
}

static shm_init()
{
}

int msg_send(int msg_id, const void *ptr, size_t size, mode_t flag)
{
}

int msg_recv(int msg_id, void *ptr, size_t size, mode_t flag)
{
}

int msg_get(key_t key, mode_t flag)
{
}

int msg_ctrl(int msg_id, int cmd, msg_queue_attr attr)
{
}

int sem_op(int sem_id, sem_buf buf, size_t nops)
{
}

int sem_get(key_t key, int count, mode_t flag)
{
}

int sem_ctrl(int sem_id, int count, int cmd, union semun args)
{
}

void *shm_at(int shm_id, const void *addr, mode_t flag)
{
}

int shm_dt(const void *addr)
{
}

int shm_get(key_t key, size_t size, mode_t flag)
{
}

int shm_ctrl(int shm_id, int cmd, shm_queue_attr attr)
{
}

int ipc_init()
{
	if (msg_init() != 0)
		panic("msg_init");
	if (sem_init() != 0)
		panic("sem_init");
	if (shm_init() != 0)
		panic("shm_init");

	return ENONE;
}
