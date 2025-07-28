# Nome da biblioteca
NAME = libftprintf.a

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Arquivos fonte (.c)
SRCS = ft_printf.c \
       ft_print_char.c \
       ft_print_string.c \
       ft_print_pointer.c \
       ft_print_decimal.c \
       ft_print_integer.c \
       ft_print_unsigned.c \
       ft_print_hex.c \
       # Adicione aqui outros arquivos .c que você criar

# Arquivos objeto (.o)
OBJS = $(SRCS:.c=.o)

# Comando para criar a biblioteca estática
AR = ar rcs

# Regra principal, que compila a biblioteca
all: $(NAME)

# Regra para criar a biblioteca a partir dos arquivos objeto
$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

# Regra para compilar arquivos .c em .o
%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar os arquivos objeto
clean:
	rm -f $(OBJS)

# Regra para limpar a biblioteca e os arquivos objeto
fclean: clean
	rm -f $(NAME)

# Regra para reconstruir o projeto do zero
re: fclean all

.PHONY: all clean fclean re