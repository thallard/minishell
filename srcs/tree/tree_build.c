/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_build.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:37:10 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/18 15:29:04 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_tree	*tree_create_node(t_shell *shell, t_args *args, t_dir **dir)
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

static int		add_op_node(t_shell *shell, t_tree *t_current, char **input)
{
	int		res;
	t_args	*args;
	t_dir	**dir;

	res = SUCCESS;
	shell->op = strdup_and_inc_input(shell, input);

// dprintf(1, "shell->op = |%s|\n", shell->op);	///////

		
	if (!(args = ft_split_args(shell, shell->op)))
		ft_exit_failure(shell, F_MALLOC, NULL);
// ft_print_tab_char(args->args);
		
	if (!(dir = ft_split_redirection(shell, shell->op)))
	// if (!(dir = ft_split_minishell_dir(shell->op, ' ', shell)))
		ft_exit_failure(shell, F_MALLOC, NULL);

	if (!(t_current->right = tree_create_node(shell, args, dir)))
		ft_exit_failure(shell, F_MALLOC, NULL);

	str_to_separator(input);
	shell->last_node = OP;
	return (res);
}

// static int		add_op_node(t_shell *shell, t_tree *t_current, char **input)
// {
// 	int		res;
// 	t_args	*args;
// 	t_dir	**dir;

// 	res = SUCCESS;
// 	if (!(shell->op = strdup_and_inc_input(shell, input)))
// 		return (FAILURE);
// 	if (!(args = ft_split_args_quotes(shell, shell->op)))
// 		return (FAILURE);
// 	if (!(dir = ft_split_redirection(shell, shell->op)))
// 	// if (!(dir = ft_split_minishell_dir(shell->op, ' ', shell)))
// 		return (FAILURE);

// 	if (!(t_current->right = tree_create_node(shell, args, dir)))
// 		return (FAILURE);

// 	str_to_separator(input);
// 	shell->last_node = OP;
// 	return (res);
// }

static int		add_sep_node(t_shell *shell, t_tree **t_current, char **input)
{
	t_tree	*op_node;
	t_args	*args;

	op_node = (*t_current)->right;
	shell->sep = strdup_and_inc_input(shell, input);
	if (!(args = ft_split_args(shell, shell->sep)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!((*t_current)->right = tree_create_node(shell, args, NULL)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	*t_current = (*t_current)->right;
	(*t_current)->left = op_node;
	shell->last_node = SEP;
	return (read_input(shell, t_current, input));
}

int		read_input(t_shell *shell, t_tree **t_current, char **input)
{
	skip_spaces(input);
	if (!(**input))
		return (SUCCESS + 1);
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
	t_args	*root;

	if (!(root = ft_split_args(shell, "ROOT")))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(shell->root = tree_create_node(shell, root, NULL)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	t_current = shell->root;
	shell->last_node = SEP;		// a confirmer
	is_end = SUCCESS;
	while (is_end == SUCCESS)
		is_end = read_input(shell, &t_current, &input);
	return (is_end);
}
