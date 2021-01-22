main = srcs/main
tree = srcs/tree
utils = srcs/utils
split = srcs/split
comm = srcs/commands
env = srcs/utils/environment
str = srcs/utils/str

SRCS	=	$(main)/ft_ctrl.c $(main)/minishell.c $(main)/redirection.c \
			$(tree)/node_exec.c $(tree)/exec_builtin_execve.c $(tree)/tree_build.c $(tree)/tree_read.c \
			$(utils)/print_return.c $(utils)/print_return_2.c $(utils)/clear_objects.c $(utils)/std_utils.c \
			$(str)/str_utils.c $(str)/str_utils_op_sep_space.c \
			$(env)/env_fill_lst_and_swap.c $(env)/env_print_and_addlast.c \
			$(env)/env_unset_utils.c $(env)/env_utils2.c \
			$(env)/env_replace_value.c $(env)/env_match_var.c $(env)/env_utils3.c \
			$(split)/split_args.c $(split)/split_args_utils.c $(split)/split_args_utils_lst.c $(split)/split_args_utils_skip.c \
			$(split)/split_dir.c $(split)/split_dir_utils.c \
			$(split)/split_exec_paths.c $(split)/split_utils.c \
			$(comm)/ft_cd.c $(comm)/ft_cd_utils.c \
			$(comm)/ft_pwd.c \
			$(comm)/ft_echo.c \
			$(comm)/ft_env.c \
			$(comm)/ft_export.c \
			$(comm)/ft_unset.c \
			$(comm)/ft_exit.c \

SRC_DIR	:= srcs/
OBJ_DIR	:= obj/

OBJS	= $(SRCS:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

NAME = minishell
CC = clang
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
INC =	-I./includes -L./libft -lft

$(NAME): libft $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 
	echo "$@ (exec) \033[32mcreated\033[0m"
	echo "--------------------------------------------"

$(OBJ_DIR):
	mkdir -p $(dir $@)

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
