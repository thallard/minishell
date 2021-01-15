/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:38:37 by thallard          #+#    #+#             */
/*   Updated: 2021/01/15 13:53:41 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static char	*ft_search_env_content(t_shell *shell, char *name, int limit)
{
	t_env	*lst;

	lst = shell->var_env;
	while (lst)
	{
		if (ft_strncmp(lst->name, name, limit) == 0)
			return (lst->content);
		lst = lst->next;
	}
	return (NULL);
}

char		*ft_get_env_value(t_shell *shell, char *txt, int *j, int i)
{
	char	*tmp;
	int		k;
	(void)i;
	txt++;
	k = 0;
	if (ft_isdigit(txt[0]))
	{
		*j += 1;
		return (NULL);
	}
	while (txt[k] && txt[k] != ' ' && txt[k] != '\'' && txt[k] != '\"' &&
		txt[k] != '/' && txt[k] != '$' && txt[k] != '_' && txt[k] != '=')
		k++;
	tmp = ft_search_env_content(shell, txt, k);
	//dprintf(1, "debug env = |%s| et limit %d\n", tmp, k);
	*j += k;
	return (tmp);
}

int		ft_change_value_tab_env(t_shell *shell, char ***tab_env, char *name, char *content)
{
	int		i;
	int		success;
	char	*var;
	char	**tab_temp;

	success = 0;
	i = -1;
	var = ft_strdup(name);	// a ajouter a la liste
	var = ft_strjoin_free(var, "=", 1, 0);
	while ((*tab_env)[++i])
	{
		if (!ft_strncmp((*tab_env)[i], var, ft_strlen(var)) && !success++)
			(*tab_env)[i] = ft_strjoin_free(var, content, 1, 0);
	}
	if (!success)
	{
		tab_temp = *tab_env;
		*tab_env = malloc_lst(shell, sizeof(char *) * (i + 2));
		i = -1;
		while (tab_temp[++i])
			(*tab_env)[i] = tab_temp[i];
		(*tab_env)[i] = ft_strjoin_free(var, content, 1, 0);
		(*tab_env)[++i] = NULL;
	}
	return (1);
}

int		ft_add_new_env(t_shell *shell, char *name, char *content)
{
	t_env	*new;

	new = ft_prepare_lst_env(shell, content, name);
	new->name = ft_memmove(new->name, name, ft_strlen(name) + 1);
	new->content = ft_memmove(new->content, content, ft_strlen(content) + 1);
	new->hidden = 0;
	ft_env_add_back(&shell->var_env, new);
	return (SUCCESS);
}

int		replace_env_content(t_shell *shell, char *name, char *content, int hidden)
{
	t_env	*begin;

	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, (ft_strlen(name))))
		{
			begin->hidden = hidden;
			begin->content = content;
			// free(begin->content);
			ft_change_value_tab_env(shell, &shell->tab_env, name, content);		
			return (SUCCESS);
		}
		begin = begin->next;
	}
	ft_add_new_env(shell, name, content);
	ft_change_value_tab_env(shell, &shell->tab_env, name, content);
	return (FAILURE);
}
