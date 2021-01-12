/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:42:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/12 11:57:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_search_wrong_character(char *str)
{
	int		i;
	int		alpha;

	alpha = 0;
	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
			alpha = 1;
		else if ((str[i] == '-') ||
				(alpha == 0 && ft_isdigit(str[i])))
			return (0);
	return (1);
}

// int		ft_unset(t_shell *shell, t_tree *node)
int		ft_unset(t_shell *shell, char **exec_args, char **tab_env, int to_print)
{
	// char	**tab;
	int		row;

(void)tab_env;

	if (!exec_args[1])
	{
		shell->exit = 1;
		return (SUCCESS);	// FAILURE ou SUCCESS
	}
	else
	{
		row = -1;
		// tab = ft_split_minishell_args(exec_args[1], ' ', shell);
		while (exec_args[++row])
			if ((ft_search_wrong_character(exec_args[row])) == 1)
				ft_env_remove_if(&shell->var_env, exec_args[row], &ft_strncmp);
			else if (to_print == CHILD)
				print_unset_error(shell, exec_args[row]);
	}
	shell->exit = 0;
	return (SUCCESS);
}