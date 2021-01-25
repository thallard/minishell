/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:50:23 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 09:08:35 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int			get_correct_return(int res)
{
	if (res == -1)
		return (-1);
	return (SUCCESS);
}

char		*build_path(t_shell *shell, char *current_path, char *folder)
{
	char	*path_temp;
	char	*path;

	if (!(path = ft_strjoin(current_path, "/")))
		ft_exit_failure(shell, F_MALLOC, NULL);
	path_temp = path;
	if (!(path = ft_strjoin_free(path, folder, 1, 0)))
		ft_exit_failure(shell, F_MALLOC, path_temp);
	path_temp = path;
	if (!(path = ft_strtrim(path, "\n")))
		ft_exit_failure(shell, F_MALLOC, path_temp);
	free(path_temp);
	return (path);
}

static int	replace_env_content_pwd(t_shell *shell, char *name, char *content)
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

void		maj_pwd_and_oldpwd(t_shell *shell, char **exec_args)
{
	char	*old_path;
	char	*cur_path;

	get_var_env(shell, "PWD", &old_path, 0);
	if (!(old_path = ft_strdup(old_path))
		|| !add_lst_to_free(shell, old_path))
		ft_exit_failure(shell, F_MALLOC, old_path);
	if (!(cur_path = ft_calloc(1, 500)) || !add_lst_to_free(shell, cur_path))
		ft_exit_failure(shell, F_MALLOC, cur_path);
	if (ft_strlen(exec_args[1]) >= 2 &&
		ft_strncmp(exec_args[1], "//", 2) == 0 && exec_args[1][2] != '/')
		ft_memcpy(cur_path, exec_args[1], ft_strlen(exec_args[1]) + 1);
	else if (!(cur_path = getcwd(NULL, 0)) || !add_lst_to_free(shell, cur_path))
		ft_exit_failure(shell, F_MALLOC, NULL);
	replace_env_content_pwd(shell, "OLDPWD", old_path);
	replace_env_content_pwd(shell, "PWD", cur_path);
}
