/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/12 11:45:35 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_exit(t_shell *shell, int to_print)
{
// dprintf(1, "builtin exit\n");		////////////////////////

	(void)to_print;

	// free_all_ptr(shell);
	// if (to_print == CHILD)
	//	 ft_printf(1, "exit\n");
	exit(shell->exit);
	return ;
}