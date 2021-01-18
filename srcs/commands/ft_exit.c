/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:41:38 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/18 08:30:12 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_full_digit(char *arg)
{
	if (*arg == '-' && !ft_isdigit(*(++arg)))
		return (0);
	while (*arg)
		if (!ft_isdigit(*(arg++)))
			return (0);
	if (!*arg)
		return (1);
	return (0);
}

void		ft_exit(t_shell *shell, char **exec_args, char **tab_env)
{
	(void)tab_env;
	// free_all_ptr(shell);			// A REMETTRE
	if (shell->lst_fd)
		ft_lstfd_close_clear(&(shell->lst_fd));
	if (exec_args[1])
	{
		if (exec_args[2])
			shell->exit = 1;
		else if (is_full_digit(exec_args[1]))
		{
			shell->exit = ft_atoi(exec_args[1]);
			shell->exit = shell->exit % 256;
		}
		else
			shell->exit = 255;
	}

	// ft_printf(shell->std[1], "exit\n");	// a enlever pour les tests ?
	
	exit(shell->exit);
}

void		ft_exit_status(t_shell *shell, int status)
{
	char	**exec_args;
	char	*str_status;
	char	*args;

	if (!(str_status = ft_itoa(status)))
		exit(EXIT_FAILURE);
	if (!(args = ft_strjoin("exit ", str_status)))
	{
		free(str_status);
		exit(EXIT_FAILURE);
	}
	exec_args = ft_split_args_quotes(shell, args);
	free(str_status);
	free(args);
	if (!exec_args)
		exit(EXIT_FAILURE);
	ft_exit(shell, exec_args, shell->tab_env);
}

void		ft_exit_failure(t_shell *shell, int int_failure, void *ptr)
{
	ft_free_ptr(ptr);
	
	if (!shell)
		exit(12);

	if (shell->lst_fd)
		ft_lstfd_close_clear(&(shell->lst_fd));
	// free_all_ptr(shell);			// A REMETTRE
	
	if (int_failure < 0)
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

// ft_exit_failure(shell, F_MALLOC, NULL);