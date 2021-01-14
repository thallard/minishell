/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:31:58 by thallard          #+#    #+#             */
/*   Updated: 2021/01/14 13:11:50 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_pwd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;
	char	*path;

// dprintf(shell->std[1], "p3\n");

dprintf(1, "pwd0\n");

	(void)shell;
	(void)exec_args;
	(void)tab_env;
	res = SUCCESS;
	if (!(path = ft_calloc(1, 500)))
		return (FAILURE);
	getcwd(path, 500);

// dprintf(shell->std[1], "p5\n");
// dprintf(shell->std[1], "path = %s\n", path);


	// if (to_print == CHILD)
		res = ft_printf(STDOUT_FILENO, "%s\n", path);	// \n a conserver ?
// dprintf(shell->std[1], "res = %d\n", res);

		
	free(path);
	shell->exit = 0;

// dprintf(shell->std[1], "p4\n");


	return (res);
}
