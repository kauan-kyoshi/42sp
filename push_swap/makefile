NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I/usr/local/include

SRCS_DIR = src
SRCS = 	main.c \
		parse.c \
		utils.c \
		stack_utils.c \
		operations.c \
		sort.c

SRCS_FULL = $(addprefix $(SRCS_DIR)/, $(SRCS))


OBJ_DIR = obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "Code by: Kyoshi Lima ^-^ "

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re


