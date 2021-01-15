/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:36:46 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/15 11:42:18 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_c(int sign)
{
	(void)sign;
	// c = 'b';
	// write(0, &c, 1);
	// ft_printf(0, "%c", 0);
	// ft_printf(0, "%c", 'a');
	ft_printf(1, "\n");
	// kill(0, SIGPIPE);
	// close(0);
}

void	ft_ctrl_back(int sign)
{
	ft_printf(1, "Quit: %d\n", sign);
}