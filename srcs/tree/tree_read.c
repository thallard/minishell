/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/11 16:06:59 by bjacob           ###   ########lyon.fr   */
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
		!(tab_paths = ft_split_minishell_args(paths, ':', shell)))
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

	if (!(tab = ft_split_minishell_args(args_temp, ' ', shell)))
	{
		free(args_temp);
		return (NULL);
	}
	free(args_temp);
	return (tab);
}

int		manage_redirection(t_shell *shell, t_dir **exec_dir)
{
	int i;
	int	fd;

	(void)shell;	// exit a gerer dans cette fonction ?
	i = -1;
	while (exec_dir[++i]->file)
	{
		if (exec_dir[i]->dir >= 0)
		{
			if ((exec_dir[i]->dir == 1 && (fd = open(exec_dir[i]->file, O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1) ||
				(exec_dir[i]->dir == 2 && (fd = open(exec_dir[i]->file, O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1))
				return (FAILURE);

dprintf(1, "pppp2\n");
				
			dup2(fd, STDOUT_FILENO);
		}
		if (exec_dir[i]->dir == -1)
		{
			if ((fd = open(exec_dir[i]->file, O_RDONLY, 0666)) == -1)
				return (FAILURE);	// a gerer avec errno

dprintf(1, "pppp3\n");
				
			dup2(fd, STDIN_FILENO);
		}
	}
	return (SUCCESS);
}

int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	char	*exec_path;
	char	**exec_args;
	t_dir	**exec_dir;
	pid_t	program;
	int		status;

	if (!(exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->item));	// valeur de retour a confirmer

	if (!node->left->item)
	{
		if (!(exec_args = ft_split_minishell_args(node->item, ' ', shell)) ||
			!(exec_dir = ft_split_minishell_dir(node->left->item, ' ', shell)))
			return (FAILURE);
	}
	else if (!(exec_args = get_exec_args(shell, node->item, node->left->item, is_pipe)) ||
			!(exec_dir = ft_split_minishell_dir(node->left->item, ' ', shell)))
		return (FAILURE);



///////////////////////
// int k = -1;
// dprintf(1, "\nPRINT EXEC_ARGS\n");
// while (exec_args[++k])
// 	dprintf(1, "tab[%d] = |%s|\n", k, exec_args[k]);
// dprintf(1, "tab[%d] = |%s|\n\n", k, exec_args[k]);
// //////////////////////

// 	///////////////////////
// k = -1;
// dprintf(1, "PRINT EXEC_DIR\n");
// while (exec_dir[++k]->file)
// 	dprintf(1, "tab[%d] = |%s|, %d\n", k, exec_dir[k]->file, exec_dir[k]->dir);
// dprintf(1, "tab[%d] = |%s|, %d\n\n", k, exec_dir[k]->file, exec_dir[k]->dir);
////////////////////

	if (manage_redirection(shell, exec_dir) == FAILURE)
		return (FAILURE);	// a gerer avec errno


dprintf(1, "is_pipe = %d, node = %s\n", is_pipe, node->item);

	if ((program = fork()) == -1)
		return (FAILURE);	// a gerer

	if (!program) // erreur a gerer si program = -1 ?
	{
		if (is_pipe / 2 < 1)	// if !PIPE_IN
			dup2(0, pipe_fd[1 - shell->last_pipe][0]);
			// dup2(shell->std[0], pipe_fd[1 - shell->last_pipe][0]);
		if (is_pipe % 2 != PIPE_OUT)
			dup2(1, pipe_fd[shell->last_pipe][1]);
			// dup2(shell->std[1], pipe_fd[shell->last_pipe][1]);

// dprintf(1, "fils___ is_pipe = %d, node = %s\n", is_pipe, node->item);


		dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO);
		dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO);
		
		close(pipe_fd[shell->last_pipe][0]);
		close(pipe_fd[1 - shell->last_pipe][1]);

		// close(pipe_fd[shell->last_pipe][1]);
		// close(pipe_fd[1 - shell->last_pipe][0]);

// dprintf(1, "p0 %s\n", node->item);
		execve(exec_path, exec_args, shell->tab_env);	// retour a checker
// dprintf(1, "p1\n");
		exit(0);
	}
	else
	{
		close(pipe_fd[shell->last_pipe][1]);
		close(pipe_fd[1 - shell->last_pipe][0]);

		// close(pipe_fd[shell->last_pipe][0]);
		// close(pipe_fd[1 - shell->last_pipe][1]);
// dprintf(1, "p5\n");
		wait(&status);
		dup2(shell->std[0], STDIN_FILENO);
		dup2(shell->std[1], STDOUT_FILENO);
	}
	return (SUCCESS);								// valeur a confirmer
}

int	ft_exec_and_pipe(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	pipe(pipe_fd[1 - shell->last_pipe]);
	// dup2(pipe_fd[shell->last_pipe][0], pipe_fd[1 - shell->last_pipe][0]);
	// dup2(pipe_fd[shell->last_pipe][1], pipe_fd[1 - shell->last_pipe][1]);
	
	shell->last_pipe = 1 - shell->last_pipe;

// pwd | cat -e | grep bjacob

// dprintf(1, "ft_exec and pipe, is_pipe = %d, node = %s\n", is_pipe, node->item);
	
	ft_exec(shell, node, pipe_fd, is_pipe);
	return (SUCCESS);
}

int		read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2], int pipe_in)
{
	int	res;
	int	is_end;

	is_end = 0;
	if (!strncmp((*t_current)->item, "|", 2))
		pipe_in = PIPE_IN; // ou += ?
		
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
		is_end = read_node(shell, &t_current, pipe_fd, 0);
	}
	return (SUCCESS);
}
