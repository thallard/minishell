/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 09:08:08 by thallard          #+#    #+#             */
/*   Updated: 2021/01/13 13:49:14 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

static void	ft_swap_env(t_env *a, t_env *b)
{
	char *lastName;

	lastName = a->name;
	a->name = b->name;
	b->name = lastName;

	lastName = a->content;
	a->content = b->content;
	b->content = lastName;
}

void		ft_env_remove_if(t_env **begin_list, void *name_ref,
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

int			get_var_env(t_shell *shell, char *var_name, char **content)
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

void		ft_sort_export_var(t_env *env)
{
	t_env	*ptr;

	ptr = env;
	while (ptr && ptr->next)
		if (ft_strcmp(ptr->name, ptr->next->name) > 0)
		{
			ft_swap_env(ptr, ptr->next);
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