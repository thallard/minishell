/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:54:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/14 10:37:32 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	if (!(node->exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->args[0]));	// valeur de retour a confirmer
	if (manage_redirection(shell, node->dir) == FAILURE)
		return (FAILURE);	// a gerer avec errno

	if (is_builtin(node->args[0]))
		exec_builtin(shell, node, pipe_fd, is_pipe);
	else if (exec_execve(shell, node, pipe_fd, is_pipe) == FAILURE)
		return (FAILURE);

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
