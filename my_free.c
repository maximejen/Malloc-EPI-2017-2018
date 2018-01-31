/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** my_free.c
*/

#include <zconf.h>
#include "my_malloc.h"

static t_block merge_block(t_block ptr)
{
	(void)ptr;
	if (ptr->next && ptr->next->free) {
		ptr->size += BLOCK_SIZE + ptr->next->size;
		ptr->next = ptr->next->next;
		if (ptr->next)
			ptr->next->prev = ptr;
	}
	return (ptr);
}

static int valid_ptr(void *ptr)
{
	int res = 0;

	if (base_list_g && (ptr > base_list_g && ptr < sbrk(0)))
		res = 1;
	return (res);
}

static void endOfTheHeap(t_block ptr)
{
	if (ptr->prev)
		ptr->prev->next = NULL;
	else
		base_list_g = NULL;
	sbrk((intptr_t)ptr);
}

void my_free(t_block ptr)
{
	if (!valid_ptr(ptr))
		return;
	t_block tmp = (ptr -= BLOCK_SIZE);

	tmp->free = 1;
	if (tmp->prev && tmp->prev->free)
		tmp = merge_block(tmp->prev);
	if (tmp->next)
		tmp = merge_block(tmp->next);
	else
		endOfTheHeap(tmp);
}