/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:49:53 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/22 14:12:28 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*build_path(t_shell *shell, char *current_path, char *folder)
{
	char	*path_temp;
	char	*path;

	if (!(path = ft_strjoin(current_path, "/")))
		ft_exit_failure(shell, F_MALLOC, NULL);
	if (!(path = ft_strjoin_free(path, folder, 1, 0)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	path_temp = path;
	if (!(path = ft_strtrim(path, "\n")))
		ft_exit_failure(shell, F_MALLOC, path_temp);
	free(path_temp);
	return (path);
}

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
	// t_env	*pwd;
	// t_env	*old_pwd;

	path = NULL;
	if ((get_var_env(shell, "OLDPWD", &path, 1) == -1) || !path || !path[0])
	{
		print_oldpwd_error(shell, "cd");
		return (FAILURE);
	}
	res = chdir(path);
	// if (!(pwd = ft_get_var_env(shell, "PWD")) ||
	// if (!(old_pwd = ft_get_var_env(shell, "OLDPWD")))
		// return (FAILURE);			// a voir comment on le gere
	// ft_swap_env_content(pwd, old_pwd);
	// ft_printf(1, "%s\n", pwd->content);
	ft_printf(1, "%s\n", path);
	return (get_correct_return(res));
}

static int		replace_env_content_pwd(t_shell *shell, char *name,
										char *content)
{
	t_env	*begin;

	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, (ft_strlen(name))))
		{
			begin->content = content;
			if (begin->hidden != UNSET && content)
				begin->hidden = 0;
			if (!begin->hidden)
				ft_change_value_tab_env(shell, &shell->tab_env, name, content);
			return (SUCCESS);
		}
		begin = begin->next;
	}
	return (SUCCESS);
}

int		ft_cd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;
	char	*old_path;
	char	*cur_path;

	(void)tab_env;
	if (!exec_args[1] || !ft_strncmp(exec_args[1], "~", 2))
		res = go_to_home(shell);
	else if (!ft_strncmp(exec_args[1], "..", 3))
		res = go_to_upper_folder(shell);
	else if (!ft_strncmp(exec_args[1], "-", 2))
	{
		if ((res = go_to_old_pwd(shell)) == FAILURE)
			return (SUCCESS);
		// return (SUCCESS);
	}
	else
		res = go_to_folder(shell, exec_args[1]);
	if (res == -1)
		return (print_error(shell, exec_args[1], 1));
	get_var_env(shell, "PWD", &old_path, 0);
	if (!(old_path = ft_strdup(old_path))
		|| !add_lst_to_free(shell, old_path))
		ft_exit_failure(shell, F_MALLOC, old_path);
	if (!(cur_path = ft_calloc(1, 500)) || !add_lst_to_free(shell, cur_path))
		ft_exit_failure(shell, F_MALLOC, cur_path);
	if (ft_strlen(exec_args[1]) >= 2 &&
		ft_strncmp(exec_args[1], "//", 2) == 0 && exec_args[1][2] != '/')
		ft_memcpy(cur_path, exec_args[1], ft_strlen(exec_args[1]) + 1);
	else
		getcwd(cur_path, 500);
	replace_env_content_pwd(shell, "OLDPWD", old_path);
	replace_env_content_pwd(shell, "PWD", cur_path);
	return (SUCCESS);
}
