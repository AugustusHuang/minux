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
 * memory.c
 * Implementation of memory management module, use first-fit algorithm and
 * a memory table to handle memory requirement.
 */

#include "param.h"
#include "systm.h"
#include "process.h"
#include "memory.h"
#include "type.h"

/* for memmove */
#include <string.h>

#ifdef CONFIG_DEBUG
#include <stdio.h>
#endif

#define MEMORY_SIZE CONFIG_HEAP_SIZE

static void memory_block_init(memory_block block);
static int memory_block_index(size_t size);
static size_t memory_block_size(const memory_block block);
static void memory_remove_free(memory_block block);
static void memory_push_free(memory_block block);

static void memory_block_init(memory_block block)
{
	block->list.next = &block->list;
	block->list.prev = &block->list;
	block->used = 0;
	block->free.next = &block->free;
	block->free.prev = &block->free;
}

static int memory_block_index(size_t size)
{
	int i = -1;
	while (size > 0) {
		size >>= 1;
		i++;
	}
	return i;
}

static size_t memory_block_size(const memory_block block)
{
	return (char *)(block->list.next) - (char *)(&block->list) - HEADER_SIZE;
}

static void memory_remove_free(memory_block block)
{
	size_t len = memory_block_size(block);
	int index = memory_block_index(len);

	/* Remove this block from free list. */
	memory_free -= len - HEADER_SIZE;
}

static void memory_push_free(memory_block block)
{
	size_t len = memory_block_size(block);
	int index = memory_block_index(len);

	/* Push this block onto the free list. */
	memory_free += len - HEADER_SIZE;
}

void memory_init()
{
	char *memory_start = __memory_start__;
	char *memory_end = __memory_end__;
	memory_list head;
	size_t len;
	int index;

	free_block[32] = { NULL };
	/* Let the FIRST and LAST memory block assigned to the head and tail. */
	first = (memory_block)memory_start;
	second = first + 1;
	last = ((memory_block)memory_end) - 1;
	memory_block_init(first);
	memory_block_init(second);
	memory_block_init(last);
	
	/* Insert our SECOND memory block's memory list in between. */
	memory_insert_after(&first->list, &second->list);
	memory_insert_after(&second->list, &last->list);
	
	/* The first and last block is occupied so we get stable head and tail. */
	first->used = 1;
	last->used = 1;

	len = memory_block_size(second);
	index = memory_block_index(len);

	/* And then push the INDEXth slot onto the free list of SECOND. */
	if (&free_block[index] == NULL)
		head = NULL;
	head = &free_block[index]->free;
	memory_push(&head, &second->free);

	memory_free = len - HEADER_SIZE;
	memory_meta = sizeof(struct memory_block) * 2 + HEADER_SIZE;
}

void *memory_alloc(size_t size)
{
	size_t new_size;
	int n;
	memory_block block;
	
	if (size < sizeof(struct memory_list))
		new_size = sizeof(struct memory_list);
	else
		new_size = ALIGN4(size);

	n = memory_block_index(new_size - 1) + 1;

	if (n >= 32) {
#ifdef CONFIG_DEBUG
		printf("Size too big.\n");
#endif
		return NULL;
	}

	while (!free_block[n]) {
		n++;
		if (n >= 32) {
#ifdef CONFIG_DEBUG
			printf("Out of memory.\n");
#endif
			return NULL;
		}
	}

	/* We have enough memory! */
}

void memory_free(void *ptr)
{
	memory_block block, next, prev;

	/* Adjust the pointer to suit the block border. */
	block = (memory_block)((char *)ptr - HEADER_SIZE);

	/* Assign next and prev to the next and prev list of LIST. */

	memory_used -= memory_block_size(block);

	if (next->used == 0) {
		memory_remove_free(next);
		memory_remove(&next->list);
		memory_meta -= HEADER_SIZE;
		memory_free += HEADER_SIZE;
	}

	if (prev->used == 0) {
		memory_remove_free(prev);
		memory_remove(&block->list);
		memory_push_free(prev);
		memory_meta -= HEADER_SIZE;
		memory_free += HEADER_SIZE;
	} else {
		block->used = 0;

		memory_push_free(block);
	}
}
