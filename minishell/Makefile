# **************************************************************************** #
# MAKEFILE MINIMAL PARA O PROJETO MINISHELL
# Targets: all, clean, fclean, re, NAME

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) -I include -L $(LIBFT_DIR) -o $(NAME) $(OBJS) -lft -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -I include -c $< -o $@

$(LIBFT_A):
	@echo "Assumindo que libft está pronta em $(LIBFT_DIR)"
	@$(MAKE) -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean || true

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean || true

re: fclean all

.PHONY: all clean fclean re
