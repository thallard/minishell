/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 09:23:42 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2],
							int is_pipe)
{
	if ((pipe(pipe_fd[1 - shell->last_pipe]) == -1))
		return (print_error(shell, "pipe", 1));
	shell->last_pipe = 1 - shell->last_pipe;
	launch_exec(shell, node, pipe_fd, is_pipe);
	return (SUCCESS);
}

int			is_builtin(char *exec)
{
	if (!ft_strncmp_lower(exec, "echo", 5) ||
		!ft_strncmp_lower(exec, "cd", 3) ||
		!ft_strncmp_lower(exec, "pwd", 4) ||
		!ft_strncmp(exec, "export", 7) ||
		!ft_strncmp(exec, "unset", 6) ||
		!ft_strncmp_lower(exec, "env", 4) ||
		!ft_strncmp(exec, "exit", 5))
		return (1);
	return (0);
}

static int	read_sep_pointv(t_shell *shell, t_tree **t_current,
							int pipe_fd[2][2], int pipe_in)
{
	if ((*t_current)->left)
		ft_exec_and_pipe(shell, (*t_current)->left, pipe_fd, pipe_in);
	return (((*t_current)->right != NULL));
}

static int	read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2],
						int pipe_in)
{
	int	is_end;

	if (!(is_end = 0) && !strncmp((*t_current)->args->args[0], "|", 2))
		pipe_in = PIPE_IN;
	*t_current = (*t_current)->right;
	if (!(*t_current) && (shell->exit = 2))
		return (is_end);
	if (!(*t_current)->args->args[0] &&
		ft_exec_and_pipe(shell, *t_current, pipe_fd, pipe_in) == SUCCESS)
		return (is_end);
	if (!strncmp((*t_current)->args->args[0], ";", 2))
		is_end = read_sep_pointv(shell, t_current, pipe_fd, pipe_in);
	else if (!ft_strncmp((*t_current)->args->args[0], "|", 2))
	{
		if (pipe(pipe_fd[1 - shell->last_pipe]) == -1)
			return (print_error(shell, "pipe", 1));
		shell->last_pipe = 1 - shell->last_pipe;
		launch_exec(shell, (*t_current)->left, pipe_fd, PIPE_OUT + pipe_in);
		if ((is_end = ((*t_current)->right != NULL)))
			return (read_node(shell, t_current, pipe_fd, 0));
		return (PIPE_STDIN);
	}
	else
		ft_exec_and_pipe(shell, *t_current, pipe_fd, pipe_in);
	return (is_end);
}

int			read_tree(t_shell *shell)
{
	int		is_end;
	t_tree	*t_current;
	int		pipe_fd[2][2];

	if (pipe(pipe_fd[0]) == -1 || pipe(pipe_fd[1]) == -1)
		return (print_error(shell, "pipe", 1));
	t_current = shell->root;
	is_end = (t_current->right != NULL);
	while (is_end)
		is_end = read_node(shell, &t_current, pipe_fd, 0);
	return (SUCCESS);
}
