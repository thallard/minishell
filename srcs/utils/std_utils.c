/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:00:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 14:41:46 by bjacob           ###   ########lyon.fr   */
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

int	print_dir_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO, "minishell: %s: is a directory\n", cmd);
	shell->exit = 126;
	return (SUCCESS);
}

int	print_dir_file_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO, "minishell: %s: No such file or directory\n", cmd);
	shell->exit = 127;
	return (SUCCESS);
}
