/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_replace_value.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:38:37 by thallard          #+#    #+#             */
/*   Updated: 2021/01/14 13:30:05 by bjacob           ###   ########lyon.fr   */
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
	while (txt[k] && txt[k] != ' ' && txt[k] != '\'' && txt[k] != '\"' &&
		txt[k] != '/' && txt[k] != '$' && txt[k] != '_' && txt[k] != '=')
		k++;
	tmp = ft_search_env_content(shell, txt, k);
	//dprintf(1, "debug env = |%s| et limit %d\n", tmp, k);
	*j += k;
	return (tmp);
}

int		ft_if_env_exists(t_shell *shell, char *name, char *content)
{
	t_env	*begin;

	begin = shell->var_env;
	while (begin->next)
	{
		begin = begin->next;
		if (ft_strncmp(begin->name, name, (ft_strlen(name))) == 0)
		{			
			if (env->hidden == 1)
			{
				begin = shell->var_env;
				return (SUCCESS);
			}
			begin->hidden = env->hidden;
			// free(shell->var_env->content);
			begin->content = content;
			begin = shell->var_env;
			return (SUCCESS);
		}
	}
	begin->next = env;
	return (FAILURE);
}

// int		ft_change_value_tab_env(t_shell *shell, char **tab_env, char *name)
// {
	

// 	return (0);
// }