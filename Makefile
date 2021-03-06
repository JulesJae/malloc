ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME = libft_malloc_$(HOSTTYPE).so

CC = gcc $(FLAGS)

LINK = libft_malloc.so

LIBFT = ./libft

LIB = ./libft/libftprintf.a

INCLUDES = -I ./includes -I ./libft/includes

PATH_SRC = ./src/

FLAGS = -Wall -Wextra -Werror $(INCLUDES) -g -fPIC

SRC =	block.c \
		free.c \
		malloc.c \
		print.c \
		realloc.c \
		utils.c \

OBJ = $(addprefix $(PATH_SRC), $(SRC:.c=.o))

all: $(LIB) $(NAME)
$(LIB): 
	make -C $(LIBFT)

$(NAME): $(OBJ)
	@rm -f $(LINK)
	$(CC) -shared -o $(NAME) $(OBJ) $(LIB) -lpthread
	@ln -s $(NAME) $(LINK)

clean: 
	make -C $(LIBFT) clean
	rm -f $(OBJ)

fclean:
	make -C $(LIBFT) fclean
	rm -f $(OBJ)
	rm -f $(NAME)
	rm -f $(LINK)

re: fclean all

.PHONY: all clean re fclean



