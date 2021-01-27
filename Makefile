SRC_DIR	:= srcs/
OBJ_DIR	:= obj/

main = main
tree = tree
utils = utils
split = split
comm = commands
env = utils/environment
str = utils/str

OBJ_DIRS = $(addprefix $(OBJ_DIR), $(main) $(tree) $(utils) $(split) $(comm) $(env) $(str))

PRE_SRCS	=	$(main)/ft_ctrl $(main)/minishell $(main)/redirection \
				$(tree)/node_exec $(tree)/exec_builtin_execve $(tree)/tree_build $(tree)/tree_read \
				$(utils)/print_return $(utils)/print_return_2 $(utils)/clear_objects $(utils)/std_utils \
				$(str)/str_utils $(str)/str_utils_op_sep_space \
				$(env)/env_fill_lst_and_swap $(env)/env_print_and_addlast \
				$(env)/env_unset_utils $(env)/env_utils2 \
				$(env)/env_replace_value $(env)/env_match_var $(env)/env_utils3 \
				$(split)/split_args $(split)/split_args_utils $(split)/split_args_utils_lst $(split)/split_args_utils_skip \
				$(split)/split_dir $(split)/split_dir_utils \
				$(split)/split_exec_paths $(split)/split_utils \
				$(comm)/ft_cd $(comm)/ft_cd_utils \
				$(comm)/ft_pwd \
				$(comm)/ft_echo \
				$(comm)/ft_env \
				$(comm)/ft_export \
				$(comm)/ft_unset \
				$(comm)/ft_exit

SRCS = $(addsuffix .c, $(addprefix $(SRC_DIR), $(PRE_SRCS)))
OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))

LIBFTA = libft/libft.a

NAME = minishell
CC = clang
RM = rm -f
# CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
CFLAGS = -Wall -Wextra -Werror -g3
INC =	-I./includes -L./libft -lft

all:	libft $(NAME)

$(NAME): $(LIBFTA) $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 
	@echo "----- \033[32m $@ created\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS) : includes/minishell.h

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "$@ \033[32mcreated\033[0m"

$(LIBFTA):
	@$(MAKE) -C ./libft

libft:
	@$(MAKE) -C ./libft

clean:
	rm -rf $(OBJ_DIR)
	@$(MAKE) clean -C libft

fclean: 	clean
	@$(RM) libft/libft.a
	rm -f minishell

re:		fclean all

.PHONY: all clean fclean re libft
