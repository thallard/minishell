/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:38:37 by thallard          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2021/01/14 14:11:37 by thallard         ###   ########lyon.fr   */
=======
/*   Updated: 2021/01/14 13:32:06 by bjacob           ###   ########lyon.fr   */
>>>>>>> b6f4c029a2bc17d4f84e08b8d771d26dec14c1b5
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

int		ft_change_value_tab_env(t_shell *shell, char **tab_env, char *name, char *content)
{
	int		i;
	int		size;
	i = -1;
	(void)shell;
	size = ft_strlen(name);
	name[size] = '=';
	name[size + 1] = '\0';
	while (tab_env[++i])
	{
		if (ft_strncmp(tab_env[i], name, ft_strlen(name)) == 0)
			tab_env[i] = ft_strjoin(name, content);
	}
	return (1);
}

int		ft_add_new_env_tab(t_shell *shell, char *name, char *content)
{
	t_env	*new;
	(void)name;
	new = ft_prepare_lst_env(shell, content);
	ft_env_add_back(&shell->var_env, new);
	return (SUCCESS);
}

int		replace_env_content(t_shell *shell, char *name, char *content)
{
	t_env	*begin;

	begin = shell->var_env;
	while (begin)
	{
		if (ft_strncmp(begin->name, name, (ft_strlen(name))) == 0)
		{
			begin->content = content;
			if (!content)
				begin->hidden = 1;
			else
				begin->hidden = 0;
			// free(begin->content);
			//ft_change_value_tab_env(shell, shell->tab_env, name, content);
			return (SUCCESS);
		}
		begin = begin->next;
	}
	ft_add_new_env_tab(shell, name, content);
	return (FAILURE);
}
