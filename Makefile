main = srcs/main
tree = srcs/tree
utils = srcs/utils
splits = srcs/utils/splits
comm = srcs/commands
env = srcs/utils/environment
str = srcs/utils/str

SRCS	=	$(main)/ft_ctrl.c $(main)/minishell.c $(main)/redirection.c \
			$(tree)/node_exec.c $(tree)/exec_builtin_execve.c $(tree)/tree_build.c $(tree)/tree_read.c \
			$(utils)/print_return.c $(utils)/print_return_2.c $(utils)/clear_objects.c \
			$(str)/str_utils.c $(str)/str_utils_op_sep_space.c \
			$(env)/env_utils.c $(env)/env_utils2.c $(env)/env_replace_value.c $(env)/env_match_var.c $(env)/env_fill.c \
			$(splits)/ft_split_quotes.c $(splits)/split_minishell_dir.c $(splits)/split_exec_paths.c $(splits)/ft_split_dir.c \
			$(splits)/ft_split_args_quotes.c $(splits)/ft_split_args.c \
			$(comm)/ft_cd.c \
			$(comm)/ft_pwd.c \
			$(comm)/ft_echo.c \
			$(comm)/ft_env.c \
			$(comm)/ft_export.c \
			$(comm)/ft_unset.c \
			$(comm)/ft_exit.c \
			srcs/print_functions.c # a supprimer

SRC_DIR	:= srcs/
OBJ_DIR	:= obj/

OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

NAME = minishell
CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
INC =	-I./includes -L./libft -lft

$(NAME): libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 
	echo "$@ (exec) \033[32mcreated\033[0m"
	echo "--------------------------------------------"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c includes/minishell.h libft/includes/libft.h | $(OBJ_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	echo "$@ \033[32mcreated\033[0m"

libft:
	@$(MAKE) -C ./libft

$(OBJS): includes/minishell.h libft/includes/libft.h

all:	$(NAME)

allc : all clean

clean:
	@$(RM) $(OBJS) 
	@$(MAKE) clean -C libft

fclean: 	clean
	@$(RM) libft/libft.a

re:		fclean all

.PHONY: all clean fclean re libft
