#include "param.h"
#include "systm.h"
#include "process.h"
#include "memory.h"

/* for memmove */
#include <string.h>

#ifdef MEMORY_SIZE_CONFIG
#define MEMORY_SIZE MEMORY_SIZE_CONFIG
#else
#define MEMORY_SIZE 256U
#endif

int memory_alloc(mapent m, uint32_t size)
{
	if (raw_memory < size)
		return ENOMEM;

	/* We have enough memory! Make a new mapent and link it to the end of
	 * the memory map list. */
	mapent slot;
	/* After the loop slot points to the last map entry. */
	for (slot = map_list; slot->next != NULL; slot = slot->next);
	slot->next = m;
	m->size = size;
	m->next = NULL;
	/* Fetch the address from the linear memory address. */
	m->addr = &memory_array[MEMORY_SIZE - raw_memory];

	raw_memory -= size;
	return ENONE;
}

/* Since map entries are single-linked, we only need to free entry. */
void memory_free(mapent m)
{
	mapend slot;

	/* Trivial case, remove it from the tail and add to raw memory. */
	if (m->next == NULL)
		for (slot = map_list; slot->next != m; slot = slot->next)
			slot->next = NULL;

	/* m lies in between. */
	else {
		/* Like what UN*X does, make those two memory fractions one. */
		memmove(m->addr, m->next->addr, &memory_array[MEMORY_SIZE - raw_memory]
				- (char *)m->next->addr);

		for (slot = m->next; slot != NULL; slot = slot->next)
			slot->addr = (void *)((char *)m->addr - m->size);

		for (slot = map_list; slot->next != m; slot = slot->next) {
			slot->next = m->next;
			m->next = NULL;
		}
	}
	
	raw_memory += m->size;
}

void memory_init()
{
	raw_memory = MEMORY_SIZE;
	/* At the very beginning raw_memory will be the one and only. */
	map_list = NULL;
}
