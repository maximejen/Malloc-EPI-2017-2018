/*
** EPITECH PROJECT, 2018
** PSU_2017_malloc
** File description:
** my_malloc.h
*/

#ifndef MY_MALLOC_H_
	#define MY_MALLOC_H_

	#include <stddef.h>
	#include <pthread.h>

	#define align(x) (((((x) - 1) >> 4) << 4) + 16)
	#define alignPageSize(x) (((((x) - 1) >> 12) << 12) + 4096)
	#define BLOCK_SIZE sizeof(struct s_block)
	#define MINSIZE (BLOCK_SIZE + 16)

extern void *base_list_g;

typedef struct s_block *t_block;

struct s_block {
	t_block next;
	t_block prev;
	size_t size;
	int free;
};

t_block find_block(t_block *last, size_t size);
void show_alloc_mem(void);
void my_putnbr(long long int nbr);
void my_putstr(char *str);
int print_address_in_hexa(unsigned long long int ptr);
int valid_ptr(void *ptr);
t_block get_block(void *ptr);
t_block merge_block(t_block ptr);
void end_of_the_heap(t_block ptr);
void valid_ptr_case(void **ret, void *ptr, size_t size);

/*
** This function will enter in your mom
*/ 
void cut_block(t_block b, size_t s);

/*
** This function will extend the heap by the size s
** If the list exist we add it to the chained list
*/
t_block extend_heap_usage(t_block list, size_t s);

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);

void *intern_malloc(size_t size);
void intern_free(void *ptr);
void *intern_realloc(void *ptr, size_t size);
void *intern_calloc(size_t nmemb, size_t size);

#endif
