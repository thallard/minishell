/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:21:19 by thallard          #+#    #+#             */
/*   Updated: 2021/01/13 13:30:38 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		ft_env(t_shell *shell, char **exec_args, char **tab_env, int to_print)
{	
	(void)exec_args;
	(void)tab_env;
	if (to_print == CHILD)
		ft_print_env_var(shell->var_env);
	return (SUCCESS);
}
