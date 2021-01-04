SRCS	=	srcs/test_minishell.c \
			srcs/tree/tree_build.c srcs/tree/tree_get_arg.c srcs/tree/tree_read.c \
			srcs/clear_objects.c \
			srcs/print_functions.c \
			srcs/str_utils.c srcs/str_utils_op_sep_space.c

SRCS_cd	=	srcs/commands/ft_cd.c \
			srcs/str_utils.c

SRCS_pwd =  srcs/commands/ft_pwd.c

SRCS_echo = srcs/commands/ft_echo.c

OBJS = $(SRCS:.c=.o)
OBJS_cd = $(SRCS_cd:.c=.o)
OBJS_pwd = $(SRCS_pwd:.c=.o)
OBJS_echo = $(SRCS_echo:.c=.o)

NAME = minishell
CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
INC =	-I./includes -L./libft -lft

.c.o:
	$(CC) -c $< -o $@

$(NAME):	libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)

cd:		libft $(OBJS_cd)
	$(CC) $(CFLAGS) $(OBJS_cd) $(INC) -o cd

pwd:	libft $(OBJS_pwd)
	$(CC) $(CFLAGS) $(OBJS_pwd) $(INC) -o pwd

echo:	libft $(OBJS_echo)
	$(CC) $(CFLAGS) $(OBJS_echo) $(INC) -o echo

libft:
	@$(MAKE) -C ./libft

$(OBJS): includes/minishell.h libft/includes/libft.h

$(OBJS_cd): includes/minishell.h libft/includes/libft.h

all: 		$(NAME) cd pwd echo

clean:
	$(RM) $(OBJS) $(OBJS_cd) $(OBJS_pwd) $(OBJS_echo)
	@$(MAKE) clean -C libft

fclean: 	clean
	$(RM) $(NAME)
	$(RM) cd pwd echo
	$(RM) libft/libft.a

re:		fclean all

.PHONY: all clean fclean re libft
