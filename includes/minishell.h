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
** tree_struct.c
*/
int		create_main_tree(t_shell *shell, char *input);
int		read_input(t_shell *shell, t_tree **t_current, char **input);

/*
** clear_objects.c
*/
void	*malloc_lst(t_shell *shell, int size);
int		free_all_ptr(t_shell *shell);

/*
* Commands
*/
int		ft_cd(char **tab, t_tree *tree, t_shell *shell);

/*
* Utils
*/
int		ft_strrfind(const char *s, int c);
char	*ft_remove_eol(char *str);
int		is_operand(char *str);
int		is_separator(char c);
int		skip_spaces(char **str);
void	str_to_separator(char **str);

/*
** print_functions.c // A SUPPRIMER
*/
void	ft_print_tree(t_tree *node, int nb); // a supprimer


#endif