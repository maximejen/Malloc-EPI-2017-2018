/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** my_free.c
*/

#include <zconf.h>
#include "my_malloc.h"

t_block merge_block(t_block ptr)
{
	if (ptr->next && ptr->next->free == 1) {
		ptr->size += BLOCK_SIZE + ptr->next->size;
		ptr->next = ptr->next->next;
		if (ptr->next)
			ptr->next->prev = ptr;
	}
	return (ptr);
}

int valid_ptr(void *ptr)
{
	int res = 0;

	if (base_list_g && (ptr > base_list_g && ptr < sbrk(0)))
		res = 1;
	return (res);
}

void end_of_the_heap(t_block ptr)
{
	if (!ptr->prev)
		base_list_g = NULL;
	sbrk((intptr_t)ptr);
}

t_block get_block(void *ptr)
{
	t_block tmp = ptr;

	tmp = (void *)tmp - BLOCK_SIZE;
	return (tmp);
}

void intern_free(void *ptr)
{
	t_block tmp;

	if (ptr == NULL || !valid_ptr(ptr))
		return;
	tmp = get_block(ptr);
	tmp->free = 1;
	if (tmp->prev && tmp->prev->free)
		tmp = merge_block(tmp->prev);
	if (tmp->next)
		tmp = merge_block(tmp);
	else
		end_of_the_heap(tmp);
}