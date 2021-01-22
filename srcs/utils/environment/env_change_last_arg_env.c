/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_change_last_arg_env.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:50:02 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 10:17:34 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_last_arg_env(t_shell *shell, t_tree *node)
{
	int		i;
	char	*str;
	char	**exec_args;

	exec_args = node->args->args;
	if (exec_args && ft_strncmp(exec_args[0], "export", 7))
	{
		exec_args = node->args->args;
		if (exec_args)
		{
			i = 0;
			while (exec_args[i + 1])
				i++;
			if (!(str = ft_strdup(exec_args[i])) || !add_lst_to_free(shell, str))
				ft_exit_failure(shell, F_MALLOC, str);
			replace_env_content(shell, "_", str, 0);
		}
	}
}
