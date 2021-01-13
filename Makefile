tree = srcs/tree
utils = srcs/utils
splits = srcs/utils/splits
comm = srcs/commands
env = srcs/commands/environment

SRCS	=	srcs/minishell.c \
			$(tree)/tree_build.c $(tree)/tree_get_arg.c $(tree)/tree_read.c \
			$(utils)/str_utils.c $(utils)/str_utils_op_sep_space.c $(utils)/env_utils.c $(utils)/env_utils2.c \
			$(utils)/print_return.c $(utils)/clear_objects.c  \
			$(utils)/ft_math.c \
			$(splits)/ft_split_quotes.c $(splits)/split_minishell_dir.c $(splits)/split_minishell_args.c $(splits)/ft_split_dir.c \
			$(splits)/ft_split_args_quotes.c \
			$(comm)/ft_cd.c \
			$(comm)/ft_pwd.c \
			$(comm)/ft_echo.c \
			$(comm)/ft_env.c \
			$(comm)/ft_export.c \
			$(comm)/ft_unset.c \
			$(comm)/ft_exit.c \
			$(env)/ft_replace_env_value.c \
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
	$(CC) $(CFLAGS) $(OBJS) $(INC) -o $(NAME) 

libft:
	@$(MAKE) -C ./libft

$(OBJS): includes/minishell.h libft/includes/libft.h

$(OBJS_cd): includes/minishell.h libft/includes/libft.h

all:	$(NAME)

allc : all clean

clean:
	@$(RM) $(OBJS) 
	@$(MAKE) clean -C libft

fclean: 	clean
	@$(RM) libft/libft.a

re:		fclean all

.PHONY: all clean fclean re libft


# OBJECTS = objects/


# # OBJS = $(SRCS:.c=.o)
# # OBJS	:= $($(SRCS)%.c=$(OBJECTS)%.o)
# OBJS		:= $(SRCS:%.c=%.o)
# NAME = minishell
# CC = gcc
# RM = rm -f
# CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
# INC =	-I./includes
# LIB =  -L./libft -lft

# %.o: %.c includes/minishell.h
# 	$(CC) $(CFLAGS) $(INC) -c $< -o $(addprefix $(OBJECTS),$(notdir $@))

# # .c.o: $(OBJS)
# # 	$(CC) $(CFLAGS) -c $< -o $(addprefix objects/,$(notdir $@))

# $(NAME):	libft $(addprefix $(OBJECTS),$(notdir $(OBJS)))
# 	$(CC) $(CFLAGS)  $(addprefix $(OBJECTS),$(notdir $(OBJS))) $(LIB) -o $(NAME)

# libft:
# 	@$(MAKE) -C ./libft


# # $(OBJS):  includes/minishell.h libft/includes/libft.h 

# SILENT:
# all:	 $(NAME)

# allc : all clean

# clean:
# 	@$(RM) $(OBJS)
# 	@$(MAKE) clean -C libft

# fclean: 	clean
# 	@$(RM) $(NAME) env_file
# 	@$(RM) libft/libft.a

# re:		fclean all

# .PHONY: all clean fclean re libft
