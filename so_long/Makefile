# O nome do seu programa executável
NAME = so_long

# Compilador e flags de compilação.
# -Iincludes diz para procurar headers na pasta 'includes'.
# -I/usr/local/include diz para procurar o mlx.h do sistema.
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes -I/usr/local/include

# --- Arquivos do seu Projeto ---
# Adicione TODOS os seus arquivos .c aqui.
SRCS_DIR = src
SRCS = 	main.c \
		map_reader.c \
		map_validation.c \
		path_validation.c \
		graphics.c \
		hooks.c \
		game_logic.c \
		cleanup.c

# Adiciona o prefixo do diretório (src/) a cada arquivo.
SRCS_FULL = $(addprefix $(SRCS_DIR)/, $(SRCS))

# --- Arquivos Objeto ---
# Diretório para guardar os arquivos .o
OBJ_DIR = obj
# Gera os nomes dos arquivos .o dentro do diretório obj/
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# --- Bibliotecas ---
# Libft
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# MiniLibX (do sistema da 42)
MLX_LIBS = -L/usr/local/lib -lmlx -lXext -lX11 -lm

# Todas as bibliotecas juntas para a linkagem final
LIBS = $(LIBFT) $(MLX_LIBS)

# --- Regras do Makefile ---

# Regra principal
all: $(NAME)

# Regra para linkar e criar o executável final
$(NAME): $(OBJS) $(LIBFT)
	@echo "Linking..."
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)
	@echo "so_long is ready!"

# Regra para compilar a Libft.
# O 'make -C' executa o Makefile que está dentro da pasta libft.
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Cria o diretório de objetos antes de compilar.
# O '@' no início da linha suprime o eco do comando.
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Regra genérica para compilar cada .c em seu respectivo .o
$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos objeto
clean:
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean

# Regra para limpar tudo
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

# Regra para recompilar tudo
re: fclean all

# Evita conflitos com nomes de arquivos
.PHONY: all clean fclean re