
# --- Programa ---
NAME = so_long

# --- Compilador e Flags ---
CC = cc
CFLAGS = -Wall -Wextra -Werror

# --- Bibliotecas ---
# Libft
LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

# MiniLibX (AJUSTE PARA O SEU SISTEMA)
MLX_PATH = ./minilibx 
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lXext -lX11 -lm

# --- Arquivos ---
SRCS_DIR = src/
OBJS_DIR = obj/

SRCS_FILES = main.c \
             map_reader.c \
             map_validation.c \
             path_validation.c \
             graphics.c \
             hooks.c \
             game_logic.c \
             cleanup.c

SRCS = $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS = $(patsubst $(SRCS_DIR)%.c, $(OBJS_DIR)%.o, $(SRCS))

# --- Regras ---
all: $(NAME)

# Regra para linkar: agora depende de $(MLX_LIB) também
$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	@echo "Linking objects to create $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)
	@echo "$(NAME) created successfully!"

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

# Regra para compilar a libft
$(LIBFT):
	@echo "Compiling Libft..."
	@make -s -C $(LIBFT_PATH)

# Regra para compilar a MiniLibX
$(MLX_LIB):
	@echo "Compiling MiniLibX..."
	@make -s -C $(MLX_PATH)

clean:
	@echo "Cleaning Libft objects..."
	@make -s -C $(LIBFT_PATH) clean
	@echo "Cleaning MiniLibX objects..."
	@make -s -C $(MLX_PATH) clean
	@echo "Cleaning project objects..."
	@rm -rf $(OBJS_DIR)

fclean: clean
	@echo "Cleaning Libft library..."
	@make -s -C $(LIBFT_PATH) fclean
	@echo "Cleaning project executable..."
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re