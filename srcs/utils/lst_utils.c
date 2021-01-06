/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:23:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/05 18:02:52 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../libft/includes/libft.h"

t_env	*ft_env_last(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}


void	ft_env_add_back(t_env **alst, t_env *new)
{
	t_env	*elem;

	if (!(*alst))
		*alst = new;
	else
	{
		elem = ft_env_last(*alst);
		elem->next = new;
	}
}

void	ft_print_env_var(t_env *var_end)
{
	while (var_end)
	{
		ft_printf("%s=%s\n", var_end->name, var_end->content);
		var_end = var_end->next;
	}
}

void	ft_remove_elem(t_env **ptr_back, t_env **ptr)
{
	(*ptr_back)->next = (*ptr)->next;
	free((*ptr)->name);
	free((*ptr)->content);
	free(*ptr);
	*ptr = (*ptr_back)->next;
}

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