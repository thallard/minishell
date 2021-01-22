/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:36:35 by thallard          #+#    #+#             */
/*   Updated: 2021/01/22 09:14:17 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

t_env	*ft_prepare_lst_env(t_shell *shell, char *content, char *name)
{
	t_env	*new_lst;
	int		size;

	if (!content)
		size = 1;
	else
		size = ft_strlen(content);
	new_lst = NULL;
	if (!(new_lst = malloc_lst(shell, sizeof(t_env))))
		ft_exit_failure(shell, F_MALLOC, NULL);
	new_lst->next = NULL;
	if (!(new_lst->name = malloc_lst(shell, sizeof(char) *
		ft_strlen(name) + 100)))
		ft_exit_failure(shell, F_MALLOC, new_lst->name);
	if (!(new_lst->content = malloc_lst(shell, sizeof(char) * size + 100)))
		ft_exit_failure(shell, F_MALLOC, NULL);
	new_lst->hidden = TO_PRINT;
	return (new_lst);
}

int		ft_add_value_to_existent_env(t_shell *shell, t_env *env, char *str)
{
	char	*old_content;
	char	*new_name;
	int		i;
	char	*new_content;

	new_name = NULL;
	new_content = ft_strdup(str);
	i = -1;
	if (!(new_name = ft_strdup(env->name)) ||
		!(add_lst_to_free(shell, new_name)))
		ft_exit_failure(shell, F_MALLOC, new_name);
	while (new_name[++i] && new_name[i] != '+')
		;
	new_name[i] = '\0';
	if (get_var_env(shell, new_name, &old_content, 1) && old_content)
	{
		new_content = ft_strjoin_free(old_content, new_content, 0, 0);
		replace_env_content(shell, new_name, new_content, env->hidden);
	}
	else
		replace_env_content(shell, new_name, new_content, env->hidden);
	return (SUCCESS);
}

int		ft_filter_and_add(t_shell *shell, t_env *env, char *str, int j)
{
	int		k;

	k = 0;
	if (j <= ft_strlen(str) && ((char *)env->content)[0] != '\0'
		&& env->hidden != 1)
	{
		if (str[j] == ' ')
			j = ft_strlen(str) + 1;
		while (str[j])
			((char *)env->content)[k++] = str[j++];
		((char *)env->content)[k] = '\0';
		env->hidden = TO_PRINT;
		replace_env_content(shell, env->name, env->content, env->hidden);
	}
	else
	{
		env->hidden = NOT_PRINT;
		((char *)env->content)[k] = '\0';
		replace_env_content(shell, env->name, env->content, 1);
	}
	return (SUCCESS);
}

int		ft_get_arg_values_env(t_shell *shell, char **arg)
{
	int		i;
	int		j;
	int		add;
	t_env	*new_lst;

	i = 0;
	while (arg[++i])
	{
		add = 0;
		new_lst = ft_prepare_lst_env(shell, arg[i], arg[i]);
		j = -1;
		if (ft_isdigit(arg[i][0]) || arg[i][0] == '-' || arg[i][0] == '=')
			return (FAILURE);
		while (arg[i][++j] && arg[i][j] != '=')
			if (!char_not_valid(&arg[i][j]))
				new_lst->name[j] = arg[i][j];
			else
				return (FAILURE);
		if (arg[i][j] == '=' && arg[i][j - 1] == '+' && j && !(add = 1))
			arg[i][j] = '\0';
		if (arg[i][j] == '=' && !arg[i][j + 1])
			new_lst->hidden = TO_PRINT;
		else if (arg[i][j] != '=' && !arg[i][j])
			new_lst->hidden = NOT_PRINT;
		new_lst->name[j++] = '\0';
		if (add)
			return (ft_add_value_to_existent_env(shell, new_lst, &arg[i][j]));
		ft_filter_and_add(shell, new_lst, arg[i], j);
	}
	if (new_lst->name)
		replace_env_content(shell, "_", new_lst->name, TO_PRINT);
	return (SUCCESS);
}

int		ft_export(t_shell *shell, char **exec_args, char **tab_env)
{
	t_env	*sorted_env;

	sorted_env = NULL;
	(void)tab_env;
	if (exec_args[1])
	{
		if (ft_get_arg_values_env(shell, exec_args) > 0)
		{
			shell->exit = 0;
			return (SUCCESS);
		}
		else
		{
			ft_printf(2, "Error : name syntax is not correct.\n");
			return ((shell->exit = 1));
		}
	}
	else
	{
		sorted_env = ft_clone_export_env(shell->var_env);
		ft_sort_export_var(sorted_env);
		ft_print_export_var(sorted_env);
		ft_free_export_env(&sorted_env);
	}
	return (SUCCESS);
}
