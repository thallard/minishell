#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/stat.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/printf/includes/printf.h"

# define SUCCESS 1
# define FAILURE -1
# define EOL 0

# define OP 1
# define SEP 2

# define NOT_ENOUGH_ARG 3
# define TOO_MANY_ARG 4

# define DOUBLE_SEP -2

typedef struct		s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	void			*item;
	int				fd;		// a gerer
}					t_tree;

typedef struct		s_env
{
	char			*name;
	void			*content;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	int				exit;
	t_env			*var_env;
	t_list			*ptrs;
	t_tree			*root;
	char			*input;
	int				last_node;
	char			*op;
	char			*sep;
}					t_shell;

/*
****************************************************
**						TREE					  **
****************************************************
*/

/*
** tree_build.c
*/
t_tree	*tree_create_node(t_shell *shell, void *item);
int		add_op_node(t_shell *shell, t_tree *t_current, char **input);
int		add_sep_node(t_shell *shell, t_tree **t_current, char **input);
int		read_input(t_shell *shell, t_tree **t_current, char **input);
int		create_main_tree(t_shell *shell, char *input);

/*
** tree_get_arg.c
*/
int		get_nb_operand_arg(char *op);
t_tree	*get_next_arg_echo(t_shell *shell,char **input, int nb_arg);
int		get_echo_arg(t_shell *shell, char **input, t_tree *op_node);
t_tree	*get_next_arg(t_shell *shell,char **input);
int		get_operand_arg(t_shell *shell, char **input, t_tree *op_node);

/*
** tree_read.c
*/
int	read_tree(t_shell *shell);



/*
****************************************************
**						UTILS					  **
****************************************************
*/

/*
** clear_objects.c
*/
void	*malloc_lst(t_shell *shell, int size);
int		free_all_ptr(t_shell *shell);

/*
* Commands
*/
int		ft_cd(t_shell *shell, t_tree *node);
int		ft_pwd(t_shell *shell);

/*
** str_utils.c
*/
int		ft_strrfind(const char *s, int c);
char	*ft_remove_eol(char *str);

/*
** str_utils_op_sep_space.c
*/
int		is_operand(char *str);
int		is_separator(char c);
int		skip_spaces(char **str);
void	str_to_separator(char **str);
char	*strdup_and_inc_input(t_shell *shell, char **input);


/*
****************************************************
**						DRAFT					  **
****************************************************
*/

/*
** print_functions.c // A SUPPRIMER
*/
void	ft_print_tree(t_tree *node, int nb); // a supprimer


#endif