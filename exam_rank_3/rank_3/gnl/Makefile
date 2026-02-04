# Variáveis de compilação
NAME    = gnl
CC      = cc
CFLAGS  = -Wall -Wextra -Werror -D BUFFER_SIZE=42
RM      = rm -f

# Arquivos
SRCS    = gnl.c main.c
OBJS    = $(SRCS:.c=.o)
INCL    = gnl.h

# Regra principal
all: $(NAME)

# Linkagem do executável
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# Compilação dos objetos
%.o: %.c $(INCL)
	$(CC) $(CFLAGS) -c $< -o $@

# Limpeza de arquivos temporários
clean:
	$(RM) $(OBJS)

# Limpeza completa (objetos + executável)
fclean: clean
	$(RM) $(NAME)

# Recompilação total
re: fclean all

# Evita conflitos com arquivos de mesmo nome
.PHONY: all clean fclean re
