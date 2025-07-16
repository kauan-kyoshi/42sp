# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kakubo-l <kakubo-l@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/16 16:27:13 by kakubo-l          #+#    #+#              #
#    Updated: 2025/07/16 16:53:36 by kakubo-l         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SRCS	= srcs/*.c
OBJS = ${SRCS:.c=.o}
LIBC = ar rcs
INCLUDES	= -I includes
CC		= cc
CFLAGS	= -Wall -Wextra -Werror ${INCLUDES}
RM		= rm -f

all:		$(NAME)

${NAME}: ${OBJS}
	${LIBC} ${NAME} ${OBJS}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME} 

re:	fclean all

.PHONY:		all clean fclean re