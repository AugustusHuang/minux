/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2015 Huang Xuxing
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software")
 * to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

/*
 * memory.h
 * Memory module, allocation and free routines to manipulate heap memory.
 * Use double-linked list to manipulate memory. Idea from osdev.org,
 * by Goswin von Brederlow.
 */

#ifndef KERN_MEMORY_H
#define KERN_MEMORY_H

/* Single-linked list is not that efficient so I decide to use double-link. */
typedef struct memory_list *memory_list;
struct memory_list {
	memory_list prev;
	memory_list next;
};

/* Every memory block will contain a double-linked list of memory list. */
typedef struct memory_block *memory_block;
struct memory_block {
	struct memory_list list;
	int used;
	union {
		char data[0];
		struct memory_list free;
	};
};

#define ALIGN4(size) (size + 3) & (~3)
#define HEADER_SIZE sizeof(struct memory_list) + sizeof(int)

/* Since we are in 32-bit content, there's no possibility to reach anything
 * larger than 2^32. */
extern memory_block free_block[32];
extern size_t memory_free;
extern size_t memory_used;
extern size_t memory_meta;
extern memory_block first;
extern memory_block last;

extern int __memory_start__;
extern int __memory_end__;

/* Insert AFTER after BEFORE. */
static inline void memory_insert_after(memory_list before, memory_list after)
{
	/* Crazy name... Change them if possible. */
	memory_list after_before = before->next;
	memory_list before_after = after->prev;

	before->next = after;
	after->prev = before;
	before_after->next = after_before;
	after_before->prev = before_after;
}

/* Insert BEFORE before AFTER. */
static inline void memory_insert_before(memory_list after, memory_list before)
{
	memory_list before_after = after->prev;
	memory_list before_before = before->prev;

	before_after->next = before;
	before->prev = before->after;
	before_before->next = after;
	after->prev = before_before;
}

static inline void memory_remove(memory_list slot)
{
	slot->prev->next = slot->next;
	slot->next->prev = slot->prev;

	slot->next = slot;
	slot->prev = slot;
}

static inline void memory_push(memory_list *listp, memory_list slot)
{
	if (listp == NULL)
		listp = slot;
	memory_insert_before(listp, slot);
}

static inline memory_list memory_pop(memory_list *listp)
{
	memory_list list1 = listp;
	memory_list list2 = list1->next;

	if (list1 = list2)
		/* a list of one and only */
		listp = NULL;
	else {
		memory_remove(list1);
		listp = list2;
	}
	return list1;
}

/* Memory module functions. */
extern void *memory_alloc(size_t size);
extern void memory_free(void *ptr);
extern void memory_init();

#endif
