#ifndef FS_BIT_H
#define FS_BIT_H

typedef struct bit_vector *bit_vector;
struct bit_vector {
	int len; /* total bits in the bit vector */
	int free; /* first free bit in the bit vector, -1 means it's full */
	int *vec;
};

extern int bit_vector_init(int len);
/* One bit version of bit vector manipulation. */
extern int bit_vector_set(bit_vector bv, int index);
extern int bit_vector_unset(bit_vector bv, int index);
extern int bit_vector_query(bit_vector bv, int index);

/* Multiple bits version of bit vector manipulation. */
extern int bit_vector_set_m(bit_vector bv, int from, int to);
extern int bit_vector_unset_m(bit_vector bv, int from, int to);
extern int bit_vector_query_m(bit_vector bv, int from, int to);

/* Get the longest free partition of a bit vector. */
extern int bit_vector_get_longest(bit_vector bv);

#endif
