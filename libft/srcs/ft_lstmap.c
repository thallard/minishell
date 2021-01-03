/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bjacob <bjacob@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 11:28:20 by bjacob            #+#    #+#             */
/*   Updated: 2020/11/23 12:41:34 by bjacob           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*elem;
	t_list	*begin;

	if (!lst)
		return (NULL);
	if (!(elem = ft_lstnew(f(lst->content))))
		return (NULL);
	lst = lst->next;
	begin = elem;
	while (lst)
	{
		if (!(elem->next = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&begin, del);
			return (NULL);
		}
		elem = elem->next;
		lst = lst->next;
	}
	return (begin);
}
