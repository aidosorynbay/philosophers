SRCS  =  main.c utils.c init.c free.c logic.c logic_utils.c more_logic.c

OBJS  =  ${SRCS:.c=.o}

CC    =  cc

CFLAGS  =  -Wall -Werror -Wextra -g3 -pthread

SANITIZE_FLAGS = -fsanitize=thread,undefined -g3 -fno-omit-frame-pointer -flto
NAME  =  philo

all    :  ${NAME}

sanitize: export TSAN_OPTIONS="history_size=7 force_seq_cst_atomics=1"
sanitize: CC = clang
sanitize: CFLAGS += ${SANITIZE_FLAGS}
sanitize: clean ${NAME}

asan: CC = clang
asan: CFLAGS += -fsanitize=address,undefined,unsigned-integer-overflow,implicit-conversion,local-bounds,integer,implicit-integer-arithmetic-value-change
asan: CFLAGS += -fno-omit-frame-pointer -fno-common -flto -g3
asan: re

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