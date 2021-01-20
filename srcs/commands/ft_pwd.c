/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/20 15:40:10 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;
	char	*path;
	// int		useless;

	(void)shell;
	(void)exec_args;
	(void)tab_env;
	res = SUCCESS;
	// path_double = NULL;
	if (!(path = ft_calloc(1, 500)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	
	// if (get_var_env(shell, "PWD", &path) && !ft_strncmp(path, "//", 2))
	if (get_var_env(shell, "PWD", &path) && path)
	{		
		res = ft_printf(STDOUT_FILENO, "%s\n", path);
	}
	else
	{
		getcwd(path, 500);
		res = ft_printf(STDOUT_FILENO, "%s\n", path);
	}
	
	// else
	// {
		
	// }
		
		// \n a conserver ?	
	// free(path);
	shell->exit = 0;
	return (res);
}
