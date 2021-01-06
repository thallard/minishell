#include "../../includes/minishell.h"

int		ft_cmd_not_found(t_shell *shell, char *exec)
{
	(void)shell;					// utilite de shell ?
	ft_printf("bash: %s: command not found\n", exec);	// message a ajuster
	return (SUCCESS);				// valeur a confirmer
}

char	*find_car_path(t_env *begin)
{
	while (begin)
	{		
		if (!ft_strncmp(begin->name, "PATH", 5))
			return (begin->content);
		begin = begin->next;
	}
	return (NULL);
}

char	*is_exec_in_path(char *exec, char *folder_path)
{
	char	*full_path;
	char	*path_temp;
	struct stat sb;

	if (!(path_temp = ft_strjoin(folder_path, "/")))
		return (NULL);
	if (!(full_path = ft_strjoin(path_temp, exec)))
	{
		free(path_temp);
		return (NULL);
	}
	free(path_temp);

dprintf(1, "path = |%s|\n", full_path); ///////////////////

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

	if (!(paths = find_car_path(shell->var_env)) ||
		!(tab_paths = ft_split(paths, ':')) ||
		!add_lst_to_free(shell, tab_paths))
		return (NULL);
	i = 0;
	while (tab_paths[i])
	{
		if ((exec_path = is_exec_in_path(node->item, tab_paths[i])))
		{
			if (!add_lst_to_free(shell, exec_path))
				return (NULL);
			return(exec_path);
		}
		i++;
	}
	return (NULL);
}

char	**get_exec_args(char *exec, char *args)
{
	char 	**tab;
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
	if (!(tab = ft_split(args_temp, ' ')))
	{
		free(args_temp);
		return (NULL);
	}
	free(args_temp);
	return (tab);
}

int	launch_exec(t_shell *shell, t_tree *node)
{
	char	*exec_path;
	char	**exec_args;
	pid_t	program;

	if (!(exec_path = find_exec(shell, node)))
		return (ft_cmd_not_found(shell, node->item));	// valeur de retour a confirmer
	if (!node->left->item)
	{
		if (!(exec_args = ft_split(node->item, ' ')))
			return (FAILURE);
	}
	else if (!(exec_args = get_exec_args(node->item, node->left->item)) ||
		!add_lst_to_free(shell, exec_args))
		return (FAILURE);
	if (!(program = fork()))
		execve(exec_path, exec_args, shell->tab_env);	// retour a checker
	return (SUCCESS);								// valeur a confirmer
}

int	ft_exec(t_shell *shell, t_tree *node)
{
	if (!ft_strncmp(node->item, "echo", 5))
		return (ft_echo(shell, node));
	if (!ft_strncmp(node->item, "cd", 3))
		return (ft_cd(shell, node));
	if (!ft_strncmp(node->item, "pwd", 4))
		return (ft_pwd(shell));
	if (!ft_strncmp(node->item, "export", 7))
	 	return (ft_export(shell, node));
	if (!ft_strncmp(node->item, "unset", 6))
		return (ft_unset(shell, node));
	if (!ft_strncmp(node->item, "env", 4))
		return (ft_env(shell, node));
	// if (!ft_strncmp(node->item, "exit", 5))
	// 	return (ft_exit(shell, node));
	return (launch_exec(shell, node));
}

int	read_tree(t_shell *shell)
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
