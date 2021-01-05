#include "../../includes/minishell.h"

int		get_nb_operand_arg(char *op)
{
	if(!ft_strncmp(op, "echo", 4))
		return (2);
	if (!ft_strncmp(op, "cd", 2) ||
		!ft_strncmp(op, "export", 6) ||
		!ft_strncmp(op, "unset", 5))
		return (1);
	if (!ft_strncmp(op, "pwd", 3) ||
		!ft_strncmp(op, "env", 3) ||
		!ft_strncmp(op, "exit", 4))
		return (0);
	return (FAILURE);
}

t_tree	*get_next_arg_echo(t_shell *shell,char **input, int nb_arg)
{
	char	*arg;
	int		len;
	int		len_char;
	int		i;

	len = 0;
	skip_spaces(input);
	if (!(**input) || is_separator(**input))
		return(tree_create_node(shell, NULL));
	if (nb_arg == 1 && !strncmp(*input, "-n", 2) &&
		((*input)[2] == ' ' || is_separator((*input)[2]) || !(*input)[2]))
		len_char = 2;
	else
		while(!is_separator((*input)[len]) && (*input)[len])
			if ((*input)[len++] != ' ')
				len_char = len;
	if (!(arg = malloc_lst(shell, len_char + 1)))
		return (NULL);
	i = 0;
	while (i < len_char)
		arg[i++] = *((*input)++);
	arg[i] = 0;
	return(tree_create_node(shell, arg));
}

int		get_echo_arg(t_shell *shell, char **input, t_tree *op_node)
{

	if (!(op_node->left = get_next_arg_echo(shell, input, 1)))
		return (FAILURE);
	if (!ft_strncmp(op_node->left->item, "-n", 3))
		op_node->right = get_next_arg_echo(shell, input, 2);
	else
	{
		op_node->right = op_node->left;
		if (!(op_node->left = tree_create_node(shell, NULL)))
			return (FAILURE);
	}
	return (SUCCESS);
}

t_tree	*get_next_arg(t_shell *shell,char **input)
{
	char	*arg;
	int		len;
	int		i;

	len = 0;
	skip_spaces(input);
	if (!(*input)[len] || is_separator((*input)[len]))
		return (tree_create_node(shell, NULL));
	while((*input)[len] != ' ' && !is_separator((*input)[len])
			&& (*input)[len])
		len++;
	if (!(arg = malloc_lst(shell, len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		arg[i++] = *((*input)++);
	arg[i] = 0;
	return(tree_create_node(shell, arg));
}

int		get_operand_arg(t_shell *shell, char **input, t_tree *op_node)
{
	int		nb_arg;

	if ((nb_arg = get_nb_operand_arg(shell->op)) == 2)
		return (get_echo_arg(shell, input, op_node));
	if (nb_arg-- > 0)
	{
		if (!(op_node->left = get_next_arg(shell, input)))
			return (FAILURE);
	}
	return (SUCCESS);
}