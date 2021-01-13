/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:33:55 by bjacob            #+#    #+#             */
/*   Updated: 2021/01/13 09:03:49 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*next;

	elem = *lst;
	while (elem)
	{
		next = elem->next;
		if (elem->content)
			del(elem->content);
		free(elem);
		elem = next;
	}
	*lst = NULL;
}
