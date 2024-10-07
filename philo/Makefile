SRCS	=	main.c utils.c init.c free.c logic.c logic_utils.c more_logic.c

OBJS	=	${SRCS:.c=.o}

CC		=	cc

CFLAGS	=	-Wall -Werror -Wextra -o3

NAME	=	philo

all		:	${NAME}

%.o		:	%.c
		${CC} ${CFLAGS} -c $< -o $@

${NAME}	:	${OBJS}
		${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean	:
		rm -f ${OBJS}

fclean	:	clean
		rm -f ${NAME}

re		:	fclean ${NAME}

.PHONY: all clean fclean re