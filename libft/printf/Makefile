

SRCS	=   src/printf.c \
			src/str_type_1.c src/str_type_2.c \
			src/printf_utils_1.c src/printf_utils_2.c src/printf_utils_len.c \
			src/ft_num.c

OBJS = ${SRCS:.c=.o}

NAME = libftprintf.a
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -I./includes


.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	${OBJS}
	ar rcs ${NAME} ${OBJS}

$(OBJS) : includes/printf.h

all : 		${NAME}

clean :
	${RM} ${OBJS}

fclean : 	clean
	${RM} ${NAME}

re :		fclean all

.PHONY: all clean fclean re libftprintf.a bonus
