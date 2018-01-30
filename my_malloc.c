/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** my_malloc.c
*/

#include <stdio.h>
#include <zconf.h>
#include <errno.h>
#include "my_malloc.h"


/*
** This global variable point to the first block of the RAM of the
** program.
*/
void *base_list = NULL;

/*
** This function find the first block that is free and wide enough.
** (size + META_DATA_SIZE).
**
** @param t_block list
** @param size_t size
**
** @return t_block
*/
t_block find_block(size_t size)
{
	t_block tmp = base_list;
	while (tmp != NULL &&
	(tmp->free == 0 && tmp->size >= size)) {
		tmp = tmp->next;
	}
	return tmp;
}

/*
** The purpose of this function is to extend the Heap Used by the program
** if it is'nt wide enough for the memory allocation of the program.
**
** @param t_block list
** @param size_t size
**
** @return t_block
*/
t_block extend_heap_usage(t_block list, size_t s)
{
	t_block block = sbrk(0);

	if(sbrk(BLOCK_SIZE + s) == (void*)-1){
		printf("%d\n", errno);
		return (NULL);
	}
	block->next = NULL;
	block->prev = list;
	block->size = s;
	block->free = 0;
	if (list)
		list->next = block;
	return (block);
}

void cut_block(t_block b, size_t s)
{
	t_block free_space = b + s + BLOCK_SIZE;

	free_space->next = b->next;
	free_space->prev = b;
	b->next = free_space;
	free_space->size = b->size - BLOCK_SIZE - s;
	free_space->free = 1;
	b->size = s;
}

void show_alloc_mem()
{
	t_block tmp = base_list;
	void *breakPoint = sbrk(0);

	if (!breakPoint)
		return;
	printf("break : %p\n", breakPoint);
	while (tmp) {
		if (tmp->free == 0) {
			printf("%p - %p : %lu bytes\n", (void *)tmp->data,
			       tmp->next, tmp->size);
		}
		tmp = tmp->next;
	}
}


void *my_malloc(size_t size)
{
	printf("Enter my malloc\n");
}
