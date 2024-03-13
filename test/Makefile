_END=\033[0m
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_CYAN=\033[0;36m

NAME = ./a.out

SRC = main.c
SRCS = $(addprefix $(SRC_DIR)/, $(SRC))

CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -I../includes -I../libft/includes

MALLOC_LIB = ./libft_malloc.so
LIBFT = ../libft/libft.a

LIB = $(LIBFT) $(MALLOC_LIB)

SRC_DIR = srcs

all: $(NAME)

$(NAME): $(LIB)
	@printf "$(_GREEN)Compiling $(SRCS)...$(_END)\n"
	@$(CC) $(CFLAGS) $(SRCS) $(LIB) $(INC) -o $@

real: $(LIBFT)
	@printf "$(_GREEN)Compiling $(SRCS)...$(_END)\n"
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(INC) -o real
	@./real

%.a:
	@make -C $(dir $@)

./libft_malloc.so:
	@make -C ..
	@cp ../libft_malloc.so .

clean:
	@printf "$(_YELLOW)Cleaning $(LIB)...$(_END)\n"
	@make -C $(dir $(LIB)) fclean
	@rm -f real

fclean: clean
	@printf "$(_RED)Cleaning $(NAME)...$(_END)\n"
	@rm -f $(NAME) 

re: fclean all

run:
	@./$(NAME)

runv:
	@valgrind --soname-synonyms=somalloc=libft_malloc.so ./$(NAME)

.PHONY: all clean fclean re run real