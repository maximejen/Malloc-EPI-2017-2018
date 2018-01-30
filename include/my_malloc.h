/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** my_malloc.h
*/

#ifndef PSU_2017_MALLOC_MY_MALLOC_H_
	#define PSU_2017_MALLOC_MY_MALLOC_H_

	#include <stddef.h>

#define align8(x) (((((x) - 1) >> 3) << 3) + 8)

typedef struct s_block *t_block;

struct s_block {
	size_t size;
	t_block next;
	t_block previous;
	int free;
	char data[1];
};

t_block find_block(size_t size);
void show_alloc_mem();

/*
** This global variable point to the first block of the RAM of the
** program. Test
*/
void *base = NULL;

	/*
	** the size of the struct.
	*/
	#define META_DATA_SIZE 12;

void *my_malloc(size_t size);

#endif //PSU_2017_MALLOC_MY_MALLOC_H_
