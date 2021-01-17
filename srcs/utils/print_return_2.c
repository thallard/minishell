/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_return_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/17 15:30:13 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/17 15:33:02 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_header(int fd)
{
	if (PRINT_HEADER)
		ft_printf(fd, "minishell$ ");
}

int		print_oldpwd_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO, "minishell: %s: OLDPWD not set\n", cmd);
	shell->exit = 0;
	return (SUCCESS);
}

int		print_unset_error(t_shell *shell, char *cmd)
{
	ft_printf(STDERR_FILENO, "minishell: unset: `%s': not a valid identifier\n", cmd);
	shell->exit = 1;
	return (SUCCESS);
}

int		ft_cmd_not_found(t_shell *shell, char *exec)
{
	(void)shell;					// utilite de shell ?
	ft_printf(STDERR_FILENO, "minishell: %s: command not found\n", exec);	// message a ajuster
	shell->exit = 127;	// selon test
	return (SUCCESS);
}
