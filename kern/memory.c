#include "param.h"
#include "systm.h"
#include "process.h"
#include "memory.h"

int memory_alloc(mapent m, int size)
{
	mapent m2;
	int a;

	for (m2 = m; m2->size; m2++) {
		if (m2->size >= size) {
			a = m2->addr;
			m2->addr += size;
			if ((m2->size -= size) == 0)
				do {
					m2++;
					(m2 - 1)->addr = m2->addr;
				} while ((m2 - 1)->size = m2->size);
			errno = ENONE;
			return a;
		}
	}

	errno = ENOMEM;
	return 0;
}

void memory_free(mapent m, int size, int addr)
{
	mapent m2;
	int temp;
	int a = addr;

	/* find the mapent which contains address a. */
	for (m2 = m; m2->addr <= a && m2->size; m2++);

	if (m2 > m && (m2 - 1)->addr + (m2 - 1)->size == a) {
		(m2 - 1)->size += size;
		if (a + size == m2->addr) {
			(m2 - 1)->size += m2->size;
			while (m2->size) {
				m2++;
				(m2 - 1)->addr = m2->addr;
				(m2 - 1)->size = m2->size;
			}
		}
	} else {
		if (a + size == m2->addr && m2->size) {
			m2->addr -= size;
			m2->size += size;
		} else if (size)
			do {
				temp = m2->addr;
				m2->addr = a;
				a = temp;
				temp = m2->size;
				m2->size = size;
				m2++;
			} while (size = temp);
	}
}

void memory_init()
{
	/* TODO: initialize a 'core' memory unit. */
}
