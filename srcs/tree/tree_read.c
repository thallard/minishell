/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/12 19:05:35 by thallard         ###   ########lyon.fr   */
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

int		is_builtin(char *exec)
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

	// ft_print_tab_dir(exec_dir);
	
	i = -1;
	if (!exec_dir[0]->file)
		return (SUCCESS);
	while (exec_dir[++i]->file)
	{
		if (exec_dir[i]->dir >= 0)
		{
// dprintf(1, "redir > - %s\n", exec_dir[i]->file);

			if ((exec_dir[i]->dir == 1 && (fd = open(exec_dir[i]->file, O_TRUNC | O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1) ||
				(exec_dir[i]->dir == 2 && (fd = open(exec_dir[i]->file, O_CREAT | O_WRONLY | O_RDONLY, 0666)) == -1))
				return (FAILURE);				
			dup2(fd, STDOUT_FILENO);
		}
		if (exec_dir[i]->dir == -1)
		{
// dprintf(1, "redir < - %s\n", exec_dir[i]->file);

			if ((fd = open(exec_dir[i]->file, O_RDONLY, 0666)) == -1)
				return (FAILURE);	// a gerer avec errno				
			dup2(fd, STDIN_FILENO);
		}
	}
	return (SUCCESS);
}

int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	char	*exec_path;
	// char	**exec_args;
	// t_dir	**exec_dir;
	pid_t	program;
	int		status;

// dprintf(1, "\n\n");
	// exec_dir = ft_split_redirection(shell, node->left->item);
	if (!(exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->args[0]));	// valeur de retour a confirmer

	// if (!node->left->args[0])
	// {
	// 	if (!(exec_args = ft_split_minishell_args(node->args[0], ' ', shell)) ||
	// 		!(exec_dir = ft_split_minishell_dir(node->left->args[0], ' ', shell)))
	// 		return (FAILURE);
	// }
	// else if (!(exec_args = get_exec_args(shell, node->args[0], node->left->args[0], is_pipe)) ||
	// 		!(exec_dir = ft_split_minishell_dir(node->left->args[0], ' ', shell)))
	// 	return (FAILURE);

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



		dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO);
		dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO);
		
		close(pipe_fd[shell->last_pipe][0]);
		close(pipe_fd[1 - shell->last_pipe][1]);

// dprintf(shell->std[1], "begin fils - %s\n", exec_path);

		ft_exec(shell, exec_path, node->args, CHILD);

// dprintf(shell->std[1], "end fils - %s\n", exec_path);

		// execve(exec_path, exec_args, shell->tab_env);	// retour a checker
		exit(0);
	}
	else
	{
		close(pipe_fd[shell->last_pipe][1]);
		close(pipe_fd[1 - shell->last_pipe][0]);

		wait(&status);
		
		dup2(shell->std[0], STDIN_FILENO);	// pour les redirections
		dup2(shell->std[1], STDOUT_FILENO);

		ft_exec(shell, exec_path, node->args, PARENT);	// ou le mettre ?
	}
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

int		read_node(t_shell *shell, t_tree **t_current, int pipe_fd[2][2], int pipe_in)
{
	int	res;
	int	is_end;

	is_end = 0;
	if (!strncmp((*t_current)->args[0], "|", 2))
		pipe_in = PIPE_IN; // ou += ?
		
	*t_current = (*t_current)->right;
	
	if (!strncmp((*t_current)->args[0], ";", 2))
	{
		res = ft_exec_and_pipe(shell, (*t_current)->left, pipe_fd, pipe_in);	// a traiter
		is_end = ((*t_current)->right != NULL);
	}
	else if (!strncmp((*t_current)->args[0], "|", 2))
	{
		if (pipe(pipe_fd[1 - shell->last_pipe]) == -1)
			return (FAILURE);
		shell->last_pipe = 1 - shell->last_pipe;
		res = launch_exec(shell, (*t_current)->left, pipe_fd, PIPE_OUT + pipe_in);
		// res = ft_exec(shell, (*t_current)->left, pipe_fd, PIPE_OUT + pipe_in);	// a traiter
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



/*
int		launch_exec(t_shell *shell, t_tree *node, int pipe_fd[2][2], int is_pipe)
{
	char	*exec_path;
	char	**exec_args;
	t_dir	**exec_dir;
	pid_t	program;
	int		status;

// dprintf(1, "\n\n");

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

	if (manage_redirection(shell, exec_dir) == FAILURE)
		return (FAILURE);	// a gerer avec errno

	if (is_pipe / 2 < 1)	// if !PIPE_IN
	{
dprintf(1, "not pipe IN - %s\n", exec_path);
		dup2(shell->std[0], pipe_fd[1 - shell->last_pipe][0]);
	}
	if (is_pipe % 2 != PIPE_OUT)
	{
dprintf(1, "not pipe OUT - %s\n", exec_path);
		dup2(shell->std[1], pipe_fd[shell->last_pipe][1]);
	}

	dup2(pipe_fd[shell->last_pipe][1], STDOUT_FILENO);
	dup2(pipe_fd[1 - shell->last_pipe][0], STDIN_FILENO);

	close(pipe_fd[shell->last_pipe][0]);
	close(pipe_fd[1 - shell->last_pipe][1]);


// dprintf(1, "test STDOUT - %s\n", exec_path);
	if ((program = fork()) == -1)
		return (FAILURE);	// a gerer

	if (!program) // erreur a gerer si program = -1 ?
	{

dprintf(shell->std[1], "begin fils - %s\n", exec_path);

		ft_exec(shell, exec_path, exec_args);
		// execve(exec_path, exec_args, shell->tab_env);	// retour a checker

// dup2(shell->std[0], STDIN_FILENO);	// pour les redirections
		// dup2(shell->std[1], STDOUT_FILENO);
// dprintf(STDOUT_FILENO, "end fils - %s\n", exec_path);
// dprintf(shell->std[1], "end fils - %s\n", exec_path);

		
		exit(shell->exit);	// pas indispensable ?
	}
	else
	{
		// close(pipe_fd[shell->last_pipe][1]);
		// close(pipe_fd[1 - shell->last_pipe][0]);

		wait(&status);
		
		dup2(shell->std[0], STDIN_FILENO);	// pour les redirections
		dup2(shell->std[1], STDOUT_FILENO);

		if (!ft_strncmp(exec_path, "exit", 5))
			exit(shell->exit);

dprintf(shell->std[1], "end parent - %s\n\n", exec_path);


	}
	return (SUCCESS);								// valeur a confirmer
}
*/