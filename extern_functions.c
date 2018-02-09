/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** intern_functions.c
*/

#include <stddef.h>
#include <pthread.h>
#include "my_malloc.h"

static pthread_mutex_t mutex_g = PTHREAD_MUTEX_INITIALIZER;

void *malloc(size_t size)
{
	void *ptr = NULL;

	if (pthread_mutex_lock(&mutex_g) != 0)
		return (NULL);
	ptr = intern_malloc(size);
	if (pthread_mutex_unlock(&mutex_g) != 0)
		return (NULL);
	return (ptr);
}

void free(void *ptr)
{
	if (pthread_mutex_lock(&mutex_g) != 0)
		return;
	intern_free(ptr);
	if (pthread_mutex_unlock(&mutex_g) != 0)
		return;
}

void *realloc(void *ptr, size_t size)
{
	void *ptr2 = NULL;

	if (pthread_mutex_lock(&mutex_g) != 0)
		return (NULL);
	ptr2 = intern_realloc(ptr, size);
	if (pthread_mutex_unlock(&mutex_g) != 0)
		return (NULL);
	return (ptr2);
}

void *calloc(size_t nmemb, size_t size)
{
	void *ptr = NULL;

	if (pthread_mutex_lock(&mutex_g) != 0)
		return (NULL);
	ptr = intern_calloc(nmemb, size);
	if (pthread_mutex_unlock(&mutex_g) != 0)
		return (NULL);
	return (ptr);
}