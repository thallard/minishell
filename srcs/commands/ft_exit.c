/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/11 14:44:05 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void		ft_exit(t_shell *shell)
{
	free_all_ptr(shell);
	// ft_printf(1, "exit\n");
	exit(shell->exit);
	return ;
}