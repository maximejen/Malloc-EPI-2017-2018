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
	size_t i = 0;

	for (; i * 8 < src->size && i * 8 < dest->size; i++)
		dest->data[i] = src->data[i];
}

void *realloc(void *ptr, size_t size)
{
	void *ret = NULL;
	if (!ptr)
		ret = malloc(size);
	else if (valid_ptr(ptr)) {
		t_block block = get_block(ptr);
		if (block->size >= align(size) &&
			(block->size - size) >= MINSIZE)
			cut_block(block, align(size));
		else {
			void *tmp = malloc(size);
			if (tmp) {
				t_block new = get_block(tmp);
				copy_block(block, new);
				free(block);
				ret = new;
			}
		}
	}
	return (ret);
}