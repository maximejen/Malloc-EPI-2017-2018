/*
** EPITECH PROJECT, 2018
** my_malloc
** File description:
** show_alloc_mem.c
*/

#include <unistd.h>
#include "my_malloc.h"

int print_address_in_hexa(unsigned long long int ptr)
{
	my_putnbr(ptr);
	return 1;
	unsigned long nbr2;
	char nbrc;
	int size = 0;

	if ((ptr / 16) != 0)
		size = print_address_in_hexa(ptr / 16);
	nbr2 = ptr % 16;
	if (nbr2 >= 10 && nbr2 <= 15)
		nbrc = (char)(nbr2 + 55);
	else
		nbrc = (char)(nbr2 + '0');
	write(1, &nbrc, 1);
	return (size + 1);
}

void my_putnbr(long long int nbr)
{
	char tmp;

	if (nbr < 0) {
		nbr *= -1;
		write(1, "-", 1);
	}
	if (nbr / 10 != 0)
		my_putnbr(nbr / 10);
	tmp = (char)((nbr % 10) + '0');
	write(1, &tmp, 1);
}

void my_putstr(char *str)
{
	for (int i = 0 ; str[i] ; i++)
		write(1, &str[i], 1);
}

void show_alloc_mem()
{
	t_block tmp = base_list_g;
	void *breakPoint = sbrk(0);

	if (!breakPoint)
		return;
	my_putstr("break : ");
	write(1, "0x", 2);
	print_address_in_hexa((unsigned long long int)breakPoint);
	my_putstr("\n");
	while (tmp) {
		if (tmp->free == 0) {
			write(1, "0x", 2);
			print_address_in_hexa((size_t)tmp + BLOCK_SIZE);
			my_putstr(" - ");
			write(1, "0x", 2);
			print_address_in_hexa((size_t)tmp + BLOCK_SIZE + tmp->size);
			my_putstr(" : ");
			my_putnbr((long long int)tmp->size);
			my_putstr(" bytes\n");
		}
		else {
			write(1, "0x", 2);
			print_address_in_hexa((size_t)tmp + BLOCK_SIZE);
			my_putstr(" - ");
			write(1, "0x", 2);
			print_address_in_hexa((size_t)tmp + BLOCK_SIZE + tmp->size);
			my_putstr(" : ");
			my_putnbr((long long int)tmp->size);
			my_putstr(" freed bytes\n");
		}
		tmp = tmp->next;
	}
}
