/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Created by Benjamin
*/

#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	void *handle;
	void *(*my_malloc)(size_t);
	void *(*my_free)(void *ptr);
	char *error;
	char *errstr;
	void *ptr;

	handle = dlopen("./libmy_malloc.so", RTLD_LAZY);
	errstr = dlerror();
	if (errstr != NULL)
		printf ("A dynamic linking error occurred: (%s)\n", errstr);
	if (!handle){
		printf("cannot open lib\n");
		return (84);
	}
	dlerror();
	*(void **)(&my_malloc) = dlsym(handle, "my_malloc");
	*(void **)(&my_free) = dlsym(handle, "my_free");
	if ((error = dlerror()) != NULL){
		printf("Error\n");
		return (84);
	}
	ptr = my_malloc(12);
	my_free(ptr);
	dlclose(handle);
	printf("No errors appened, everything works perfectly\n");
	return (0);
}