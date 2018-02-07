##
## EPITECH PROJECT, 2018
## my_malloc
## File description:
## my_malloc.c
##

CC 			= 		gcc
RM 			= 		rm -f
TARGET_LIB 	= 		my_malloc.so

SRCS		= 		./extern_functions.c 	\
	  				./main_test.c 			\
	  				./my_free.c 			\
	  				./my_malloc.c 			\
	  				./my_realloc.c 			\
	  				./show_alloc_mem.c

OBJS 		= 		$(SRCS:.c=.o)

CFLAGS 		= 		-I./include/
CFLAGS 		+= 		-W -Wall -Wextra -fPIC
LDFLAGS      = 		-shared

all: $(TARGET_LIB)

$(TARGET_LIB): $(OBJS)
	 $(CC) $(OBJS) -o $(TARGET_LIB) $(LDFLAGS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
