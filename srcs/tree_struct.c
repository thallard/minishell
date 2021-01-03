#include "../includes/minishell.h"

/*
**	Separateurs a gerer :
**		;
**		|
**		" " et ' '
**
**
**
*/

t_tree	*tree_create_node(t_shell *shell, void *item)
{
	t_tree	*node;

	if (!(node = malloc_lst(shell, sizeof(t_tree*))))
		return (NULL);
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int		is_operand(char *str)
{
	if(!ft_strncmp(str, "echo", 4))
		return (4);
	if (!ft_strncmp(str, "cd", 2))
		return (2);
	if (!ft_strncmp(str, "pwd", 3))
		return (3);
	if (!ft_strncmp(str, "export", 6))
		return (6);
	if (!ft_strncmp(str, "unset", 5))
		return (5);
	if (!ft_strncmp(str, "env", 3))
		return (3);
	if (!ft_strncmp(str, "exit", 4))
		return (4);
	return (0);
}

int		is_separator(char c)
{
	return (c == '|' ||
			c == ';');
}

char	*strdup_and_inc_input(t_shell *shell, char **input, int len)
{
	char *op;
	int i;

	if (!(op = malloc_lst(shell, len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		op[i++] = *((*input)++);
	op[i] = 0;
	return (op);
}

int		get_nb_operand_arg(char *op)
{
	if(!ft_strncmp(op, "echo", 4))
		return (2);
	if (!ft_strncmp(op, "cd", 2))
		return (1);
	if (!ft_strncmp(op, "pwd", 3))
		return (3);
	if (!ft_strncmp(op, "export", 6))
		return (6);
	if (!ft_strncmp(op, "unset", 5))
		return (5);
	if (!ft_strncmp(op, "env", 3))
		return (3);
	if (!ft_strncmp(op, "exit", 4))
		return (4);
	return (0);
}

int		get_operand_arg(t_shell *shell, char **input, char *op)
{
	int	nb_arg;

	nb_arg = get_nb_operand_arg(op);
}

int		add_left_node(t_shell *shell, t_tree *t_current, char **input, int len)
{
	char	*op;

	if (!(op = strdup_and_inc_input(shell, input, len)))
		return (FAILURE);
	if (!(t_current->left = tree_create_node(shell, op)))		// ajout operand dans le noeud left de t_current
		return (FAILURE);
	
	//	if(*input == ' ')
	//		(*input)++;
	//	else
	//		return (FAILURE);



	return (SUCCESS);
}

int		add_right_node(t_shell *shell, t_tree **t_current, char **input)
{
	char	*sep;
	int		res;

	sep = strdup_and_inc_input(shell, input, 1);
	if (!((*t_current)->right = tree_create_node(shell, sep)))
		return (FAILURE);
	*t_current = (*t_current)->right;
	shell->last_node = RIGHT;

	//	if(*input == ' ')
	//		(*input)++;
	//	else
	//		return (FAILURE);

	res = read_input(shell, t_current, input);

	if (!res || res == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

int		read_input(t_shell *shell, t_tree **t_current, char *input) 		// faut il trim les espaces ?
{
	int		len_op;
	t_tree	*node;

	if(!(*input))										// fin de l'input
		return (0);
	if(len_op = is_operand(input))						// operateur
	{
		if (shell->last_node == RIGHT)
			return (add_left_node(shell, *t_current, &input, len_op));
		return (FAILURE);
	}
	if (is_separator(*input))							// separateur
	{
		if (shell->last_node == LEFT)
			return (add_right_node(shell, t_current, &input));
		return (FAILURE);
	}
	return (FAILURE);
}

int		create_main_tree(t_shell *shell, char *input)
{
	int		is_end;
	t_tree	*t_current;

	if (!(shell->root = tree_create_node(shell, NULL)))
		return (FAILURE);
	t_current = shell->root;
	is_end = 1;
	while (is_end)
		is_end = read_input(shell, &t_current, &input);
	if(is_end == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}