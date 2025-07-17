# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 16:27:13 by kakubo-l          #+#    #+#              #
#    Updated: 2025/07/17 13:53:49 by kakubo-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= *.c
OBJS = ${SRCS:.c=.o}
LIBC = ar rcs
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f

all:		$(NAME)

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

${OBJS}: 
	${CC} ${CFLAGS} -I . -c ${SRCS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} 

re:	fclean all

.PHONY:		all clean fclean re