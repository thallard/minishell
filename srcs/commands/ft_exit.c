/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 14:18:03 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_full_digit(char *arg)
{
	while (*arg == ' ')
		arg++;
	if ((*arg == '-' || *arg == '+') && !ft_isdigit(*(++arg)))
		return (0);
	while (*arg && ft_isdigit(*arg))
		arg++;
	while (*arg == ' ')
		arg++;
	if (!*arg)
		return (1);
	return (0);
}

int			ft_exit(t_shell *shell, char **exec_args, char **tab_env)
{
	(void)tab_env;
	if (exec_args[1] && exec_args[2])
	{
		if (!is_full_digit(exec_args[1]))
			return (print_exit_error(shell, exec_args[1],
					": numeric argument required", 255));
		else if (exec_args[2])
			return (print_exit_error(shell, "", "too many arguments", 1));
	}
	if (exec_args[1])
	{
		if (!is_full_digit(exec_args[1]))
			print_exit_error(shell, exec_args[1],
					": numeric argument required", 255);
		else
			shell->exit = ft_atoi(exec_args[1]) % 256;
	}
	ft_printf(STDERR_FILENO, "exit\n");
	if (shell->lst_fd)
		ft_lstfd_close_clear(&(shell->lst_fd));
	free_all_ptr(shell);
	exit(shell->exit);
}

void		ft_exit_failure(t_shell *shell, int int_failure, void *ptr)
{
	ft_free_ptr(ptr);
	if (!shell)
		exit(12);
	if (shell->lst_fd)
		ft_lstfd_close_clear(&(shell->lst_fd));
	if ((free_all_ptr(shell) == SUCCESS) && (int_failure < 0))
		shell->exit = ft_abs(int_failure);
	if (int_failure == F_MALLOC)
	{
		shell->exit = F_MALLOC;
		ft_printf(2, "A malloc has failed\n");
	}
	if (int_failure == F_FORK)
	{
		shell->exit = F_FORK;
		ft_printf(2, "No child processes\n");
	}
	else if (int_failure == NO_EXEC_PATH)
	{
		shell->exit = 1;
		ft_printf(2, "Exec_path variable not found\n");
	}
	else if (int_failure > 0)
		ft_printf(2, "An error has occured\n");
	exit(shell->exit);
}
