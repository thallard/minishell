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
	t_tree	*node;

	len = 0;
	if (!skip_spaces(input))
		return (NULL);
	if (!(*input)[len])
	{
		if (!(node = tree_create_node(shell, NULL)))
			return (NULL);
		return (node);	// a confirmer
	}
	while((*input)[len] != ' ' && !is_separator((*input)[len]) && (*input)[len])
		len++;
	if (!len)
		{
			if (!(node = tree_create_node(shell, NULL)))
				return (NULL);
			return (node);
		}
	if (!(arg = malloc_lst(shell, len + 1)))
		return (NULL);
	i = 0;
	while (i < len)
		arg[i++] = *((*input)++);
	arg[i] = 0;
	if (!(node = tree_create_node(shell, arg)))
		return (NULL);
	return (node);
}

int		get_operand_arg(t_shell *shell, char **input, t_tree *op_node, char *op)
{
	int		nb_arg;
	char	*arg;

	nb_arg = get_nb_operand_arg(op);
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



int		add_op_node(t_shell *shell, t_tree *t_current, char **input, int len)
{
	char	*op;
	int		res;

	if (!(op = strdup_and_inc_input(shell, input, len)))
		return (FAILURE);

// ft_printf("op = |%s|\n", op); //////////////////////////


	if (!(t_current->right = tree_create_node(shell, op)))		// ajout operand dans le noeud right de t_current
		return (FAILURE);
		
// argument a ajouter

// ft_printf("current = |%s|\n", t_current->item); //////////////////////////
// ft_printf("current->right = |%s|\n", t_current->right->item); //////////////////////////

	res = get_operand_arg(shell, input, (t_current->right), op);

	shell->last_node = OP;

	return (res);
}



int		add_sep_node(t_shell *shell, t_tree **t_current, char **input)
{
	char	*sep;
	t_tree	*op_node;
	int		len_op;

	op_node = (*t_current)->right;
	sep = strdup_and_inc_input(shell, input, 1);
	if (!((*t_current)->right = tree_create_node(shell, sep)))
		return (FAILURE);
	*t_current = (*t_current)->right;
	(*t_current)->left = op_node;
	shell->last_node = SEP;
	return (read_input(shell, t_current, input));
}

int		read_input(t_shell *shell, t_tree **t_current, char **input) 		// faut il trim les espaces ?
{
	int		len_op;
	t_tree	*node;

//////////////////////////////////
if (shell->last_node == 1)
	ft_printf("\nl_node = OP\n\n");
else
	ft_printf("\nl_node = SEP\n\n");
///////////////////////////////////

	skip_spaces(input);

	if(!(**input))										// fin de l'input
		return (EOL);
	if((len_op = is_operand(*input)))						// operateur
	{
		if (shell->last_node == SEP)
			return (add_op_node(shell, *t_current, input, len_op));
		return (FAILURE);
	}
	if (is_separator(**input))							// separateur
	{
		if (shell->last_node == OP)
			return (add_sep_node(shell, t_current, input));
		return (DOUBLE_SEP);
	}
	return (FAILURE);
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
