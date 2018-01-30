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
void *base_list_g = NULL;

/*
** This function find the first block that is free and wide enough.
** length needed : (size + META_DATA_SIZE)
**
** about last :
** if no block was found, last is now set the the end of the list.
** else, last is set to the element just before the block found.
**
** @param t_block last
** @param size_t size
**
** @return t_block
*/
t_block find_block(t_block *last, size_t size)
{
	t_block tmp = base_list_g;
	while (tmp != NULL && (tmp->free == 0 && tmp->size >= size)) {
		*last = tmp;
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
	int minsize = BLOCK_SIZE + 8;
	if (b->size - s > minsize) {
		t_block free_space = b + s + BLOCK_SIZE;

		free_space->next = b->next;
		free_space->prev = b;
		b->next = free_space;
		free_space->size = b->size - BLOCK_SIZE - s;
		free_space->free = 1;
		b->size = s;
	}
}

void *malloc(size_t size)
{
	t_block alloc;
	t_block list = base_list_g;
	size = align8(size);

	if (list != NULL) {
		alloc = find_block(&list, size);
		if (alloc != NULL) {
			cut_block(alloc, size);
			alloc->free = 0;
		}
		else
			alloc = extend_heap_usage(list, size);
		show_alloc_mem();
		if (!alloc)
			return NULL;
	}
	else {
		alloc = extend_heap_usage(list, size);
		base_list_g = alloc;
	}
	show_alloc_mem();
	return alloc;
}

void free(void *ptr)
{
	(void)ptr;
	return;
}
