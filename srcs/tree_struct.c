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

char	*strdup_and_inc_input(t_shell *shell, char **input)
{
	char	*op;
	int		i;
	int		len;

	len = 0;
	if (is_separator((*input)[len]))
		len++;
	else
	{
		while ((*input)[len] != ' ' && !is_separator((*input)[len]) && (*input)[len])
			len++;
	}
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
				len_char = len - 1;
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
	char	*arg;

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

int		get_operand_arg(t_shell *shell, char **input, t_tree *op_node)
{
	int		nb_arg;
	char	*arg;

	if ((nb_arg = get_nb_operand_arg(shell->op)) == 2)
		return (get_echo_arg(shell, input, op_node));
	if (nb_arg-- > 0)
	{
		if (!(op_node->left = get_next_arg(shell, input)))	// echo a gerer a part
			return (FAILURE);
	}
	if (nb_arg > 0)						//	gestion de echo
	{
		if (!ft_strncmp(op_node->left->item, "-n", 3))
			op_node->right = get_next_arg(shell, input);
		else
		{
			op_node->right = op_node->left;
			if (!(op_node->left = tree_create_node(shell, NULL)))
				return (FAILURE);
		}
	}
	return (SUCCESS);
}


int		add_op_node(t_shell *shell, t_tree *t_current, char **input)
{
	int		res;

	if (!(shell->op = strdup_and_inc_input(shell, input)))
		return (FAILURE);

	if (!(t_current->right = tree_create_node(shell, shell->op)))		// ajout operand dans le noeud right de t_current
		return (FAILURE);
		
// argument a ajouter
	if (is_operand(shell->op))
		res = get_operand_arg(shell, input, (t_current->right));

	str_to_separator(input);

	shell->last_node = OP;

	return (res);
}

int		add_sep_node(t_shell *shell, t_tree **t_current, char **input)
{
	t_tree	*op_node;
	int		len_op;

	op_node = (*t_current)->right;
	shell->sep = strdup_and_inc_input(shell, input);
	if (!((*t_current)->right = tree_create_node(shell, shell->sep)))
		return (FAILURE);
	*t_current = (*t_current)->right;
	(*t_current)->left = op_node;
	shell->last_node = SEP;
	return (read_input(shell, t_current, input));
}

int		read_input(t_shell *shell, t_tree **t_current, char **input)
{
	int		len_op;
	t_tree	*node;

	skip_spaces(input);

	if(!(**input))										// fin de l'input
		return (EOL);
	if (is_separator(**input))							// separateur
	{
		if (shell->last_node == OP)
			return (add_sep_node(shell, t_current, input));
		if (!shell->sep)
			add_sep_node(shell, t_current, input);
		return (DOUBLE_SEP);
	}
	return (add_op_node(shell, *t_current, input));
}

int		create_main_tree(t_shell *shell, char *input)
{
	int		is_end;
	t_tree	*t_current;


ft_printf("\ninput = |%s|\n", input); ////////////////////////////

	if (!(shell->root = tree_create_node(shell, "ROOT")))		// a supprimer, juste pour les tests
	// if (!(shell->root = tree_create_node(shell, NULL)))
		return (FAILURE);
	t_current = shell->root;
	shell->last_node = SEP;		// a confirmer

	is_end = SUCCESS;
	while (is_end == SUCCESS)
		is_end = read_input(shell, &t_current, &input);
	return (is_end);
}
