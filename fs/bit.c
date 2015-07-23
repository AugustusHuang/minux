#include "fs.h"
#include "../kern/errno.h"

int bit_vector_set(bit_vector bv, int index)
{
	int i, j, nth_int, nth_bit;

	if (index < 0 || index >= bv->len)
		return EINVAL;

	nth_int = index / sizeof(int);
	nth_bit = index % sizeof(int);
	/* Search all bits after, find one 0. */
	if (bv->free == index) {
		for (i = nth_bit + 1; i < sizeof(int); i++)
			if ((bv->vec[nth_int] | 1 << i) == 0)
				bv->free = nth_int * sizeof(int) + i;

		/* And the consecutive integers. */
		for (i = nth_int; i < bv->len / sizeof(int); i++)
			for (j = 0; j < sizeof(int); j++)
				if ((bv->vec[i] | 1 << j) == 0)
					bv->free = i * sizeof(int) + j;
	}

	/* The 'index'th bit will be in the 'index / sizeof(int)'th int,
	 * and at the 'index % sizeof(int)' th bit position. */
	bv->vec[nth_int] |= (1 << nth_bit);
	return ENONE;
}

int bit_vector_unset(bit_vector bv, int index)
{
	int nth_int;

	if (index < 0 || index >= bv->len)
		return EINVAL;

	nth_int = index / sizeof(int);
	bv->vec[i] &= ~(1 << (index % sizeof(int)));
	if (bv->free > index)
		/* index will be the new toppest free slot. */
		bv->free = index;

	return ENONE;
}

/* Return 0 if 0, return 1 if 1. */
int bit_vector_query(bit_vector bv, int index)
{
	int mask;

	if (index < 0 || index >= bv->len)
		return EINVAL;

	mask = 1 << (index % sizeof(int));
	return bv->vec[index / sizeof(int)] & mask;
}

int bit_vector_set_m(bit_vector bv, int from, int to)
{
	int i, j;

	if (from < 0 || to < 0 || from >= bv->len || to >= bv->len || from > to)
		return EINVAL;

	if (bv->free == from) {
		/* The next free one will be search from 'to'th slot. */
		for (i = to / sizeof(int); i < bv->len / sizeof(int); i++)
	}

	for (i = from; i < to; i++)
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

