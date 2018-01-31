/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** my_malloc.h
*/

#ifndef MY_MALLOC_H_
	#define MY_MALLOC_H_

	#include <stddef.h>

	#define align(x) (((((x) - 1) >> 2) << 2) + 4)
	#define BLOCK_SIZE sizeof(struct s_block)
	#define META_DATA_SIZE BLOCK_SIZE
	#define MINSIZE (BLOCK_SIZE + 4)

extern void *base_list_g;

typedef struct s_block *t_block;

struct s_block {
	t_block next;
	t_block prev;
	size_t size;
	int free;
	char data[1];
};

t_block find_block(t_block *last, size_t size);
void show_alloc_mem();
void my_putnbr(long long int nbr);
void my_putstr(char *str);
int print_address_in_hexa(unsigned long long int ptr);

/*
** This function will enter in your mom
*/ 
void cut_block(t_block b, size_t s);

/*
** This function will extend the heap by the size s
** If the list exist we add it to the chained list
*/
t_block extend_heap_usage(t_block list, size_t s);

void *my_malloc(size_t size);
void my_free(t_block ptr);

#endif
