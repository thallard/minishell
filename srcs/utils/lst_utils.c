/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:23:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/06 09:17:13 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
