#include "fs.h"
#include "../kern/errno.h"

int bit_vector_set(bit_vector bv, int index)
{
	int i;

	if (index < 0 || index >= bv->len)
		return EINVAL;

	/* The 'index'th bit will be in the 'index / sizeof(int)'th int,
	 * and at the 'index % sizeof(int)' th bit position. */
	bv->vec[index / sizeof(int)] |= (1 << (index % sizeof(int)));
	if (bv->free == index)
		for (i = index / sizeof(int); i < 
	return ENONE;
}

int bit_vector_unset(bit_vector bv, int index)
{
	int i;

	if (index < 0 || index >= bv->len)
		return EINVAL;

	i = index / sizeof(int);
	bv->vec[i] &= ~(1 << (index % sizeof(int)));
	bv->free = i;

	return ENONE;
}

int bit_vector_query(bit_vector bv, int index)
{
}

int bit_vector_set_m(bit_vector bv, int from, int to)
{
}

int bit_vector_unset_m(bit_vector bv, int from, int to)
{
}

int bit_vector_query_m(bit_vector bv, int from, int to)
{
}

int bit_vector_get_longest(bit_vector bv)
{
}

int bit_vector_init()
{
}

