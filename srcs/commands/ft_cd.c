/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:53:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 14:53:43 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	go_to_upper_folder(t_shell *shell)
{
	char	*current_path;
	char	*path_temp;
	char	*upper_path;
	int		indice;
	int		res;

	if (!(current_path = ft_calloc(1, 500)))
		ft_exit_failure(shell, F_MALLOC, current_path);
	upper_path = NULL;
	path_temp = current_path;
	getcwd(current_path, 1000);
	if (!current_path)
		return (ft_free_ptr(path_temp));
	indice = ft_strrfind(current_path, '/');
	if (indice > 0)
		upper_path = ft_substr(current_path, 0, indice);
	else
		upper_path = current_path;
	res = chdir(upper_path);
	if (current_path != upper_path)
		ft_free_ptr(upper_path);
	ft_free_ptr(current_path);
	if (res == -1)
		return (-1);
	return (SUCCESS);
}

static int	go_to_folder(t_shell *shell, char *folder)
{
	char	*current_path;
	char	*path_temp;
	char	*path;
	int		res;

	current_path = NULL;
	if (folder[0] == '/')
	{
		if (!(path = ft_strdup(folder)))
			return (-1);
	}
	else
	{
		if (!(current_path = ft_calloc(1, 500)))
			ft_exit_failure(shell, F_MALLOC, NULL);
		path_temp = current_path;
		if (!(getcwd(current_path, 1000)))
			return (ft_free_ptr(path_temp));
		else if (!(path = build_path(shell, current_path, folder)))
			return (-1);
	}
	res = chdir(path);
	ft_free_ptr(current_path);
	ft_free_ptr(path);
	return (get_correct_return(res));
}

static int	go_to_home(t_shell *shell)
{
	char	*path;
	int		res;

	path = NULL;
	if ((get_var_env(shell, "HOME", &path, 1) == -1) || !path)
		return (-1);
	res = chdir(path);
	return (get_correct_return(res));
}

static int	go_to_old_pwd(t_shell *shell)
{
	char	*path;
	int		res;

	path = NULL;
	if ((get_var_env(shell, "OLDPWD", &path, 1) == -1) || !path || !path[0])
	{
		print_oldpwd_error(shell, "cd");
		return (FAILURE);
	}
	res = chdir(path);
	ft_printf(1, "%s\n", path);
	return (get_correct_return(res));
}

int			ft_cd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;

	(void)tab_env;
	if (!exec_args[1] || !ft_strncmp(exec_args[1], "~", 2))
		res = go_to_home(shell);
	else if (!ft_strncmp(exec_args[1], "..", 3))
		res = go_to_upper_folder(shell);
	else if (!ft_strncmp(exec_args[1], "-", 2))
	{
		if ((res = go_to_old_pwd(shell)) == FAILURE)
			return (SUCCESS);
	}
	else
		res = go_to_folder(shell, exec_args[1]);
	if (res == -1)
		return (print_error(shell, exec_args[1], 1));
	maj_pwd_and_oldpwd(shell, exec_args);
	return (SUCCESS);
}
