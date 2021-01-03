#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <errno.h>

# include "../libft/includes/libft.h"
# include "../libft/includes/get_next_line.h"
# include "../libft/printf/includes/printf.h"

# define SUCCESS 0
# define FAILURE -1

typedef struct	s_tree
{
	struct s_tree	*left;
	struct s_tree	*right;
	void			*item;
}				t_tree;

int	ft_strrfind(const char *s, int c);

#endif