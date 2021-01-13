/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 10:35:52 by bjacob           ###   ########lyon.fr   */
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

void		ft_exit(t_shell *shell, char **exec_args, char **tab_env, int to_print)
{
// dprintf(1, "builtin exit\n");		////////////////////////
	(void)to_print;
	(void)tab_env;

	// free_all_ptr(shell);			// A REMETTRE
	// ft_lstfd_close_clear(&shell->lst_fd);
	
	// if (to_print == CHILD)
	//	 ft_printf(1, "exit\n");

// ft_print_tab_char(exec_args);

	if (exec_args[1])
	{
		if (exec_args[2])
			shell->exit = 1;
		else if (is_full_digit(exec_args[1]))
		{
			shell->exit = ft_atoi(exec_args[1]);
			shell->exit = shell->exit % 256;
// dprintf(shell->std[1], "exit s = %d\n", shell->exit); ///////////////
		}
		else
			shell->exit = 255;

// dprintf(1, "bool = %d\n", is_full_digit(exec_args[1]));
	}
	exit(shell->exit);
}