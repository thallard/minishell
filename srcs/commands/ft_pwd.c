/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/20 15:58:41 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;
	char	*path_var;
	char	*path_cwd;

	(void)exec_args;
	(void)tab_env;
	res = SUCCESS;
	path_cwd = NULL;
	if (get_var_env(shell, "PWD", &path_var) && path_var &&
		!ft_strncmp(path_var, "//", 2))
		res = ft_printf(STDOUT_FILENO, "%s\n", path_var);
	else
	{
		if (!(path_cwd = ft_calloc(1, 500)))
			ft_exit_failure(shell, F_MALLOC, NULL);
		getcwd(path_cwd, 500);
		res = ft_printf(STDOUT_FILENO, "%s\n", path_cwd);
	}
	ft_free_ptr(path_cwd);
	shell->exit = 0;
	return (res);
}
