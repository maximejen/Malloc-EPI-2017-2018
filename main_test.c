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

	handle = dlopen("/home/benjamin/Dropbox/PSU_2017_malloc/cmake-build-debug/libmy_malloc.so", RTLD_LAZY);
	if (!handle){
		printf("lol\n");
		return (84);
	}
	dlerror();
	*(void **)(&my_malloc) = dlsym(handle, "my_malloc");
	if ((error = dlerror()) != NULL){
		printf("Non\n");
		return (84);
	}
	dlclose(handle);
	return (0);
}