/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 10:44:22 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/23 09:37:26 by bjacob           ###   ########lyon.fr   */
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
	if (!(shell->ptrs))
		shell->ptrs = elem;
	else
		ft_lstadd_back(&shell->ptrs, elem);
	return (ptr);
}

void	*malloc_lst(t_shell *shell, int size)
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
	return (SUCCESS);
}

void	ft_lstfd_close_clear(t_fd **lst)
{
	t_fd	*elem;
	t_fd	*next;

	elem = *lst;
	while (elem)
	{
		next = elem->next;
		close(elem->fd);
		elem = next;
	}
	*lst = NULL;
}
