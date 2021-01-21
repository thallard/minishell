/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_unset_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:48:28 by thallard          #+#    #+#             */
/*   Updated: 2021/01/21 15:55:48 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

int		ft_sort_tab_env(t_shell *shell, char **tab)
{
	int		len;
	int		i;

	i = -1;
	len = 0;
	while (tab[++i])
		if (!tab[i][0])
			len = i;
	if (!(tab[len] = ft_strdup(tab[i - 1])) ||
		!(add_lst_to_free(shell, tab[len])))
		ft_exit_failure(shell, F_MALLOC, tab[len]);
	tab[i - 1] = NULL;
	// ft_print_tab_char(tab);
	return (SUCCESS);
}

int		ft_remove_element_tab(t_shell *shell, char **tab, char *name)
{
	int		i;

	i = -1;
	if (!(name = ft_strjoin(name, "=")) || !(add_lst_to_free(shell, name)))
		ft_exit_failure(shell, F_MALLOC, name);
	while (tab[++i])
	{
		if (!ft_strncmp(name, tab[i], ft_strlen(name)))
		{
				tab[i] = "";
				ft_sort_tab_env(shell, tab);
				return (SUCCESS);
		}
			
	}
	return (SUCCESS);
}

int		ft_unset_hide_env(t_shell *shell, t_env **env, char *name)
{
	t_env	*begin;

	begin = *env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, ft_strlen(name) + 1))
		{
			begin->content = "";
			begin->hidden = UNSET;
			ft_remove_element_tab(shell, shell->tab_env, name);
			return (SUCCESS);
		}
		begin = begin->next;
	}
	return (FAILURE);
}


int			char_not_valid(char c)
{
	return (c == ';' || c == '\\' || c == '\'' || c == '&' || c == '!' ||
			c == '\"' || c == '$' || c == '@' || c == '|');
}

int		ft_set_shlvl(t_shell *shell)
{
	char	*content;
	int		lvl;

	if (ft_get_var_env(shell, "SHLVL"))
		if (get_var_env(shell, "SHLVL", &content))
		{
			lvl = ft_atoi(content);
			content = ft_itoa(++lvl);
			dprintf(1, "content = %s\n", content);
			replace_env_content(shell, "SHLVL", content, TO_PRINT);
			return (SUCCESS);
		}
	return (FAILURE);
}