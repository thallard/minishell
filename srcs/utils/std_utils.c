/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:00:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:31:34 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	reset_stds(t_shell *shell)
{
	ft_lstfd_close_clear(&shell->lst_fd);
	if (dup2(shell->std[0], STDIN_FILENO) == -1 ||
		dup2(shell->std[1], STDOUT_FILENO) == -1 ||
		dup2(shell->std[2], STDERR_FILENO) == -1)
		return (print_error(shell, "dup", 1));
	return (SUCCESS);
}
