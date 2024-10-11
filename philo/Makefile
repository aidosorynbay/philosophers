SRCS  =  main.c utils.c parsing.c

OBJS  =  ${SRCS:.c=.o}

CC    =  cc

CFLAGS  =  -Wall -Werror -Wextra -O3 -g3 -pthread

SANITIZE_FLAGS = -fsanitize=thread,undefined -g3 -fno-omit-frame-pointer -flto -O3
NAME  =  philo

all    :  ${NAME}

%.o    :  %.c
	${CC} ${CFLAGS} -c $< -o $@

${NAME}  :  ${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME}

clean  :
	rm -f ${OBJS}

fclean  :  clean
	rm -f ${NAME}

re    :  fclean ${NAME}

.PHONY: all clean fclean re sanitize