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

	while (tmp != NULL) {
		if (tmp->free == 1 && tmp->size >= size)
			return (tmp);
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

	my_putstr("=== extend the heap usage ===\n");
	if(sbrk(BLOCK_SIZE + s) == (void*)-1)
		return (NULL);

	my_putstr("apparently, you just allocated ");
	my_putnbr(BLOCK_SIZE + s);
	my_putstr(" bytes.\nat : ");
	print_address_in_hexa((unsigned long long int)block);
	my_putstr("\n");

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
	my_putstr("Cuting the block found if possible\n");
	t_block free_space = (t_block)(b->data + s);
	free_space->next = b->next;
	free_space->prev = b;
	b->next = free_space;
	my_putstr("when cut, s is : ");
	my_putnbr((long long int)s);
	my_putstr("\n");
	my_putstr("when cut, size of b is : ");
	my_putnbr((long long int)b->size);
	my_putstr("\n");
	free_space->size = b->size - BLOCK_SIZE - s;
	my_putstr("when cut, size of free_space is : ");
	my_putnbr((long long int)free_space->size);
	my_putstr("\n");
	free_space->free = 1;
	b->size = s;
}

void *malloc(size_t size)
{
	t_block alloc;
	t_block list = base_list_g;
	size = align8(size);
	my_putstr("======== Entering My malloc ========\n");

	if (list != NULL) {
		my_putstr("base is defined\n");
		my_putstr("size of base : ");
		my_putnbr((long long int)list->size);
		my_putstr(" bytes.\naddress of base is : ");
		print_address_in_hexa((unsigned long long int)list);
		my_putstr("\n");
		alloc = find_block(&list, size);
		if (alloc != NULL) {
			my_putstr("Found a block wide enough\n");
			if (alloc->size - size >= BLOCK_SIZE + 8)
				cut_block(alloc, size);
			alloc->free = 0;
		}
		else {
			my_putstr("Did not found a block wide enough\n");
			my_putstr("=========== address of list element : ");
			print_address_in_hexa((unsigned long long int)list);
			my_putstr("\n");
			alloc = extend_heap_usage(list, size);
			if (!alloc)
				return (NULL);
		}
	}
	else {
		my_putstr("base is not defined, define it\n");
		alloc = extend_heap_usage(list, size);
		base_list_g = alloc;
	}
	show_alloc_mem();
	return (alloc);
}

void free(void *ptr)
{
	(void)ptr;
	return;
}
