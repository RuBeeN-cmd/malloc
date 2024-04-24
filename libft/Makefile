_END="\033[0m"
_RED="\033[0;31m"
_GREEN="\033[0;32m"
_YELLOW="\033[0;33m"
_CYAN="\033[0;36m"

NAME = libft.a
SRC = ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_atoi.c \
		ft_itoa.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		print_str_fd.c \
		print_nbr_fd.c \
		print_addr_fd.c \
		print_unbr_fd.c \
		ft_printf_fd.c
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
CC = gcc
CFLAGS = -Wall -Werror -Wextra
INC = -Iincludes

SRC_DIR = srcs
OBJ_DIR = objs

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo $(_GREEN)Compiling $(OBJ)...$(END)
	@ar -rc $(NAME) $(OBJ)

$(OBJ_DIR):
	@mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo $(_CYAN)Compiling $<...$(END)
	@$(CC) -o $@ -c $< $(CFLAGS) $(INC)

clean:
	@echo $(_YELLOW)Cleaning $(OBJ)...$(END)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo $(_RED)Cleaning $(NAME)...$(END)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
