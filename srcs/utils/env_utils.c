/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:23:56 by thallard          #+#    #+#             */
/*   Updated: 2021/01/07 10:33:04 by bjacob           ###   ########lyon.fr   */
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
		if (var_end->hidden == 2)
			ft_printf(1, "%s=\n", var_end->name);
		if (var_end->hidden == 0)
		ft_printf(1, "%s", var_end->name);
		if (var_end->hidden == 0)
			ft_printf(1, "=");
		if (var_end->hidden == 0)
			ft_printf(1, "%s", var_end->content);
		if (var_end->hidden == 0)
			ft_printf(1, "\n");
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
