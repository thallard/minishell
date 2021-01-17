/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/17 15:53:15 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			is_builtin(char *exec)
{
	if (!ft_strncmp(exec, "echo", 5) ||
		!ft_strncmp(exec, "cd", 3) ||
		!ft_strncmp(exec, "pwd", 4) ||
		!ft_strncmp(exec, "export", 7) ||
		!ft_strncmp(exec, "unset", 6) ||
		!ft_strncmp(exec, "env", 4) ||
		!ft_strncmp(exec, "exit", 5))
		return (1);
	return (0);
}

static int	read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2], int pipe_in)
{
	int	res;
	int	is_end;

	is_end = 0;
	if (!strncmp((*t_current)->args->args[0], "|", 2))
		pipe_in = PIPE_IN;
	*t_current = (*t_current)->right;
	if (!strncmp((*t_current)->args->args[0], ";", 2))
	{
		res = ft_exec_and_pipe(shell, (*t_current)->left, pipe_fd, pipe_in); // a traiter
		is_end = ((*t_current)->right != NULL);
	}
	else if (!strncmp((*t_current)->args->args[0], "|", 2))
	{
		if (pipe(pipe_fd[1 - shell->last_pipe]) == -1)
			print_error_and_exit(shell, "pipe", -1 * ENFILE); // possible exit status
		shell->last_pipe = 1 - shell->last_pipe;
		res = launch_exec(shell, (*t_current)->left, pipe_fd, PIPE_OUT + pipe_in);
// verif du fd entre les deux ?
		if ((is_end = ((*t_current)->right != NULL)))
			return (read_node(shell, t_current, pipe_fd, 0));
		return (PIPE_STDIN);						// a gerer ?
	}
	else
		res = ft_exec_and_pipe(shell, *t_current, pipe_fd, pipe_in);
	return (is_end);
}

int		read_tree(t_shell *shell)
{
	int		is_end;
	t_tree	*t_current;
	int pipe_fd[2][2];
	if (pipe(pipe_fd[0]) == -1 || pipe(pipe_fd[1]) == -1)
			print_error_and_exit(shell, "pipe", -1 * ENFILE); // possible exit status
	// pipe_fd[0][0] = -1;
	// pipe_fd[0][1] = -1;
	// pipe_fd[1][0] = -1;
	// pipe_fd[1][1] = -1;

	t_current = shell->root;
	is_end = (t_current->right != NULL);
	while (is_end)
		is_end = read_node(shell, &t_current, pipe_fd, 0);
	return (SUCCESS);
}
