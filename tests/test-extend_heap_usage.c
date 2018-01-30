/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** Created by Benjamin
*/

#include <criterion/criterion.h>
#include "my_malloc.h"

Test(extend_heap_usage, TestPointer)
{

	t_block block_test = NULL;

	block_test = extend_heap_usage(NULL, 1);
	cr_expect_neq(block_test, NULL, "Extend_heap doesn't return\n");
}