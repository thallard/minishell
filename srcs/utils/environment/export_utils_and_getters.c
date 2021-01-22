/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:08:08 by thallard          #+#    #+#             */
/*   Updated: 2021/01/22 09:29:30 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_env	*ft_get_var_env(t_shell *shell, char *name)
{
	t_env	*begin;
	int		len;

	len = ft_strlen(name);
	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, name, len))
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}

int			get_var_env(t_shell *shell, char *var_name, char **content, int unset)
{
	t_env	*begin;

	*content = NULL;
	if (var_name && ft_isdigit(var_name[0]) && !var_name[1])
	{
		if (!(*content = malloc_lst(shell, 1)))
			ft_exit_failure(shell, F_MALLOC, NULL);
		(*content)[0] = 0;
		return (1);
	}
	if (var_name && var_name[0] == '?' && !var_name[1])	// bloc a verifier
	{
		if (!(*content = ft_itoa(shell->exit)) ||
			!add_lst_to_free(shell, content))
			ft_exit_failure(shell, F_MALLOC, content);
		return (1);
	}
	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, var_name, ft_strlen(var_name) + 1))
		{
			if (unset == 0 || begin->hidden != UNSET)
				*content = begin->content;
			if (!(*content))
				return (0);
			return (1);
		}
		begin = begin->next;
	}
	return (-1);
}

void		ft_sort_export_var(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr && ptr->next)
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
		{
			ft_swap_env_all(ptr, ptr->next);
			ptr = env;
		}
		else
			ptr = ptr->next;
}

t_env		*ft_clone_export_env(t_env *lst)
{
	t_env	*sorted;

	if (lst == NULL || !(sorted = malloc(sizeof(t_env))))
		return (NULL);
	sorted->content = ft_strdup(lst->content);
	sorted->name = ft_strdup(lst->name);
	sorted->hidden = lst->hidden;
	sorted->next = ft_clone_export_env(lst->next);
	return (sorted);
}