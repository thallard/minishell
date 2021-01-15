/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/15 08:36:10 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_full_digit(char *arg)
{
	if (*arg == '-' && !ft_isdigit(*(++arg)))
		return (0);
	while (*arg)
		if (!ft_isdigit(*(arg++)))
			return (0);
	if (!*arg)
		return (1);
	return (0);
}

void		ft_exit(t_shell *shell, char **exec_args, char **tab_env)
{
	(void)tab_env;
	
	// free_all_ptr(shell);			// A REMETTRE
	if (shell->lst_fd)
		ft_lstfd_close_clear(&(shell->lst_fd));
	if (exec_args[1])
	{
		if (exec_args[2])
			shell->exit = 1;
		else if (is_full_digit(exec_args[1]))
		{
			shell->exit = ft_atoi(exec_args[1]);
			shell->exit = shell->exit % 256;
		}
		else
			shell->exit = 255;
	}

	ft_printf(shell->std[1], "exit\n");	// a enlever pour les tests ?
	
	exit(shell->exit);
}