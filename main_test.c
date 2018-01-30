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
	char *errstr;

	handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
	if (errstr != NULL)
		printf ("A dynamic linking error occurred: (%s)\n", errstr);
	errstr = dlerror();
	if (!handle){
		printf("cannot open lib\n");
		return (84);
	}
	dlerror();
	*(void **)(&my_malloc) = dlsym(handle, "my_malloc");
	if ((error = dlerror()) != NULL){
		printf("Error\n");
		return (84);
	}
	dlclose(handle);
	return (0);
}