/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/12 15:59:38 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_full_digit(char *arg)
{
	if (*arg == '-' && !ft_isdigit(*(++arg)))
		return (1);
	while (*arg)
		if (!ft_isdigit(*(arg++)))
			return (0);
	if (!*arg)
		return (0);
	return (1);
}

void		ft_exit(t_shell *shell, char **exec_args, char **tab_env, int to_print)
{
// dprintf(1, "builtin exit\n");		////////////////////////

	(void)to_print;
	(void)shell;
	(void)tab_env;
	(void)exec_args;

	// free_all_ptr(shell);			// A REMETTRE
	// if (to_print == CHILD)
	//	 ft_printf(1, "exit\n");

	if (exec_args[1])
	{
		if (exec_args[2])
			shell->exit = 1;
		else if (is_full_digit(exec_args[1]))
			shell->exit = ft_atoi(exec_args[1]);
		else
			shell->exit = 255;
	}
	
	exit(shell->exit);
}