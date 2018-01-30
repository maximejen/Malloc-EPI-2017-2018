/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Created by Benjamin
*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include "my_malloc.h"

int main()
{
	void *handle;
	void *(*my_malloc)(size_t);
	char *error;

	handle = dlopen("./libmalloc_bootstrap.so", RTLD_LAZY);
	if (!handle)
		return (84);
	dlerror();
	(void *)(&my_malloc) = dlsym(handle, "my_malloc");
	if ((error = dlerror()) != NULL)
		return (84);
	dlclose(handle);
	return (0);
}