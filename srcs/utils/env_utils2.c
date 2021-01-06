/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:08:08 by thallard          #+#    #+#             */
/*   Updated: 2021/01/06 09:18:31 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_env_remove_if(t_env **begin_list, void *name_ref,
		int (*cmp)())
{
	t_env	*ptr;
	t_env	*ptr_back;

	if (*begin_list == NULL)
		return ;
	ptr = (*begin_list)->next;
	ptr_back = (*begin_list);
	while (ptr)
	{
		if (cmp(ptr->name, name_ref) == 0)
			ft_remove_elem(&ptr_back, &ptr);
		else
		{
			ptr_back = ptr;
			ptr = ptr->next;
		}
	}
	if (cmp((*begin_list)->name, name_ref) == 0)
	{
		ptr = (*begin_list)->next;
		free((*begin_list)->name);
		free(ptr->content);
		free(*begin_list);
		*begin_list = ptr;
	}
}

int		get_var_env(t_shell *shell, char *var_name, char **content)
{
	t_env	*begin;

	begin = shell->var_env;
	while (begin)
	{
		if (!ft_strncmp(begin->name, var_name, ft_strlen(var_name) + 1))
		{
			*content = begin->content;
			if (!(*content))
				return (0);
			return (1);
		}
		begin = begin->next;
	}
	return (-1);
}