SRCS	=	srcs/test_minishell.c \
			srcs/str_utils.c
SRCS_cd	=	srcs/ft_cd.c \
			srcs/str_utils.c
SRCS_pwd =  srcs/ft_pwd.c

OBJS = $(SRCS:.c=.o)
OBJS_cd = $(SRCS_cd:.c=.o)
OBJS_pwd = $(SRCS_pwd:.c=.o)

NAME = minishell
CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INC =	-I./includes -L./libft -lft

.c.o:
	$(CC) -c $< -o $@

$(NAME):	libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME)

cd:		libft $(OBJS_cd)
	$(CC) $(CFLAGS) $(OBJS_cd) $(INC) -o cd

pwd:		libft $(OBJS_pwd)
	$(CC) $(CFLAGS) $(OBJS_pwd) $(INC) -o pwd

libft:
	@$(MAKE) -C ./libft

$(OBJS): includes/minishell.h libft/includes/libft.h

$(OBJS_cd): includes/minishell.h libft/includes/libft.h

all: 		$(NAME) cd pwd

clean:
	$(RM) $(OBJS) $(OBJS_cd) $(OBJS_pwd)
	@$(MAKE) clean -C libft

fclean: 	clean
	$(RM) $(NAME)
	$(RM) cd
	$(RM) pwd
	$(RM) libft/libft.a

re:		fclean all

.PHONY: all clean fclean re libft
