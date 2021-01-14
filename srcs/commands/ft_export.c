/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:36:35 by thallard          #+#    #+#             */
/*   Updated: 2021/01/14 10:37:49 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

t_env	*ft_prepare_lst_env(t_shell *shell, char **tab, int i)
{
	t_env	*new_lst;

	new_lst = NULL;
	if (!(new_lst = malloc_lst(shell, sizeof(t_env))) ||
		!(add_lst_to_free(shell, new_lst)))
		return (NULL);
	new_lst->next = NULL;
	if (!(new_lst->name = malloc(sizeof(char) * (ft_strlen(tab[i]) + 100))) ||
		!(add_lst_to_free(shell, new_lst->name)))
		return (NULL);
	if (!(new_lst->content = malloc(sizeof(char) * (ft_strlen(tab[i]) + 100))) ||
		!(add_lst_to_free(shell, new_lst->content)))
		return (NULL);
	return (new_lst);
}

int		ft_filter_and_add(t_shell *shell, t_env *env, char *str, int j)
{
	int		k;

	k = 0;
	if (j <= ft_strlen(str) && ((char *)env->content)[0] != '\0' && env->hidden != 2)
		{
			if (str[j] == ' ')
				j = ft_strlen(str) + 1;
			while (str[j])
				((char *)env->content)[k++] = str[j++];
			((char *)env->content)[k] = '\0';
			env->hidden = 0;
			ft_if_env_exists(shell, env->name, env->content, env);
		}
		else if (env->hidden != 2)
		{
			env->hidden = 1;
			((char *)env->content)[k] = '\0';
			ft_if_env_exists(shell, env->name, env->content, env);
		}
		else if (env->hidden == 2)
		{
			((char *)env->content)[k] = '\0';
			ft_if_env_exists(shell, env->name, env->content, env);
		}
	return (SUCCESS);
}

int		ft_add_new_env(t_shell *shell, char **tab)
{
	int		i;
	int		j;
	t_env	*new_lst;
	// tab = ft_split_minishell_args(node->left->item, ' ', shell);
	//tab = node->args;
	i = 0;
	while (tab[++i])
	{
		//str = ft_split_quotes(shell, shell->split, tab[i]);
			new_lst = ft_prepare_lst_env(shell, tab, 0);
		j = -1;
		while (tab[i][++j] && tab[i][j] != '=')
			new_lst->name[j] = tab[i][j];
		if (tab[i][j] == '=' && !tab[i][j + 1])
			new_lst->hidden = 2;
		else if (tab[i][j] != '=' && !tab[i][j])
			new_lst->hidden = 1;
		else
			new_lst->hidden = 0;
		new_lst->name[j++] = '\0';
		if ((j + 2) <= ft_strlen(tab[i]))
			if (ft_strncmp(&tab[i][j], "\"\"", 2) == 0 || ft_strncmp(&tab[i][j], "\'\'", 2) == 0)
				((char *)new_lst->content)[i] = '\0';
		ft_filter_and_add(shell, new_lst, tab[i], j);
	}
	return (SUCCESS);
}

int		ft_export(t_shell *shell, char **exec_args, char **tab_env)
{
	t_env	*sorted_env;

	sorted_env = NULL;
	(void)tab_env;
	//ft_print_tab_char(exec_args);
	if (exec_args[1])
	{
		if (ft_add_new_env(shell, exec_args))
		{
			shell->exit = 0;
			return (SUCCESS);
		}
		else
		{
			shell->exit = 1;
			return (SUCCESS);
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
