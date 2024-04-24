_END=\033[0m
_RED=\033[0;31m
_GREEN=\033[0;32m
_YELLOW=\033[0;33m
_CYAN=\033[0;36m

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

LNAME = libft_malloc.so

SRC = malloc.c \
		show_alloc_mem.c \
		show_alloc_mem_hex.c \
		page.c \
		free.c \
		realloc.c \
		collector.c \
		logger.c

NAME = $(basename $(LNAME))_$(HOSTTYPE).so
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = gcc
CFLAGS = -Wall -Werror -Wextra -fPIC -pthread -g3
INC = -Iincludes -I$(dir $(LIB))/includes

LIBFT = libft/libft.a
LIB = $(LIBFT)
LIBFLAGS = -L$(dir $(LIBFT)) -l$(subst lib,,$(basename $(notdir $(LIBFT))))

SRC_DIR = srcs
OBJ_DIR = objs

all: $(LNAME)

$(LNAME): $(NAME)
	@ln -sf $(NAME) $(LNAME)

$(NAME): $(LIB) $(OBJ_DIR) $(OBJ)
	@printf "$(_GREEN)Compiling $(OBJ)...$(_END)\n"
	@$(CC) $(CFLAGS) -shared $(OBJ) $(LIBFLAGS) -o $@

$(LIB):
	@make -C $(dir $@)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@printf "$(_CYAN)Compiling $<...$(_END)\n"
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)

clean:
	@printf "$(_YELLOW)Cleaning $(OBJ)...$(_END)\n"
	@make -C $(dir $(LIB)) fclean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@printf "$(_RED)Cleaning $(NAME)...$(_END)\n"
	@rm -f $(NAME) $(LNAME)

re: fclean all

test: $(LNAME)
	@printf "$(_YELLOW)Testing $(LNAME)...$(_END)\n"
	@make -C test re
	@make -C test run

testv: $(LNAME)
	@printf "$(_YELLOW)Testing $(LNAME)...$(_END)\n"
	@make -C test
	@make -C test runv

.PHONY: all clean fclean re test