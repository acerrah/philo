NAME = philo
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIB = ./lib/lib.a
SRCS =	./srcs/main.c \
		./srcs/error_and_data.c \
		./srcs/ring.c

all: ${MLX} ${NAME}

${NAME}: ${SRCS} ${LIB}
	@gcc -g ${MFLAGS} ${CFLAGS} ${SRCS} ${LIB} -o ${NAME}

${LIB}:
	@make re -C ./Libraries/lib

clean:
	@make clean -C ./Libraries/lib/libft

fclean: clean
	@rm -rf ${NAME}
	@make clean -C ./Libraries/minilibx
	@make clean -C ./Libraries/lib
	@rm -rf ${NAME}.dSYM

re: fclean all

.PHONY: clean re
