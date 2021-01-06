SRCS	=	srcs/main/minishell.c \
			srcs/tree/tree_build.c srcs/tree/tree_get_arg.c srcs/tree/tree_read.c \
			srcs/clear_objects.c \
			srcs/print_functions.c \
			srcs/utils/str_utils.c srcs/utils/str_utils_op_sep_space.c srcs/utils/lst_utils.c \
			srcs/utils/print_return.c srcs/utils/split_minishell.c \
			srcs/commands/ft_cd.c \
			srcs/commands/ft_pwd.c \
			srcs/commands/ft_echo.c \
			srcs/commands/ft_env.c \
			srcs/commands/ft_export.c \
			srcs/commands/ft_unset.c

OBJS = $(SRCS:.c=.o)


NAME = minishell
CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
INC =	-I./includes -L./libft -lft

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	libft $(OBJS)
	$(CC)  $(CFLAGS) $(OBJS) $(INC) -o $(NAME)
	bash srcs/commands/sh/get_env.sh


libft:
	@$(MAKE) -C ./libft

$(OBJS): includes/minishell.h libft/includes/libft.h

$(OBJS_cd): includes/minishell.h libft/includes/libft.h

all:	$(NAME)

clean:
	$(RM) $(OBJS) 
	@$(MAKE) clean -C libft

fclean: 	clean
	$(RM) $(NAME) env_file
	$(RM) libft/libft.a

re:		fclean all

.PHONY: all clean fclean re libft
