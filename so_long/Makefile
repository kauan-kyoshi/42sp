NAME = so_long
CC = cc
CFLAGS = -Wall -Wextra -Werror
# --- Configuração da MiniLibX (AJUSTE PARA O SEU SISTEMA) ---
# Exemplo para Linux
MLX_PATH = ./minilibx # Supondo que a pasta da minilibx está aqui
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# Exemplo para macOS
# MLX_PATH = /path/to/your/minilibx
# MLX_FLAGS = -L$(MLX_PATH) -lmlx -framework OpenGL -framework AppKit

# --- Libft ---
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# --- Arquivos Fonte ---
SRCS_DIR = src/
SRCS = main.c \
       map_reader.c \
       map_validation.c \
       path_validation.c \
       graphics.c \
       hooks.c \
       game_logic.c \
       cleanup.c \

# Incluir GNL se não estiver na libft
SRCS += $(LIBFT_PATH)/get_next_line.c $(LIBFT_PATH)/get_next_line_utils.c

OBJS_DIR = obj/
OBJS = $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))

# Regras
all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

# Regra especial para GNL se estiver fora do SRCS_DIR
$(OBJS_DIR)get_next_line.o: $(LIBFT_PATH)/get_next_line.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJS_DIR)get_next_line_utils.o: $(LIBFT_PATH)/get_next_line_utils.c
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re