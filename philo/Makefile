SRCS  =  main.c utils.c parsing.c init.c monitor.c routine.c clear.c routine_utils.c more_utils.c

OBJS  =  ${SRCS:.c=.o}

CC    =  cc

CFLAGS  =  -Wall -Werror -Wextra -pthread

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

sanitize: CFLAGS += -fsanitize=undefined,thread,unsigned-integer-overflow,implicit-conversion,local-bounds,implicit-integer-arithmetic-value-change,implicit-conversion,integer -g3 -O3 
sanitize: re

.PHONY: all clean fclean re sanitize