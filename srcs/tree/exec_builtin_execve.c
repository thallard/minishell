/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_execve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 09:32:49 by bjacob            #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/01/14 18:33:31 by thallard         ###   ########lyon.fr   */
=======
/*   Updated: 2021/01/15 10:21:57 by bjacob           ###   ########lyon.fr   */
>>>>>>> 8de0ec3c7e7139c91cde93cb19b9c493fe052820
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exec(t_shell *shell, char *exec_path, char **exec_args, int to_print)
{
	if (!ft_strncmp(exec_path, "echo", 5))
		return (ft_echo(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "cd", 3))
		return (ft_cd(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "pwd", 4))
		return (ft_pwd(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "export", 7))
	 	return (ft_export(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "unset", 6))
		return (ft_unset(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "env", 4))
		return (ft_env(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "exit", 5))
		ft_exit(shell, exec_args, shell->tab_env);
	if (to_print == CHILD)
		return (execve(exec_path, exec_args, shell->tab_env));
	else
		return (SUCCESS);
}

static void	exec_child(t_shell *shell, t_tree *node, int pipe_fd[2][2])
{
	char	*exec_path;

	exec_path = node->exec_path;
	dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO);
	dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO);
	close(pipe_fd[shell->last_pipe][0]);
	close(pipe_fd[1 - shell->last_pipe][1]);
	if (ft_exec(shell, exec_path, node->args, CHILD) == -1)
		exit(FAILURE);	// bonne valeur
	exit(shell->exit);
}

static void	exec_parent(t_shell *shell, t_tree *node, pid_t program)
{
	char	*exec_path;

	exec_path = node->exec_path;
	waitpid(program, &(shell->exit), 0);
	shell->exit /= 256;				// pourquoi ?
	dup2(shell->std[0], STDIN_FILENO);	// pour les redirections
	dup2(shell->std[1], STDOUT_FILENO);
	signal(SIGQUIT,SIG_IGN);
}

int			exec_builtin(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	if (is_pipe / 2 < 1)	// if !PIPE_IN
		dup2(0, pipe_fd[1 - shell->last_pipe][0]);
	if (is_pipe % 2 != PIPE_OUT)
		dup2(1, pipe_fd[shell->last_pipe][1]);

	dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO);
	dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO);

	if (ft_exec(shell, node->exec_path, node->args, CHILD) == -1)
		exit(FAILURE);	// bonne valeur

	close(pipe_fd[shell->last_pipe][1]);
	close(pipe_fd[1 - shell->last_pipe][0]);
	
	dup2(shell->std[0], STDIN_FILENO);	// pour les redirections
	dup2(shell->std[1], STDOUT_FILENO);

	return (SUCCESS);
}

int			exec_execve(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	pid_t	program;

	if ((program = fork()) == -1)
		return (FAILURE);	// a gerer
	if (!program) // erreur a gerer si program = -1 ?
	{
		
		signal(SIGQUIT,SIG_DFL);

		if (is_pipe / 2 < 1)	// if !PIPE_IN
			dup2(0, pipe_fd[1 - shell->last_pipe][0]);
		if (is_pipe % 2 != PIPE_OUT)
			dup2(1, pipe_fd[shell->last_pipe][1]);
		exec_child(shell, node, pipe_fd);
	}
	else
	{
		signal(SIGQUIT, &ft_ctrl_back);

		close(pipe_fd[shell->last_pipe][1]);
		close(pipe_fd[1 - shell->last_pipe][0]);
		exec_parent(shell, node, program);


	}


	return (SUCCESS);
}
