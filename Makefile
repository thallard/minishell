main = srcs/main
tree = srcs/tree
utils = srcs/utils
comm = srcs/commands

SRCS	=	$(main)/minishell.c \
			$(tree)/tree_build.c $(tree)/tree_get_arg.c $(tree)/tree_read.c \
			$(utils)/str_utils.c $(utils)/str_utils_op_sep_space.c $(utils)/env_utils.c $(utils)/env_utils2.c \
			$(utils)/print_return.c $(utils)/split_minishell.c $(utils)/clear_objects.c \
			$(comm)/ft_cd.c \
			$(comm)/ft_pwd.c \
			$(comm)/ft_echo.c \
			$(comm)/ft_env.c \
			$(comm)/ft_export.c \
			$(comm)/ft_unset.c \
			srcs/print_functions.c \

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
