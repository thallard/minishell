/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:45:02 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/18 13:16:01 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		print_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
	shell->exit = 1;	// a verifier
	// exit (shell->exit);
	return (SUCCESS);
}

void	print_error_and_exit(t_shell *shell, char *cmd, int int_failure)
{
	ft_printf(STDERR_FILENO, "minishell: %s: %s\n", cmd, strerror(errno));
	ft_exit_failure(shell, int_failure, NULL);
}

void	ft_exit_split(t_shell *shell, char *str)	// doit-il exit le programme ?
{
	ft_printf(1, "%s", str);
	ft_exit_failure(shell, -1, NULL);
}
