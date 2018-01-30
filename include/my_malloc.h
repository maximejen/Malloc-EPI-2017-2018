/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** my_malloc.h
*/

#ifndef PSU_2017_MALLOC_MY_MALLOC_H_
	#define PSU_2017_MALLOC_MY_MALLOC_H_

	#include <stddef.h>

#define align8(x) (((((x)-1)>>3)<<3)+8)

typedef struct s_block *t_block;

struct s_block {
	size_t size;
	t_block next;
	int free;
	char data[1];
};

/*
** the size of the struct.
*/
	#define META_DATA_SIZE 12;

#endif //PSU_2017_MALLOC_MY_MALLOC_H_
