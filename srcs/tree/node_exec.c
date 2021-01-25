/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:54:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 14:52:00 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*is_exec_in_path(t_shell *shell, char *exec, char *folder_path)
{
	char		*full_path;
	char		*path_temp;
	struct stat sb;

	if (!(path_temp = ft_strjoin(folder_path, "/")))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(full_path = ft_strjoin_free(path_temp, exec, 1, 0)))
		ft_exit_failure(shell, F_MALLOC, path_temp);
	if (!stat(full_path, &sb))
		return (full_path);
	free(full_path);
	return (NULL);
}

static int	is_exec_path(char *exec)
{
	struct stat sb;
	int			fd;

	if (!ft_strncmp(exec, "~", 2))
		return (-1);
	fd = open(exec, O_DIRECTORY, 0666);
	if (fd != -1)
	{
		close(fd);
		return (-1);
	}
	if (!stat(exec, &sb) && ft_memchr(exec, '/', ft_strlen(exec)))
		return (1);
	if (ft_memchr(exec, '/', ft_strlen(exec)))
		return (-2);
	return (0);
}

static int	find_exec(t_shell *shell, t_tree *node, char **exec_path)
{
	char	*paths;
	char	**tab_paths;
	int		i;

	paths = NULL;
	if ((i = is_builtin(node->args->args[0])) > 0 ||
		(i = is_exec_path(node->args->args[0])) != 0)
		return (i);
	if (get_var_env(shell, "PATH", &paths, 1) <= 0)
		ft_exit_failure(shell, NO_EXEC_PATH, NULL);
	if (!(tab_paths = ft_split_exec_paths(paths, ':', shell)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = -1;
	while (tab_paths[++i])
	{
		if ((*exec_path = is_exec_in_path(shell, node->args->args[0],
										tab_paths[i])))
		{
			if (!add_lst_to_free(shell, *exec_path))
				ft_exit_failure(shell, F_MALLOC, *exec_path);
			return (2);
		}
	}
	return (0);
}

static void	trim_first_empty_args(t_tree *node)
{
	char	**exec_args;
	int		i;

	exec_args = node->args->args;
	while (exec_args[0] && exec_args[0][0] == 0)
	{
		i = -1;
		while (exec_args[++i])
			exec_args[i] = exec_args[i + 1];
	}
}

int			launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2],
						int is_pipe)
{
	int	is_exec;

	ft_match_var_env(shell, node);
	trim_first_empty_args(node);
	if (!node->args->args[0])
	{
		manage_redirection(shell, node->dir);
		reset_stds(shell);
		return (SUCCESS);
	}
	if (!(is_exec = find_exec(shell, node, &node->exec_path)))
		return (ft_cmd_not_found(shell, node->args->args[0], node));
	if (is_exec == 1)
		node->exec_path = node->args->args[0];
	if (is_exec == -1)
		return (print_dir_error(shell, node->args->args[0]));
	if (is_exec == -2)
		return (print_dir_file_error(shell, node->args->args[0]));
	if (is_builtin(node->args->args[0]))
		exec_builtin(shell, node, pipe_fd, is_pipe);
	else
		exec_execve(shell, node, pipe_fd, is_pipe);
	change_last_arg_env(shell, node);
	ft_lstfd_close_clear(&shell->lst_fd);
	return (SUCCESS);
}
