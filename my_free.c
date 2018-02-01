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

static void end_of_the_heap(t_block ptr)
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

void free(void *ptr)
{
	my_putstr("Enter the free function\n");
	my_putstr("=== MEM AT BEGIN FREE ===\n");
	show_alloc_mem();
	my_putstr("=== MEM AT BEGIN FREE ===\n");
	t_block tmp;

	my_putstr("asked ptr : ");
	print_address_in_hexa((unsigned long long int)ptr);
	my_putstr("\n");
	if (ptr == NULL || !valid_ptr(ptr))
		return;
	my_putstr("ptr is valid\n");
	tmp = get_block(ptr);
	my_putstr("header found : ");
	print_address_in_hexa((unsigned long long int)tmp);
	my_putstr("\n");
	print_address_in_hexa((unsigned long long int)tmp->prev);
	my_putstr("we have the block now\n");
	tmp->free = 1;
	my_putstr("tmp->free is now set to 1\n");
	if (tmp->prev && tmp->prev->free) {
		my_putstr("try to merge prev block\n");
		tmp = merge_block(tmp->prev);
	}
	my_putstr("prev if passed\n");
	if (tmp->next) {
		my_putstr("try to merge next block\n");
		tmp = merge_block(tmp);
	}
	else {
		my_putstr("end of Heap\n");
		end_of_the_heap(tmp);
	}
	my_putstr("=== MEM AT END FREE ===\n");
	show_alloc_mem();
	my_putstr("=== MEM AT END FREE ===\n");
}