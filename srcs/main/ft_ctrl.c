/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ctrl.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 11:36:46 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/15 10:20:29 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_ctrl_c(int sign)
{
	(void)sign;
	ft_printf(1, "\n");
}

void	ft_ctrl_back(int sign)
{
	ft_printf(1, "Quit: %d\n", sign);
}