/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/08 10:21:25 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*is_exec_in_path(char *exec, char *folder_path)
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
	if (get_var_env(shell, "PATH", &paths) <= 0 ||
		!(tab_paths = ft_split_minishell(paths, ':', shell)))
		return (NULL);
	i = 0;
	while (tab_paths[i])
	{
		if ((exec_path = is_exec_in_path(node->item, tab_paths[i])))
		{
			if (!add_lst_to_free(shell, exec_path))
				return (NULL);
			return (exec_path);
		}
		i++;
	}
	return (NULL);
}

char	**get_exec_args(t_shell *shell, char *exec, char *args, int is_pipe)
{
	char	**tab;
	char	*str_temp;
	char	*args_temp;

	(void)is_pipe;

	if (!(str_temp = ft_strjoin(exec, " ")))
		return (NULL);
	args_temp = ft_strjoin(str_temp, args);
	free(str_temp);
	if (!args_temp)
		return (NULL);
	// if (is_pipe == PIPE_IN)
	// {
	// 	str_temp = args_temp;
	// 	args_temp = ft_strjoin(args_temp, " temp/fd_temp"); // a modifier
	// 	free(str_temp);
	// 	if (!args_temp)
	// 		return (NULL);
	// }
	if (!(tab = ft_split_minishell(args_temp, ' ', shell)))
	{
		free(args_temp);
		return (NULL);
	}
	free(args_temp);
	return (tab);
}

int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	char	*exec_path;
	char	**exec_args;
	pid_t	program;
	int		status;

	// int		stdin_s;
	// int		stdout_s;

	// stdin_s = dup(0);
	// stdout_s = dup(1);
// ft_printf(1, "cmd = %s\npipe_out = %d\npipe_in = %d\n", node->item, is_pipe == PIPE_OUT, is_pipe == PIPE_IN);

	if (!(exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->item));	// valeur de retour a confirmer
	if (!node->left->item)
	{
		if (!(exec_args = ft_split_minishell(node->item, ' ', shell)))
			return (FAILURE);
	}
	else if (!(exec_args = get_exec_args(shell, node->item, node->left->item, is_pipe)))
		return (FAILURE);

// dprintf(1, "pipe_in = %d\n\n", is_pipe);
// dprintf(1, "shell->last_pipe = %d\n", shell->last_pipe);
// dprintf(1, "main program pid = %d\n", getpid());

	if ((program = fork()) == -1)
		return (FAILURE);	// a gerer

// dprintf(1, "program = %d\n\n", program);

	if (!program) // erreur a gerer si program = -1 ?
	{
		if (is_pipe / 2 != 1)
		{
// dprintf(1, "--NOT PIPE_IN %s\n", node->item);
			// close(pipe_fd[1 - shell->last_pipe][0]);
			// pipe_fd[1 - shell->last_pipe][0] = shell->std[0];
			dup2(shell->std[0], pipe_fd[1 - shell->last_pipe][0]);
		}
		if (is_pipe % 2 != PIPE_OUT)
		{
// dprintf(1, "--NOT PIPE_OUT %s\n", node->item);
			// close(pipe_fd[shell->last_pipe][1]);
			// pipe_fd[shell->last_pipe][1] = shell->std[1];
			dup2(shell->std[1], pipe_fd[shell->last_pipe][1]);
		}
		
		dup2(pipe_fd[shell->last_pipe][1], 1);
		dup2(pipe_fd[1 - shell->last_pipe][0], 0);
		
		close(pipe_fd[shell->last_pipe][0]);
		close(pipe_fd[1 - shell->last_pipe][1]);

// dprintf(1, "--PIPE %s\n", node->item);
		execve(exec_path, exec_args, shell->tab_env);	// retour a checker
		exit(0);
	}
	else
	{		
		close(pipe_fd[shell->last_pipe][1]);
		close(pipe_fd[1 - shell->last_pipe][0]);
		wait(&status);
		// dup2(shell->std[0], 0);
		// dup2(shell->std[1], 1);

// dprintf(1, "--> %s\n", node->item);
		
	}

	return (SUCCESS);								// valeur a confirmer
}

int	ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	pipe(pipe_fd[1 - shell->last_pipe]);
	dup2(pipe_fd[shell->last_pipe][0], pipe_fd[1 - shell->last_pipe][0]);
	dup2(pipe_fd[shell->last_pipe][1], pipe_fd[1 - shell->last_pipe][1]);
	shell->last_pipe = 1 - shell->last_pipe;
	ft_exec(shell, node, pipe_fd, is_pipe);
	return (SUCCESS);
}

int		read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2], int pipe_in)
{
	int	res;
	int	is_end;

	is_end = 0;
	if (!strncmp((*t_current)->item, "|", 2))
		pipe_in += PIPE_IN;
		
	*t_current = (*t_current)->right;
	
	if (!strncmp((*t_current)->item, ";", 2))
	{
		res = ft_exec_and_pipe(shell, (*t_current)->left, pipe_fd, pipe_in);	// a traiter
		is_end = ((*t_current)->right != NULL);
	}
	else if (!strncmp((*t_current)->item, "|", 2))
	{
		if (pipe(pipe_fd[1 - shell->last_pipe]) == -1)
			return (FAILURE);
		shell->last_pipe = 1 - shell->last_pipe;		
		res = ft_exec(shell, (*t_current)->left, pipe_fd, PIPE_OUT + pipe_in);	// a traiter
		// verif du fd entre les deux ?
		if ((is_end = ((*t_current)->right != NULL)))
			return (read_node(shell, t_current, pipe_fd, pipe_in));
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
		// t_current = t_current->right;
		is_end = read_node(shell, &t_current, pipe_fd, 0);
		// close(pipe_fd[0]);
        // close(pipe_fd[1]);
		// pipe_fd[0] = -1;
		// pipe_fd[1] = -1;	
	}
	return (SUCCESS);
}
