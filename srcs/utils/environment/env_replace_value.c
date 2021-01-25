/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:38:37 by thallard          #+#    #+#             */
/*   Updated: 2021/01/23 09:13:14 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_last_arg_env(t_shell *shell, t_tree *node)
{
	int		i;
	char	*str;
	char	**arg;

	arg = node->args->args;
	if (arg && ft_strncmp(arg[0], "export", 7) &&
		ft_strncmp(arg[0], "env", 4))
	{
		arg = node->args->args;
		if (arg)
		{
			i = 0;
			while (arg[i + 1])
				i++;
			if (!(str = ft_strdup(arg[i])) || !add_lst_to_free(shell, str))
				ft_exit_failure(shell, F_MALLOC, str);
			replace_env_content(shell, "_", str, 0);
		}
	}
}

void	ft_change_value_tab_env(t_shell *shell, char ***tab_env,
								char *name, char *content)
{
	int		i;
	int		success;
	char	*var;
	char	**tab_temp;

	success = 0;
	var = ft_prepare_tab_change_value(shell, name, &i);
	while ((*tab_env)[++i])
		if (!ft_strncmp((*tab_env)[i], var, ft_strlen(var)) && !success++ &&
			(!((*tab_env)[i] = ft_strjoin_free(var, content, 0, 0)) ||
			!add_lst_to_free(shell, (*tab_env)[i])))
			ft_exit_failure(shell, F_MALLOC, (*tab_env)[i]);
	if (!success && content[0])
	{
		tab_temp = *tab_env;
		if (!(*tab_env = malloc_lst(shell, sizeof(char *) * (i + 2))))
			ft_exit_failure(shell, F_MALLOC, NULL);
		i = -1;
		while (tab_temp[++i])
			(*tab_env)[i] = tab_temp[i];
		if (!((*tab_env)[i] = ft_strjoin_free(var, content, 0, 0)) ||
			!add_lst_to_free(shell, (*tab_env)[i]))
			ft_exit_failure(shell, F_MALLOC, (*tab_env)[i]);
		(*tab_env)[++i] = NULL;
	}
}

int		ft_add_new_env(t_shell *shell, char *name, char *content, int hidden)
{
	t_env	*new;

	new = ft_prepare_lst_env(shell, content, name);
	new->name = ft_memmove(new->name, name, ft_strlen(name) + 1);
	new->content = ft_memmove(new->content, content, ft_strlen(content) + 1);
	new->hidden = hidden;
	ft_env_add_back(&shell->var_env, new);
	return (SUCCESS);
}

int		replace_env_content(t_shell *shell, char *name,
		char *content, int hidden)
{
	t_env	*begin;

	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, (ft_strlen(name) + 1)))
		{
			if (hidden != NOT_PRINT)
			{
				begin->hidden = hidden;
				begin->content = content;
				ft_change_value_tab_env(shell, &shell->tab_env, name, content);
			}
			return (SUCCESS);
		}
		begin = begin->next;
	}
	ft_add_new_env(shell, name, content, hidden);
	ft_change_value_tab_env(shell, &shell->tab_env, name, content);
	return (SUCCESS);
}

int		ft_prepare_hidden_name_export(t_shell *shell,
		t_env **env, char *arg, int j)
{
	int		add;

	add = 0;
	if (arg[j] == '=' && arg[j - 1] == '+' && j && !(add = 1))
		arg[j] = '\0';
	if (arg[j] == '=' && arg[j + 1])
		(*env)->hidden = TO_PRINT;
	else if (arg[j] != '=' && !arg[j])
		(*env)->hidden = NOT_PRINT;
	(*env)->name[j++] = '\0';
	if (add)
		return (ft_add_value_to_existent_env(shell, *env, &arg[j]));
	ft_filter_and_add(shell, *env, arg, j);
	return (SUCCESS);
}
