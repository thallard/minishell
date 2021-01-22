/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:42:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/22 09:16:26 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_search_wrong_character(char *str)
{
	int		i;
	int		alpha;

	alpha = 0;
	i = -1;
	while (str[++i])
		if (ft_isalpha(str[i]))
			alpha = 1;
		else if ((str[i] == '-') || char_not_valid(&str[i]) ||
				(!alpha && ft_isdigit(str[i])))
			return (0);
	return (1);
}

int			ft_unset(t_shell *shell, char **exec_args, char **tab_env)
{
	int		row;

	(void)tab_env;
	if (!exec_args[1])
	{
		shell->exit = 0;
		return (SUCCESS);
	}
	else
	{
		row = -1;
		while (exec_args[++row])
			if ((ft_search_wrong_character(exec_args[row])) == 1)
				ft_unset_hide_env(shell, &shell->var_env, exec_args[row]);
			else
			{
				shell->exit = 1;
				print_unset_error(shell, exec_args[row]);
				return (SUCCESS);
			}
	}
	shell->exit = 0;
	return (SUCCESS);
}
