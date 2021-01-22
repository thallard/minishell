/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin_execve.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:22:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 09:00:36 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exec(t_shell *shell, char *exec_path, t_tree *node)
{
	char	**exec_args;

	exec_args = node->args->args;
	if (!ft_strncmp(exec_path, "echo", 5))
		return (ft_echo(shell, exec_args, node->args->null));
	if (!ft_strncmp(exec_path, "cd", 3))
		return (ft_cd(shell, exec_args, shell->tab_env));	// retour a gerer
	if (!ft_strncmp(exec_path, "pwd", 4))
		return (ft_pwd(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "export", 7))
	 	return (ft_export(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "unset", 6))					// retour a gerer
		return (ft_unset(shell, exec_args, shell->tab_env));
	if (!ft_strncmp(exec_path, "env", 4))
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
		print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status
	if (close(pipe_fd[shell->last_pipe][0]) == -1 ||
		close(pipe_fd[1 - shell->last_pipe][1]) == -1)
		print_error_and_exit(shell, "close", -1 * EBADF); // possible exit status

	if (manage_redirection(shell, node->dir) == FAILURE)
			exit(1) ; // a confirmer	
		
	if (ft_exec(shell, exec_path, node) == -1)	// if execve == -1
		;		// faire quelque chose ?
		// shell->exit = EXIT_FAILURE;	// bonne valeur ?
	// exit(shell->exit);
}

static void	exec_parent(t_shell *shell, t_tree *node, pid_t program)
{
	(void)node;

	waitpid(program, &(shell->exit), 0);
	
	shell->exit /= 256;				// pourquoi ?

// dprintf(1, "exit status = %d\n", shell->exit);

	reset_stds(shell);
	// if (dup2(shell->std[0], STDIN_FILENO) == -1 ||
	// 	dup2(shell->std[1], STDOUT_FILENO) == -1 ||
	// 	dup2(shell->std[2], STDERR_FILENO) == -1)
	// 	print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status
	signal(SIGQUIT,SIG_IGN);
}

int			exec_builtin(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	if ((is_pipe / 2 < 1) &&
		dup2(0, pipe_fd[1 - shell->last_pipe][0]) == -1)	// if !PIPE_IN
		print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status
	if ((is_pipe % 2 != PIPE_OUT) &&
		dup2(1, pipe_fd[shell->last_pipe][1]) == -1)
		print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status
	if (dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO) == -1 ||
		dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO) == -1)
		print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status

	if (manage_redirection(shell, node->dir) == FAILURE)
		return (SUCCESS); // a confirmer

	if (ft_exec(shell, node->exec_path, node) == -1)	// A CHECKER
		exit(FAILURE);	// bonne valeur

	if (close(pipe_fd[shell->last_pipe][1]) == -1 ||
		close(pipe_fd[1 - shell->last_pipe][0]) == -1)
		// print_error_and_exit(shell, "close", -1 * EBADF); // possible exit status
		return (print_error(shell, "close", 1));	// a confirmer vs ligne du dessus

	reset_stds(shell);

	return (SUCCESS);
}

int			exec_execve(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	pid_t	program;

	if ((program = fork()) == -1)
		ft_exit_failure(shell, F_FORK, NULL);
	if (!program) // erreur a gerer si program = -1 ?
	{
		signal(SIGQUIT,SIG_DFL);

		if (is_pipe / 2 < 1 && dup2(0, pipe_fd[1 - shell->last_pipe][0]) == -1) // if !PIPE_IN
			print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status
		if (is_pipe % 2 != PIPE_OUT &&
			dup2(1, pipe_fd[shell->last_pipe][1]) == -1)
			print_error_and_exit(shell, "dup", -1 * EMFILE); // possible exit status
		
		exec_child(shell, node, pipe_fd);
	}
	else
	{
		signal(SIGQUIT, &ft_ctrl_back);

		if (close(pipe_fd[shell->last_pipe][1]) == -1 ||
			close(pipe_fd[1 - shell->last_pipe][0]) == -1)
			print_error_and_exit(shell, "close", -1 * EBADF); // possible exit status
		exec_parent(shell, node, program);
	}
	return (SUCCESS);
}
