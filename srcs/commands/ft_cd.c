/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 14:53:40 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/28 12:37:59 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	go_to_upper_folder(t_shell *shell)
{
	char	*current_path;
	char	*upper_path;
	int		indice;
	int		res;

	upper_path = NULL;
	current_path = NULL;
	if (!(current_path = getcwd(NULL, 0)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	indice = ft_strrfind(current_path, '/');
	if (!indice)
		indice = 1;
	if (!(upper_path = ft_substr(current_path, 0, indice)))
		ft_exit_failure(shell, F_MALLOC, current_path);
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
	char	*path;
	int		res;

	path = NULL;
	current_path = NULL;
	if (folder[0] == '/')
	{
		if (!(path = ft_strdup(folder)))
			return (-1);
	}
	else
	{
		if (!(current_path = getcwd(NULL, 0)) ||
			!add_lst_to_free(shell, current_path))
			ft_exit_failure(shell, F_MALLOC, current_path);
		else
			path = build_path(shell, current_path, folder);
	}
	res = chdir(path);
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
