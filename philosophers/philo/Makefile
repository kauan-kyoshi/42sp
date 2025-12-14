# Minimal Makefile for philo (no libft dependency per subject)

NAME	= philo
CC		= cc
CFLAGS	= -Wall -Wextra -Werror -pthread
RM		= rm -f

# Liste explicitamente os fontes do philo (ajuste conforme criar os .c)
SRCS	= main.c args.c init.c time_utils.c routine.c monitor.c log.c cleanup.c
OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re