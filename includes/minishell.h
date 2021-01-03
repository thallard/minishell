#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>

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
}					t_shell;
/*
* Utils
*/
int		ft_strrfind(const char *s, int c);
char	*ft_remove_eol(char *str);


#endif