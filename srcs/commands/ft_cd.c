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
		return (ft_free_ptr(path_temp));	// a gerer
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
		return (print_oldpwd_error(shell, "cd"));
	res = chdir(path);
	if (!(pwd = ft_get_var_env(shell, "PWD")) ||
		!(old_pwd = ft_get_var_env(shell, "OLDPWD")))
		return (FAILURE);			// a voir comment on le gere
	ft_swap_env_content(pwd, old_pwd);
	ft_printf(1, "%s\n", pwd->content);
	return (get_correct_return(res));
}

int		ft_cd(t_shell *shell, char **exec_args, char **tab_env)
{
	int		res;
	char	*old_path;
	char	*cur_path;

	// ft_print_tab_char(exec_args);
	(void)tab_env;
	if (!exec_args[1] || !ft_strncmp(exec_args[1], "~", 2))
		res = go_to_home(shell);
	else if (!ft_strncmp(exec_args[1], "..", 3))
		res = go_to_upper_folder();
	else if (!ft_strncmp(exec_args[1], "-", 2))
		return (go_to_old_pwd(shell));
	else
		res = go_to_folder(shell, exec_args[1]);
	if (res == -1)
		return (print_error(shell, exec_args[1]));	// a voir
	get_var_env(shell, "PWD", &old_path);
	if (!(old_path = ft_strdup(old_path)) || !add_lst_to_free(shell, old_path))
		ft_exit_failure(shell, F_MALLOC, old_path);
	if (!(cur_path = ft_calloc(1, 500))
		|| !add_lst_to_free(shell, cur_path))
		ft_exit_failure(shell, F_MALLOC, cur_path);
	if (exec_args[1] && ft_strncmp(exec_args[1], "..", 3) && ft_strncmp(exec_args[1], "-", 2) &&
		ft_strncmp(exec_args[1], "~", 2))
		ft_memcpy(cur_path, exec_args[1], ft_strlen(exec_args[1]) + 1);
	else
		getcwd(cur_path, 1000);
	replace_env_content(shell, "OLDPWD", old_path, 0); // pb possible avec lst des ptrs
	replace_env_content(shell, "PWD", cur_path, 0);

// ft_print_env_var(shell->var_env);
// dprintf(1, "\n\n");

// ft_print_tab_char(shell->tab_env);

	return (SUCCESS);
}
