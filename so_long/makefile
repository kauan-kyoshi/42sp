# Nome do programa executável
NAME = so_long

# Compilador a ser usado
CC = cc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror

# Arquivos fonte (.c)
SRCS = main.c

# Arquivos objeto (.o), derivados dos arquivos .c
OBJS = $(SRCS:.c=.o)

# --- CONFIGURAÇÃO DA MINILIBX ---
# Caminho para o diretório da sua MiniLibX local
# Altere "./minilibx" se sua pasta tiver outro nome (ex: ./minilibx_linux)
MLX_DIR = ./minilibx 

# Flags do linker para a MiniLibX local
# -L aponta para o diretório da biblioteca
# -I aponta para o diretório dos headers (.h)
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm -lz

# Adiciona o caminho dos headers da MLX às flags de compilação
CFLAGS += -I$(MLX_DIR)

# Comando para remover arquivos gerados
RM = rm -f

# --- REGRAS ---

all: $(NAME)

$(NAME): $(OBJS)
# Compila a biblioteca MiniLibX (necessário em alguns sistemas)
	make -C $(MLX_DIR)
# Linka o seu programa com a biblioteca
	$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
# Limpa os objetos da MiniLibX também
	make clean -C $(MLX_DIR)
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re