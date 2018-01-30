/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** my_malloc.c
*/

#include "my_malloc.h"

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
	t_block tmp = base;
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
	(void)s;
	(void)list;
}

void split_block(t_block b, size_t s)
{

}
