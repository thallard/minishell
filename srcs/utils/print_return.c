/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:45:02 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 13:28:05 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_header(int fd)
{
	if (PRINT_HEADER)
		ft_printf(fd, "minishell$ ");
}

int		print_error(t_shell *shell, char *cmd, int exit_status)
{
	ft_printf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
	shell->exit = exit_status;
	return (FAILURE);
}

int		print_exit_error(t_shell *shell, char *arg, char *text, int exit_status)
{
	ft_printf(STDERR_FILENO, "minishell: exit: %s%s\n", arg, text);
	shell->exit = exit_status;
	return (SUCCESS);
}

void	print_error_and_exit(t_shell *shell, char *cmd, int int_failure)
{
	ft_printf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
	ft_exit_failure(shell, int_failure, NULL);
}

void	ft_exit_split(t_shell *shell, char *str)
{
	ft_printf(1, "%s", str);
	ft_exit_failure(shell, -1, NULL);
}
