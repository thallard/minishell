/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:39:14 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/06 13:49:12 by bjacob           ###   ########lyon.fr   */
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

char	**get_exec_args(t_shell *shell, char *exec, char *args)
{
	char	**tab;
	char	*str_temp;
	char	*args_temp;

	if (!(str_temp = ft_strjoin(exec, " ")))
		return (NULL);
	if (!(args_temp = ft_strjoin(str_temp, args)))
	{
		free(str_temp);
		return (NULL);
	}
	free(str_temp);
	if (!(tab = ft_split_minishell(args_temp, ' ', shell)))
	{
		free(args_temp);
		return (NULL);
	}
	free(args_temp);
	return (tab);
}

int		launch_exec(t_shell *shell, t_tree *node)
{
	char	*exec_path;
	char	**exec_args;
	pid_t	program;
	int		status;

	if (!(exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->item));	// valeur de retour a confirmer
	if (!node->left->item)
	{
		if (!(exec_args = ft_split_minishell(node->item, ' ', shell)))
			return (FAILURE);
	}
	else if (!(exec_args = get_exec_args(shell, node->item, node->left->item))
			|| !add_lst_to_free(shell, exec_args))
		return (FAILURE);
	if (!(program = fork())) // erreur a gerer si program = -1 ?
		execve(exec_path, exec_args, shell->tab_env);	// retour a checker
	else
		wait(&status);
	
	return (SUCCESS);								// valeur a confirmer
}

int		read_tree(t_shell *shell)
{
	int		is_end;
	t_tree	*t_current;
	int		res;

	t_current = shell->root;
	is_end = (t_current->right != NULL);
	while (is_end)
	{
		t_current = t_current->right;
		if (!strncmp(t_current->item, ";", 2))	//	a voir pour |
		{
			res = ft_exec(shell, t_current->left);	// a traiter
			is_end = (t_current->right != NULL);
		}
		else
		{
			res = ft_exec(shell, t_current);
			is_end = 0;
		}
	}
	return (SUCCESS);
}
