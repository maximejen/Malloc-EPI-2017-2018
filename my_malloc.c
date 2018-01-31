/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** my_malloc.c
*/

#include <stdio.h>
#include <zconf.h>
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
	while (tmp) {
		if (tmp->free && tmp->size >= size)
			return (tmp);
		*last = tmp;
		tmp = tmp->next;
	}
	return (tmp);
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

	if(sbrk(BLOCK_SIZE + s) == (void*)-1)
		return (NULL);
	block->size = s;
	block->next = NULL;
	block->prev = list;
	if (list)
		list->next = block;
	block->free = 0;
	return (block);
}

void cut_block(t_block b, size_t s)
{
	t_block free_space;

	free_space = (t_block)(b->data + s);
	free_space->next = b->next;
	free_space->prev = b;
	b->next = free_space;
	free_space->size = b->size - BLOCK_SIZE - s;
	free_space->free = 1;
	b->size = s;
}

void *malloc(size_t size)
{
	t_block alloc;
	t_block list = base_list_g;
	size = align(size);

	if (list != NULL) {
		alloc = find_block(&list, size);
		if (alloc != NULL) {
			my_putstr("a block was found\n");
			if (alloc->size - size >= MINSIZE)
				cut_block(alloc, size);
			alloc->free = 0;
		}
		else
			alloc = extend_heap_usage(list, size);
	}
	else {
		alloc = extend_heap_usage(list, size);
		base_list_g = alloc;
	}
	return (alloc->data);
}

//t_block merge_block(t_block ptr)
//{
//	(void)ptr;
//	if (ptr->next && ptr->next->free) {
//		ptr->size += BLOCK_SIZE + ptr->next->size;
//		ptr->next = ptr->next->next;
//		if (ptr->next)
//			ptr->next->prev = ptr;
//	}
//	return (ptr);
//}
//
//int valid_ptr(void *ptr)
//{
//	int res = 0;
//
//	if (base_list_g && (ptr > base_list_g && ptr < sbrk(0)))
//		res = 1;
//	return (res);
//}
//
//void endOfTheHeap(t_block ptr)
//{
//	if (ptr->prev)
//		ptr->prev->next = NULL;
//	else
//		base_list_g = NULL;
//	sbrk((intptr_t)ptr);
//}
//
//void free(t_block ptr)
//{
//	if (!valid_ptr(ptr))
//		return;
//	t_block tmp = (ptr -= BLOCK_SIZE);
//
//	tmp->free = 1;
//	if (tmp->prev && tmp->prev->free)
//		tmp = merge_block(tmp->prev);
//	if (tmp->next)
//		tmp = merge_block(tmp->next);
//	else
//		endOfTheHeap(tmp);
//}
