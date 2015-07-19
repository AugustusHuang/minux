#ifndef KERN_MEMORY_H
#define KERN_MEMORY_H

/* We once used original UN*X memory management here, but it will allocate
 * fixed amount of structures before use, and I don't think it's a good choice.
 */
typedef struct mapent *mapent;
struct mapent {
	mapent next;
	uint32_t size;
	void *addr;
};

extern uint32_t total_memory;
extern mapent map_list;

int memory_alloc(mapent m, uint32_t size);
void memory_free(mapent m);
void memory_init();

#endif
