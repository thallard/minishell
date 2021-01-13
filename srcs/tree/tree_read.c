/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 12:01:12 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static int	is_builtin(char *exec)
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

static char	*is_exec_in_path(char *exec, char *folder_path)
{
	char		*full_path;
	char		*path_temp;
	struct stat sb;

	if (!(path_temp = ft_strjoin(folder_path, "/")))
		return (NULL);
	if (!(full_path = ft_strjoin(path_temp, exec)))
	{
		free(path_temp);
		return (NULL);
	}
	free(path_temp);
	if (!stat(full_path, &sb))
		return (full_path);
	free(full_path);
	return (NULL);
}

char	*find_exec(t_shell *shell, t_tree *node)
{
	char	*paths;
	char	**tab_paths;
	char	*exec_path;
	int		i;

	paths = NULL;
	
	if (is_builtin(node->args[0]))
		return (node->args[0]);
	if (get_var_env(shell, "PATH", &paths) <= 0 ||
		!(tab_paths = ft_split_minishell_args(paths, ':', shell)))
		return (NULL);
	i = 0;
	while (tab_paths[i])
	{
		if ((exec_path = is_exec_in_path(node->args[0], tab_paths[i])))
		{
			if (!add_lst_to_free(shell, exec_path))
				return (NULL);
			return (exec_path);
		}
		i++;
	}
	return (NULL);
}

static int	read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2], int pipe_in)
{
	int	res;
	int	is_end;

	is_end = 0;
	if (!strncmp((*t_current)->args[0], "|", 2))
		pipe_in = PIPE_IN;
		
	*t_current = (*t_current)->right;
	
	if (!strncmp((*t_current)->args[0], ";", 2))
	{
		res = ft_exec_and_pipe(shell, (*t_current)->left, pipe_fd, pipe_in); // a traiter
		is_end = ((*t_current)->right != NULL);
	}
	else if (!strncmp((*t_current)->args[0], "|", 2))
	{
		if (pipe(pipe_fd[1 - shell->last_pipe]) == -1)
			return (FAILURE);
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
	pipe_fd[0][0] = -1;
	pipe_fd[0][1] = -1;
	pipe_fd[1][0] = -1;
	pipe_fd[1][1] = -1;

	t_current = shell->root;
	is_end = (t_current->right != NULL);
	while (is_end)
	{
		is_end = read_node(shell, &t_current, pipe_fd, 0);
	}
	return (SUCCESS);
}
