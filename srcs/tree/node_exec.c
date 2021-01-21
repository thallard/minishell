/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 11:54:41 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/21 15:23:00 by bjacob           ###   ########lyon.fr   */
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

	if (!stat(exec, &sb) && ft_memchr(exec, '/', ft_strlen(exec)))
		return (1);
	return (0);
}

static char	*find_exec(t_shell *shell, t_tree *node)
{
	char	*paths;
	char	**tab_paths;
	char	*exec_path;
	int		i;

	paths = NULL;
	if (is_builtin(node->args->args[0]) ||
		is_exec_path(node->args->args[0]))
		return (node->args->args[0]);
	if (get_var_env(shell, "PATH", &paths, 1) <= 0)
		ft_exit_failure(shell, NO_EXEC_PATH, NULL);
	if(!(tab_paths = ft_split_exec_paths(paths, ':', shell)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	i = -1;
	while (tab_paths[++i])
	{
		if ((exec_path = is_exec_in_path(shell, node->args->args[0],
										tab_paths[i])))
		{
			if (!add_lst_to_free(shell, exec_path))
				ft_exit_failure(shell, F_MALLOC, exec_path);
			return (exec_path);
		}
	}
	return (NULL);
}

int			launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{	

// ft_print_tab_char(node->args->args);
// ft_print_node(node);

	ft_match_var_env(shell, node);
	
	if (!node->args->args[0])
	{
		manage_redirection(shell, node->dir); ////////////////
		reset_stds(shell);
		return (SUCCESS);
	}

	if (!(node->exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->args->args[0], node));	// valeur de retour a confirmer
	
	if (is_builtin(node->args->args[0]))
		exec_builtin(shell, node, pipe_fd, is_pipe);
	else
		exec_execve(shell, node, pipe_fd, is_pipe);

	change_last_arg_env(shell, node);
	
	ft_lstfd_close_clear(&shell->lst_fd);	// a mettre ici ?

// verifie-t-on le shell->exit du child apres exec_execve ?

	return (SUCCESS);								// valeur a confirmer
}

int			ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	if ((pipe(pipe_fd[1 - shell->last_pipe]) == -1))
		print_error_and_exit(shell, "pipe", -1 * ENFILE); // possible exit status

	shell->last_pipe = 1 - shell->last_pipe;

	launch_exec(shell, node, pipe_fd, is_pipe);
	
	return (SUCCESS);
}
