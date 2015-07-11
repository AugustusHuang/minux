#ifndef KERN_MEMORY_H
#define KERN_MEMORY_H

/* We use original UN*X memory management here,
 * maybe changed when uxxx_fs is done. */
typedef struct map *map;
struct map {
	char *name;
	mapent limit;
};

typedef struct mapent *mapent;
struct mapent {
	int size;
	int addr;
};

int memory_alloc(map m, int size);
void memory_free(map m, int, int);
void memory_init();

#endif
