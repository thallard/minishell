/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:38:37 by thallard          #+#    #+#             */
/*   Updated: 2021/01/22 10:21:44 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void	change_last_arg_env(t_shell *shell, t_tree *node)
{
	int		i;
	char	*str;
	char	**exec_args;

	exec_args = node->args->args;
	if (exec_args && ft_strncmp(exec_args[0], "export", 7))
	{
		exec_args = node->args->args;
		if (exec_args)
		{
			i = 0;
			while (exec_args[i + 1])
				i++;
			if (!(str = ft_strdup(exec_args[i])) || !add_lst_to_free(shell, str))
				ft_exit_failure(shell, F_MALLOC, str);
			replace_env_content(shell, "_", str, 0);
		}
	}
}

int		ft_change_value_tab_env(t_shell *shell, char ***tab_env, char *name, char *content)
{
	int		i;
	int		success;
	char	*var;
	char	**tab_temp;

	success = 0;
	i = -1;
	if (!(var = ft_strdup(name)) || !add_lst_to_free(shell, var))
		ft_exit_failure(shell, F_MALLOC, var);
		if (!(var = ft_strjoin_free(var, "=", 1, 0)))
			ft_exit_failure(shell, F_MALLOC, NULL);
	while ((*tab_env)[++i])
		if (!ft_strncmp((*tab_env)[i], var, ft_strlen(var)) && !success++ &&
			!((*tab_env)[i] = ft_strjoin_free(var, content, 1, 0)))
			ft_exit_failure(shell, F_MALLOC, NULL);
	if (!success && content[0])
	{
		tab_temp = *tab_env;
		if (!(*tab_env = malloc_lst(shell, sizeof(char *) * (i + 2))))
			ft_exit_failure(shell, F_MALLOC, NULL);
		i = -1;
		while (tab_temp[++i])
			(*tab_env)[i] = tab_temp[i];
			if (!((*tab_env)[i] = ft_strjoin_free(var, content, 1, 0)))
				ft_exit_failure(shell, F_MALLOC, NULL);
		(*tab_env)[++i] = NULL;
	}
	return (1);
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

int		replace_env_content(t_shell *shell, char *name, char *content, int hidden)
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
				// free(begin->content);
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
