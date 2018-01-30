/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** my_malloc.h
*/

#ifndef MY_MALLOC_H_
	#define MY_MALLOC_H_

	#include <stddef.h>

	#define align8(x) (((((x) - 1) >> 3) << 3) + 8)
	#define BLOCK_SIZE sizeof(struct s_block)
	#define METADATA_SIZE (BLOCK_SIZE - 1)

typedef struct s_block *t_block;

struct s_block {
	size_t size;
	t_block next;
	t_block prev;
	int free;
	char data[1];
};

t_block find_block(size_t size);
void show_alloc_mem();

/*
** This function will enter in your mom
**
*/

void cut_block(t_block b, size_t s);

/*
** This function will extend the heap by the size s
** If the list exist we add it to the chained list
*/
t_block extend_heap_usage(t_block list, size_t s);

void *my_malloc(size_t size);

#endif
