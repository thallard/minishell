/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:54:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 16:45:54 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_exec(t_shell *shell, char *exec_path, char **exec_args, int to_print)
{
	if (!ft_strncmp(exec_path, "echo", 5))
		return (ft_echo(shell, exec_args, shell->tab_env, to_print));
	if (!ft_strncmp(exec_path, "cd", 3))
		return (ft_cd(shell, exec_args, shell->tab_env, to_print));
	if (!ft_strncmp(exec_path, "pwd", 4))
		return (ft_pwd(shell, exec_args, shell->tab_env, to_print));
	if (!ft_strncmp(exec_path, "export", 7))
	 	return (ft_export(shell, exec_args, shell->tab_env, to_print));
	if (!ft_strncmp(exec_path, "unset", 6))
		return (ft_unset(shell, exec_args, shell->tab_env, to_print));
	if (!ft_strncmp(exec_path, "env", 4))
		return (ft_env(shell, exec_args, shell->tab_env, to_print));
	if (!ft_strncmp(exec_path, "exit", 5))
		ft_exit(shell, exec_args, shell->tab_env, to_print);
	if (to_print == CHILD)
		return (execve(exec_path, exec_args, shell->tab_env));
	else
		return (SUCCESS);
}

static void	exec_child(t_shell *shell, t_tree *node, int pipe_fd[2][2], char *exec_path)
{
	dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO);
	dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO);
	close(pipe_fd[shell->last_pipe][0]);
	close(pipe_fd[1 - shell->last_pipe][1]);
	if (ft_exec(shell, exec_path, node->args, CHILD) == -1)
		exit(FAILURE);	// bonne valeur
	exit(shell->exit);
}

static void	exec_parent(t_shell *shell, t_tree *node, char *exec_path, pid_t program)
{
	waitpid(program, &(shell->exit), 0);
	shell->exit /= 256;				// pourquoi ?
	dup2(shell->std[0], STDIN_FILENO);	// pour les redirections
	dup2(shell->std[1], STDOUT_FILENO);
	if (!shell->exit || !ft_strncmp(exec_path, "exit", 5))	// bon ?
		ft_exec(shell, exec_path, node->args, PARENT);	// ou le mettre ?
}

int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	char	*exec_path;
	pid_t	program;

	if (!(exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->args[0]));	// valeur de retour a confirmer
	if (manage_redirection(shell, node->dir) == FAILURE)
		return (FAILURE);	// a gerer avec errno
	if ((program = fork()) == -1)
		return (FAILURE);	// a gerer
	if (!program) // erreur a gerer si program = -1 ?
	{
		if (is_pipe / 2 < 1)	// if !PIPE_IN
			dup2(0, pipe_fd[1 - shell->last_pipe][0]);
		if (is_pipe % 2 != PIPE_OUT)
			dup2(1, pipe_fd[shell->last_pipe][1]);
		exec_child(shell, node, pipe_fd, exec_path);
	}
	else
	{
		close(pipe_fd[shell->last_pipe][1]);
		close(pipe_fd[1 - shell->last_pipe][0]);
		exec_parent(shell, node, exec_path, program);
	}
	ft_lstfd_close_clear(&shell->lst_fd);	// a mettre ici ?
	return (SUCCESS);								// valeur a confirmer
}


int	ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	pipe(pipe_fd[1 - shell->last_pipe]);	// a verifier
	
	// dup2(pipe_fd[shell->last_pipe][0], pipe_fd[1 - shell->last_pipe][0]);
	// dup2(pipe_fd[shell->last_pipe][1], pipe_fd[1 - shell->last_pipe][1]);
	
	shell->last_pipe = 1 - shell->last_pipe;

	launch_exec(shell, node, pipe_fd, is_pipe);
	
	return (SUCCESS);
}