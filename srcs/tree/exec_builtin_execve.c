/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_execve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:22:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 14:47:31 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exec(t_shell *shell, char *exec_path, t_tree *node)
{
	char	**exec_args;

	exec_args = node->args->args;
	if (!ft_strncmp_lower(exec_path, "echo", 5))
		return (ft_echo(shell, exec_args, node->args->null));
	if (!ft_strncmp_lower(exec_path, "cd", 3))
		return (ft_cd(shell, exec_args, shell->tab_env));
	if (!ft_strncmp_lower(exec_path, "pwd", 4))
		return (ft_pwd(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "export", 7))
		return (ft_export(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "unset", 6))
		return (ft_unset(shell, exec_args, shell->tab_env));
	if (!ft_strncmp_lower(exec_path, "env", 4))
		return (ft_env(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "exit", 5))
		ft_exit(shell, exec_args, shell->tab_env);
	else
		return (execve(exec_path, exec_args, shell->tab_env));
	return (SUCCESS);
}

static void	exec_child(t_shell *shell, t_tree *node, int pipe_fd[2][2])
{
	char	*exec_path;

	exec_path = node->exec_path;
	if (dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO) == -1 ||
		dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO) == -1)
		print_error_and_exit(shell, "dup", -1);
	if (close(pipe_fd[shell->last_pipe][0]) == -1 ||
		close(pipe_fd[1 - shell->last_pipe][1]) == -1)
		print_error_and_exit(shell, "close", -1);
	if (manage_redirection(shell, node->dir) == FAILURE)
		exit(1);
	if (ft_exec(shell, exec_path, node) == -1)
		exit(127);
}

static void	exec_parent(t_shell *shell, t_tree *node, pid_t program)
{
	(void)node;
	waitpid(program, &(shell->exit), 0);
	if (shell->exit < 256)
	{
		if (shell->exit == 2)
			shell->exit = 130;
		else if (shell->exit == 3)
			shell->exit = 131;
	}
	else
		shell->exit /= 256;
	reset_stds(shell);
	signal(SIGQUIT, SIG_IGN);
}

int			exec_builtin(t_shell *shell, t_tree *node, int pipe_fd[2][2],
						int is_pipe)
{
	if ((is_pipe / 2 < 1) &&
		dup2(0, pipe_fd[1 - shell->last_pipe][0]) == -1)
		return (print_error(shell, "dup", 1));
	if ((is_pipe % 2 != PIPE_OUT) &&
		dup2(1, pipe_fd[shell->last_pipe][1]) == -1)
		return (print_error(shell, "dup", 1));
	if (dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO) == -1 ||
		dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO) == -1)
		return (print_error(shell, "dup", 1));
	if (manage_redirection(shell, node->dir) == FAILURE)
		return (SUCCESS);
	ft_exec(shell, node->exec_path, node);
	if (close(pipe_fd[shell->last_pipe][1]) == -1 ||
		close(pipe_fd[1 - shell->last_pipe][0]) == -1)
		return (print_error(shell, "close", 1));
	reset_stds(shell);
	return (SUCCESS);
}

int			exec_execve(t_shell *shell, t_tree *node, int pipe_fd[2][2],
						int is_pipe)
{
	pid_t	program;

	if ((program = fork()) == -1)
		ft_exit_failure(shell, F_FORK, NULL);
	if (!program)
	{
		signal(SIGQUIT, SIG_DFL);
		if (is_pipe / 2 < 1 && dup2(0, pipe_fd[1 - shell->last_pipe][0]) == -1)
			print_error_and_exit(shell, "dup", -1);
		if (is_pipe % 2 != PIPE_OUT &&
			dup2(1, pipe_fd[shell->last_pipe][1]) == -1)
			print_error_and_exit(shell, "dup", -1);
		exec_child(shell, node, pipe_fd);
	}
	else
	{
		signal(SIGQUIT, &ft_ctrl_back);
		if (close(pipe_fd[shell->last_pipe][1]) == -1 ||
			close(pipe_fd[1 - shell->last_pipe][0]) == -1)
			return (print_error(shell, "close", 1));
		exec_parent(shell, node, program);
	}
	return (SUCCESS);
}
