
SRC_NAME = get_next_line.c\
		get_next_line_utils.c\


OBJ_NAME = $(SRC_NAME:.c=.o) 
CFLAG = -Wall -Wextra -Werror
NAME = gnl.a

.PHONY: all clean fclean re

all: ${NAME}
	 @echo > /dev/null

${NAME}: ${OBJ_NAME}
	@gcc -c ${CFLAG} ${SRC_NAME}
	@ar -rc $(NAME) $(OBJ_NAME)
	@ranlib ${NAME}

%.o: %.c
	@gcc ${CFLAG} -c $< -o ${<:%.c=%.o}

clean:
	@rm -rf ${OBJ_NAME}

fclean: clean
	@rm -f ${NAME}

re: fclean all