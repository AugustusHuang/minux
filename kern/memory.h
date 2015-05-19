#ifndef _MEMORY_H_
#define _MEMORY_H_

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
void memory_init(map m, int, int, char *, int);

#endif
