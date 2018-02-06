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

	sdata = (int *)src;
	ddata = (int *)dest;
	for (; i * 4 < src->size && i * 4 < dest->size ; i++)
		sdata[i] = ddata[i];
}

void valid_ptr_case(void **ret, void *ptr, size_t size)
{
	t_block b = get_block(ptr);
	if (b->size >= align(size) && (b->size - size) >= MINSIZE) {
		cut_block(b, align(size));
		*ret = (void *)b + BLOCK_SIZE;
	} else {
		*ret = intern_malloc(size);
		if (*ret) {
			t_block new = get_block(*ret);
			copy_block(b, new);
			intern_free(b);
		}
	}
}

void *intern_realloc(void *ptr, size_t size)
{
	void *ret = NULL;
	if (!ptr)
		ret = intern_malloc(size);
	else if (valid_ptr(ptr)) {
		valid_ptr_case(&ret, ptr, size);
	}
	return (ret);
}