/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Created by Benjamin
*/

#include <zconf.h>
#include "my_malloc.h"

static void copy_block(t_block src, t_block dest)
{
	int *sdata;
	int *ddata;
	size_t i = 0;

	sdata = (int *)get_block(src);
	ddata = (int *)get_block(dest);
	for (; i * 4 < src->size && i * 4 < dest->size ; i++)
		sdata[i] = ddata[i];
}

void *realloc(void *ptr, size_t size)
{
	void *ret = NULL;
	if (!ptr)
		ret = malloc(size);
	else if (valid_ptr(ptr)) {
		t_block b = get_block(ptr);
		if (b->size >= align(size) && (b->size - size) >= MINSIZE) {
			cut_block(b, align(size));
			ret = (void *)b + BLOCK_SIZE;
		} else {
			ret = malloc(size);
			if (ret) {
				t_block new = get_block(ret);
				copy_block(b, new);
				free(b);
			}
		}
	}
	my_putstr("=== MEM AT END REALLOC ===\n");
	show_alloc_mem();
	my_putstr("=== MEM AT END REALLOC ===\n");
	my_putstr("return this address by realloc : ");
	print_address_in_hexa(
	(unsigned long long int)(ret + BLOCK_SIZE));
	my_putstr("\n");
	return (ret);
}