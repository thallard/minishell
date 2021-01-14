/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 15:08:51 by thallard          #+#    #+#             */
/*   Updated: 2021/01/03 15:08:51 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_correct_return(int res)
{
	if (res == -1)
		return (-1);
	return (SUCCESS);
}

static char	*build_path(char *current_path, char *folder)
{
char	*path_temp;
char	*path;

	if (!(path = ft_strjoin(current_path, "/")))
		return (NULL);
	path_temp = path;
	path = ft_strjoin(path, folder);
	free(path_temp);
	if (!path)
		return (NULL);
	path_temp = path;
	path = ft_strtrim(path, "\n");
	free(path_temp);
	return (path);
}

static int	go_to_upper_folder(void)
{
	char	*current_path;
	char	*path_temp;
	char	*upper_path;
	int		indice;
	int		res;

	if (!(current_path = ft_calloc(1, 500)))
		return (-1);
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

static int	go_to_folder(char *folder)
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
			return (-1);
		path_temp = current_path;
		if (!(getcwd(current_path, 1000)))
			return (ft_free_ptr(path_temp));
		else if (!(path = build_path(current_path, folder)))
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
	if ((get_var_env(shell, "HOME", &path) == -1) || !path)
		return (-1);
	res = chdir(path);
	return (get_correct_return(res));
}

static int	go_to_old_pwd(t_shell *shell)
{
	char	*path;
	int		res;
	t_env	*pwd;
	t_env	*old_pwd;

	path = NULL;
	if ((get_var_env(shell, "OLDPWD", &path) == -1) || !path)
		return (FAILURE);
	res = chdir(path);
	if (!(pwd = ft_get_var_env(shell, "PWD")) ||
		!(old_pwd = ft_get_var_env(shell, "OLDPWD")))
		return (FAILURE);
	ft_swap_env_content(pwd, old_pwd);
	ft_printf(1, "%s\n", pwd->content);
	return (get_correct_return(res));
}

int		ft_cd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;
	char	*old_path;
	char	*current_path;

// dprintf(1, "cd0\n");

(void)tab_env;
	if (!exec_args[1] || !ft_strncmp(exec_args[1], "~", 2))
		res = go_to_home(shell);
	else if (!ft_strncmp(exec_args[1], "..", 3))
		res = go_to_upper_folder();
	else if (!ft_strncmp(exec_args[1], "-", 2))
		// res = go_to_old_pwd(shell);
		return (go_to_old_pwd(shell));
	else
		res = go_to_folder(exec_args[1]);
	if (res == -1)		// PARENT ou CHILD
		return (print_cd_error(shell, exec_args[1]));

// dprintf(1, "cd1\n");

	get_var_env(shell, "PWD", &old_path);
	if (!(old_path = ft_strdup(old_path)) || !add_lst_to_free(shell, old_path))
		return (FAILURE);
	if (!(current_path = ft_calloc(1, 500)) ||
		!add_lst_to_free(shell, current_path))
		return (FAILURE);

// dprintf(1, "cd2\n");

	getcwd(current_path, 1000);	// a proteger ?


	replace_env_content(shell, "OLDPWD", old_path); // pb possible avec lst des ptrs
	replace_env_content(shell, "PWD", current_path);
	return (SUCCESS);
}
