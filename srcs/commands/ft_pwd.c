/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/12 11:45:32 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_shell *shell, char **exec_args, char **tab_env, int to_print)
{
	int		res;
	char	*path;

// dprintf(1, "builtin pwd\n");	////////////////////////

	(void)shell;
	(void)exec_args;
	(void)tab_env;
	res = SUCCESS;
	path = ft_calloc(1, 500);	// a proteger
	getcwd(path, 500);
	if (to_print == CHILD)
		res = ft_printf(STDOUT_FILENO, "%s\n", path);	// \n a conserver ?
	return (res);
}
