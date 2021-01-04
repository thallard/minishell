SRCS	=	srcs/test_minishell.c \
			srcs/str_utils.c \
			srcs/tree_struct.c \
			srcs/clear_objects.c \
			srcs/print_functions.c \
			srcs/commands/ft_cd.c \
			#srcs/commands/ft_pwd.c \
			#srcs/commands/ft_echo.c \
			#srcs/commands/ft_env.c

OBJS = $(SRCS:.c=.o)


NAME = minishell
CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
INC =	-I./includes -L./libft -lft

.c.o:
	$(CC) -c $< -o $@

$(NAME):	libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)


libft:
	@$(MAKE) -C ./libft

$(OBJS): includes/minishell.h libft/includes/libft.h

$(OBJS_cd): includes/minishell.h libft/includes/libft.h

all: 		$(NAME) cd pwd echo env

clean:
	$(RM) $(OBJS) 
	@$(MAKE) clean -C libft

fclean: 	clean
	$(RM) $(NAME)
	$(RM) libft/libft.a

re:		fclean all

.PHONY: all clean fclean re libft
