#ifndef KERN_MEMORY_H
#define KERN_MEMORY_H

/* We use original UN*X memory management here,
 * maybe changed when uxxx_fs is done. */
typedef struct mapent *mapent;
struct mapent {
	void *size;
	void *addr;
};

int memory_alloc(mapent m, int size);
void memory_free(mapent m, int size, int);
void memory_init();

#endif
