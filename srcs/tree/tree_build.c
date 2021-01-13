/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:37:10 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 11:22:56 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_tree	*tree_create_node(t_shell *shell, char **args, t_dir **dir)
{
	t_tree	*node;

	if (!(node = malloc_lst(shell, sizeof(t_tree))))
		return (NULL);
	node->args = args;
	node->dir = dir;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

int		add_op_node(t_shell *shell, t_tree *t_current, char **input)
{
	int		res;
	char	**tab;
	t_dir	**dir;

	res = SUCCESS;
	if (!(shell->op = strdup_and_inc_input(shell, input)))
		return (FAILURE);
	ft_split_args_quotes(shell, shell->op);
	if (!(tab = ft_split_minishell_args(shell->op, ' ', shell)))
		return (FAILURE);
	// if (!(dir = ft_split_redirection(shell, shell->op)))
	if (!(dir = ft_split_minishell_dir(shell->op, ' ', shell)))
		return (FAILURE);

	if (!(t_current->right = tree_create_node(shell, tab, dir)))
		return (FAILURE);
	// if (!(t_current->right->left = tree_create_node(shell, NULL, dir)))
	// 	return (FAILURE);

	// if (is_operand(shell->op))
	// {
	// 	if (!(t_current->right->left = get_next_arg_echo(shell, input, 2)))
	// 		return (FAILURE);
	// 	// res = get_operand_arg(shell, input, t_current->right);
	// }
	// else 
	// if (!(t_current->right->left = get_next_arg_echo(shell, input, 2)))
	// 	return (FAILURE);
	str_to_separator(input);
	shell->last_node = OP;
	return (res);
}

int		add_sep_node(t_shell *shell, t_tree **t_current, char **input)
{
	t_tree	*op_node;
	char	**tab;

	op_node = (*t_current)->right;
	shell->sep = strdup_and_inc_input(shell, input);

	if (!(tab = ft_split_minishell_args(shell->sep, ' ', shell)))
		return (FAILURE);

	if (!((*t_current)->right = tree_create_node(shell, tab, NULL)))
		return (FAILURE);
	*t_current = (*t_current)->right;
	(*t_current)->left = op_node;
	shell->last_node = SEP;
	return (read_input(shell, t_current, input));
}

int		read_input(t_shell *shell, t_tree **t_current, char **input)
{
	skip_spaces(input);
	if (!(**input))
		return (EOL);
	if (is_separator(**input))
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
	char	**root;

	if (!(root = ft_split_minishell_args("ROOT", ' ', shell)))
		return (FAILURE);
	if (!(shell->root = tree_create_node(shell, root, NULL)))
		return (FAILURE);
	t_current = shell->root;
	shell->last_node = SEP;		// a confirmer
	is_end = SUCCESS;
	while (is_end == SUCCESS)
		is_end = read_input(shell, &t_current, &input);
	return (is_end);
}
