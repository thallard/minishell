/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallard <thallard@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:44:22 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/07 13:22:56 by thallard         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*add_lst_to_free(t_shell *shell, void *ptr)
{
	t_list	*elem;

	if (!(elem = ft_lstnew(ptr)))
	{
		free(ptr);
		return (NULL);
	}
	ft_lstadd_back(&shell->ptrs, elem);
	return (ptr);
}

void	*malloc_lst(t_shell *shell, int size) //penser a initialiser shell-ptrs
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	if (!add_lst_to_free(shell, ptr))
	{
		free(ptr);
		return (NULL);
	}
	return (ptr);
}

int		free_all_ptr(t_shell *shell)
{
	ft_lstclear(&shell->ptrs, free);
	return (0);
}

void	ft_free_export_env(t_env **env)
{
	t_env	*elem;
	t_env	*next;

	elem = *env;
	while (elem)
	{
		next = elem->next;
		ft_free_ptr(elem->content);
		ft_free_ptr(elem->name);
		ft_free_ptr(elem);
		elem = next;
	}
	*env = NULL;
}
