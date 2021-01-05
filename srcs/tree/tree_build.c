#include "../../includes/minishell.h"

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

	if (!(node = malloc_lst(shell, sizeof(t_tree))))
		return (NULL);
	node->item = item;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int		add_op_node(t_shell *shell, t_tree *t_current, char **input)
{
	int		res;

	res = SUCCESS;
	if (!(shell->op = strdup_and_inc_input(shell, input)))
		return (FAILURE);
	if (!(t_current->right = tree_create_node(shell, shell->op)))	// ajout operand dans le noeud right de t_current
		return (FAILURE);
// argument a ajouter
	if (is_operand(shell->op))
		res = get_operand_arg(shell, input, t_current->right);
	else
		if (!(t_current->right->left = get_next_arg_echo(shell, input, 2)))
			return (FAILURE);
	str_to_separator(input);
	shell->last_node = OP;
	return (res);
}

int		add_sep_node(t_shell *shell, t_tree **t_current, char **input)
{
	t_tree	*op_node;
<<<<<<< HEAD
=======
	// int		len_op;
>>>>>>> 3dfdc5636b151ae2b43fec68188279d62c17ef0b

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
<<<<<<< HEAD
=======
	// int		len_op;
	// t_tree	*node;

>>>>>>> 3dfdc5636b151ae2b43fec68188279d62c17ef0b
	skip_spaces(input);

	if(!(**input))										// fin de l'input
		return (EOL);
	if (is_separator(**input))							// separateur
	{
		if (shell->last_node == OP)
			return (add_sep_node(shell, t_current, input));
		if (!shell->sep)
			add_sep_node(shell, t_current, input);	//	erreur a gerer ;;
		return (DOUBLE_SEP);
	}
	return (add_op_node(shell, *t_current, input));
}

int		create_main_tree(t_shell *shell, char *input)
{
	int		is_end;
	t_tree	*t_current;

// ft_printf("\ninput = |%s|\n", input); ////////////////////////////

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
