/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:21:19 by thallard          #+#    #+#             */
/*   Updated: 2021/01/22 12:26:13 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_add_env_export_dollar(t_shell *shell, char *str)
{
	char	*str_env;

	if (!(str_env = ft_strdup(str)) || !add_lst_to_free(shell, str_env))
		ft_exit_failure(shell, F_MALLOC, str_env);
	replace_env_content(shell, "_", str_env, TO_PRINT);
}

int		ft_env(t_shell *shell, char **exec_args, char **tab_env)
{
	(void)exec_args;
	(void)tab_env;
	ft_add_env_export_dollar(shell, "env");
	ft_print_env_var(shell->var_env);
	return (SUCCESS);
}
